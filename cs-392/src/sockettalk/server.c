/* 
Authors: Daniel Heyman & Carla Noshi
Implements a piping process.
Sources used: https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm, http://www.binarytides.com/multiple-socket-connections-fdset-select-linux/
*/
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <sys/time.h>
#include <errno.h>
#include "my.h"

/*void doprocessing (int sock) {
   int n, pid;
   char buffer[256];
   bzero(buffer,256);
   n = read(sock,buffer,255);
   char * username;
   
   if (n < 0) {
      my_str("ERROR reading from socket");
      return -1;
   }
   
   username = my_strdup(buffer);
   
   while(1) {
       n = read(sock,buffer,255);
       if (n < 0) {
          my_str("ERROR reading from socket");
          return -1;
       }
       
       if(my_strncmp(buffer, "/nick ", 6)) {
           
       } else if(my_strncmp(buffer, "/exit ", 6)) {
           
       } else if(my_strncmp(buffer, "/me ", 4)) {
           
       } else {
           my_str()
       }
   }
	
}*/

int main(int argc, char* argv[])
{
    fd_set readfds;
    int port, sockfd, newsockfd, newsockfds[99], max_fds = 99, sd, max_sd, activity, n;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[256];
    
    if (argc < 2) {
        my_str("Invalid arguments");
        return -1;
    }
    
    for(int i = 0; i < max_fds; i++) newsockfds[i] = 0;
    
    port = my_atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        my_str("Error opening socket");
        return -1;
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        my_str("ERROR on binding");
        return -1;
    }
   
    if (listen(sockfd, 5) < 0) {
        my_str("ERROR on listening");
        return -1;
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
            return -1;
        }
        
        if (FD_ISSET(sockfd, &readfds)) {
            if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) < 0) {
                my_str("Error on selecting socket");
                return -1;
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
            
            if (FD_ISSET( sd , &readfds))  {
                if ((n = read( sd , buffer, 255)) == 0) {
                    getpeername(sd , (struct sockaddr*) &cli_addr, &clilen);
                    close(sd);
                    newsockfds[i] = 0;
                } else {
                    buffer[n] = '\0';
                    
                    //send(sd , buffer , strlen(buffer) , 0 );
                }
            }
        }
    }
    
    return 0;
}
