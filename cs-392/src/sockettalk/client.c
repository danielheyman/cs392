/* 
Authors: Daniel Heyman & Carla Noshi
Takes two command line arguments: a hostname and a port with which to connect.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "../../include/my.h"
#define h_addr h_addr_list[0]

int main(int argc, char* argv[])
{
    int sockfd, portno, n, length, i, num, j;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char user[256];
    char buffer[256];
    char first[270] = "/nick ";
    fd_set readSet;
    
    FD_ZERO(&readSet);
    
    if (argc < 3) 
    {
        my_str("Invalid arguments");
        exit(0);
    }
   
    portno = my_atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) 
    {
       my_str("Error opening socket");
       exit(1);
    }
        
    server = gethostbyname(argv[1]);
    
    if (server == NULL) 
    {
        my_str("Error, invalid server");
        exit(0);
    }
    
    for(j = 0; j < sizeof(serv_addr); j++)
    {
        ((char *) &serv_addr)[j] = 0;
    }
    
    serv_addr.sin_family = AF_INET;
    
    length = server->h_length;
    
    for(i = 0; i < length; i++)
    {
        ((char *)&serv_addr.sin_addr.s_addr)[i] = ((char *)server->h_addr)[i];
    }
    
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
        my_str("Connect Error");
        exit(1);
    } 
    
       
    for(i = 0; i < 256; i++)
    {
        user[i] = '\0';
    } 
    
    my_str("Please enter a username: ");
    
    num = read(0, user, 255);
    user[num - 1] = '\0';
    my_strcat(first, user);
                
    if (write(sockfd, first, my_strlen(first)) < 0) 
    {
        my_str("Write Error");
        exit(1);
    } 
    
    while(1)
    {    
        FD_ZERO(&readSet);
        FD_SET(0, &readSet);
        FD_SET(sockfd, &readSet);
       
        for(i = 0; i < 256; i++)
        {
            buffer[i] = '\0';
        } 
        
        if(select(sockfd + 1, &readSet, NULL, NULL, NULL) < 0)
        {
            my_str("select Error");
            exit(1);       
        }
        
        /*If true, user input will be read in, otherwise 
          it will read from server */
        if(FD_ISSET(0, &readSet))
        {
            n = read(0, buffer, 255);
                
            if (n < 0) 
            {
                my_str("Read Error");
                exit(1);
            }
                    
            n = write(sockfd, buffer, my_strlen(buffer));
                
            if (n < 0) 
            {
                my_str("Write Error");
                exit(1);
            }        
            
            if(my_strncmp(buffer, "/exit", 5) == 0) 
            {
                 my_str("Disconnecting from server.");
                 break;
            }
                    
            for(i = 0; i < 256; i++)
            {
                buffer[i] = '\0';
            } 
        }
        
        else   
        {       
            n = read(sockfd, buffer, 255);
                
            if (n < 0) 
            {
                my_str("Read Error");
                exit(1);
            }
                    
            my_str(buffer);
            
            for(i = 0; i < 256; i++)
            {
                buffer[i] = '\0';
            } 
        }
        for(i = 0; i < 256; i++)
        {
            buffer[i] = '\0';
        } 
    }    
    
    close(sockfd);
    
    return 0;
}
