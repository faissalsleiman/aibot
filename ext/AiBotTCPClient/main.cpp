#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
//CLIENT

#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 12000
#define MAXSIZE 1024
#define SERVER "127.0.0.1"

using namespace std;

int sendTwoWayTCP (const char * serverIP , int serverPort , string msgToSend); 

int main(int argc, char *argv[])
{
    sendTwoWayTCP("127.0.0.1",12000,"Hello Mister Server\n");
    return 0;
}//End of main


int sendTwoWayTCP (const char * serverIP , int serverPort , string msgToSend)
{
  struct sockaddr_in server_info;
    struct hostent *he;
    int socket_fd,num;
    char buffer[1024];

    char buff[1024];

    if ((he = gethostbyname(serverIP))==NULL) {
        cout << "Cannot get host name" << endl;
	return 0;
    }

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0))== -1) {
        cout << "Socket Failure" << endl;
	return 0;
    }

    memset(&server_info, 0, sizeof(server_info));
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(serverPort);
    server_info.sin_addr = *((struct in_addr *)he->h_addr);
    if (connect(socket_fd, (struct sockaddr *)&server_info, sizeof(struct sockaddr))<0) {
        cout << "Cannection Failure" << endl;
	return 0;
    }

	char *y = new char[msgToSend.length() + 1];
	strcpy(y, msgToSend.c_str());
	  
        if ((send(socket_fd,y, strlen(y),0))== -1) {
                cout << "Failure Sending Message" << endl;
                close(socket_fd);
                return 0;
        }
        else {
                cout << "Message Sent:" << buffer << endl;
		cout << "Receiving Confimation from server..." << endl;
                num = recv(socket_fd, buffer, sizeof(buffer),0);
                if ( num <= 0 )
                {
                        cout << "Either Connection Closed or Error" << endl ;
                        
                }

                buff[num] = '\0';
                cout << "Message Received from Server:" << buffer << endl;
           }
        delete[] y;
    
    close(socket_fd);
    return 1;
}