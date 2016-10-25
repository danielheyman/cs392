/* 
Authors: Daniel Heyman & Carla Noshi
Takes one command line arguments: a port with which to listen.
Sources used: https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm, http://www.binarytides.com/multiple-socket-connections-fdset-select-linux/
*/
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>
#include "my.h"

int sockfd;

void closing() {
    close(sockfd);
    exit(0);
}

int main(int argc, char* argv[])
{
    fd_set readfds;
    int port, newsockfd, newsockfds[99], max_fds = 99, sd, max_sd, activity, n;
    char * usernames[99];
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[256];
    char * sending;
    
    signal(SIGINT, closing);
    signal(SIGQUIT, closing);
    signal(SIGPIPE, SIG_IGN);
    
    if (argc < 2) {
        my_str("Invalid arguments");
        exit(1);
    }
    
    for(int i = 0; i < max_fds; i++) newsockfds[i] = 0;
    
    port = my_atoi(argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        my_str("Error opening socket");
        exit(1);
    } else {
        my_str("Opened socket...\n");
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        my_str("ERROR on binding");
        exit(1);
    }
   
    if (listen(sockfd, 5) < 0) {
        my_str("ERROR on listening");
        exit(1);
    } else {
        my_str("Listening on ");
        my_str(argv[1]);
        my_str("...\n");
    }
    
    clilen = sizeof(cli_addr);
   
    while(1) {
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        max_sd = sockfd;
        
        for(int i = 0 ; i < max_fds ; i++) {
            sd = newsockfds[i];
            if(sd > 0) FD_SET( sd , &readfds);
            if(sd > max_sd) max_sd = sd;
        }
        
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
        if (activity < 0 && errno != EINTR) {
            my_str("Error selecting socket");
            exit(1);
        }
        
        if (FD_ISSET(sockfd, &readfds)) {
            if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) < 0) {
                my_str("Error on selecting socket");
                exit(1);
            }
            
            if (n < 0) {
               my_str("ERROR reading from socket");
               exit(1);
            }
            
            for(int i = 0; i < max_fds; i++)  {
                if(newsockfds[i] == 0) {
                    newsockfds[i] = newsockfd;
                    break;
                }
            }
        }

        for(int i = 0; i < max_fds; i++)  {
            sd = newsockfds[i];
            
            if (FD_ISSET(sd , &readfds)) {
                 if ((n = read( sd , buffer, 255)) == 0) {
                    getpeername(sd , (struct sockaddr*) &cli_addr, &clilen);
                    close(sd);
                    newsockfds[i] = 0;
                    free(usernames[i]);
                    usernames[i] = NULL;
                } else {
                    buffer[n] = '\0';

                    if(my_strncmp(buffer, "/nick ", 6) == 0) {
                        if(buffer[n - 1] == '\n') buffer[n - 1] = '\0';
                        free(usernames[i]);
                        usernames[i] = my_strdup(&(buffer[6]));
                    } else if(my_strncmp(buffer, "/", 1) == 0 && my_strncmp(buffer, "/me", 3) != 0) {
                        sending = my_strdup("This is an invalid command.\n");
                        free(sending);
                        send(sd , sending , my_strlen(sending) , 0 );
                    } else {
                        if(my_strncmp(buffer, "/me ", 4) == 0) {
                            sending = my_strconcat(usernames[i], my_strconcat(" ", &(buffer[4])));
                        } else {
                            sending = my_strconcat(usernames[i], my_strconcat(": ", buffer));
                        }
                        my_str(sending);
                        for(int j = 0; j < max_fds; j++)  {
                            if(newsockfds[j] > 0 && i != j)  send(newsockfds[j] , sending , my_strlen(sending) , 0 );
                        }
                        free(sending);
                    }
                }
            }
        }
    }
    
    return 0;
}
