//SERVER
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#define PORT 12000
#define MAX_SIZE 1024

using namespace std;

int main()
{
	cout << "Starting..." << endl;
	
	// Two socket descriptors which are just integer numbers used to access a socket
        int sock_descriptor, conn_desc;

        // Two socket address structures - One for the server itself and the other for client
        struct sockaddr_in serv_addr, client_addr;

        // Buffer to store data read from client
        char buff[MAX_SIZE];

        // Create socket of domain - Internet (IP) address, type - Stream based (TCP) and protocol unspecified
        // since it is only useful when underlying stack allows more than one protocol and we are choosing one.
        // 0 means choose the default protocol.
        sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	int iSetOption = 1;
	setsockopt(sock_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption,sizeof(iSetOption));

        // A valid descriptor is always a positive value
        if(sock_descriptor < 0)
	  cout << "Failed creating socket" << endl;

        // Initialize the server address struct to zero
        bzero((char *)&serv_addr, sizeof(serv_addr));

        // Fill server's address family
        serv_addr.sin_family = AF_INET;

        // Server should allow connections from any ip address
        serv_addr.sin_addr.s_addr = INADDR_ANY;

        // 16 bit port number on which server listens
        // The function htons (host to network short) ensures that an integer is interpretted
        // correctly (whether little endian or big endian) even if client and server have different architectures
        serv_addr.sin_port = htons(PORT);
 
	
        // Attach the server socket to a port. This is required only for server since we enforce
        // that it does not select a port randomly on it's own, rather it uses the port specified
        // in serv_addr struct.
        if (bind(sock_descriptor, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        	cout << "Failed to Bind" << endl;
       
        // Server should start listening - This enables the program to halt on accept call (coming next)
        // and wait until a client connects. Also it specifies the size of pending connection requests queue
        // i.e. in this case it is 5 which means 5 clients connection requests will be held pending while
        // the server is already processing another connection request.
        listen(sock_descriptor, 5);
 
        cout << "Waiting for Connection..." << endl;
        int size = sizeof(client_addr);

        // Server blocks on this call until a client tries to establish connection.
        // When a connection is established, it returns a 'connected socket descriptor' different
        // from the one created earlier.
	while(1)
	{
	    conn_desc = accept(sock_descriptor, (struct sockaddr *)&client_addr, (socklen_t *) &size);         
	    if (conn_desc == -1)
		    cout << "Failed Accepting Connection..." << endl;
	    else
		    cout << "Connected to Client!" << endl;

	    while (1)
	    {
		// The new descriptor can be simply read from / written up just like a normal file descriptor
		if ( read(conn_desc, buff, sizeof(buff)-1) > 0)
		{
			cout << "Received:" ;
			int rcvlength;
			for (rcvlength = 0 ; rcvlength < sizeof(buff) ; rcvlength++)
			{
			  if (buff[rcvlength] == '\n')
			  {
			    break;
			  }
			    cout << buff[rcvlength];
			}
			    send(conn_desc,buff, rcvlength,0); //echo back to client
			    cout << endl;
			    
			    //*********
			    //PROCESS buff HERE!!!!!!
			    //*********
		}
		else
		{
		  cout << "Client Closed Connection, Closing Socket..." << endl;
		  break;
		}
	    }
	    close(conn_desc);
	}
        close(sock_descriptor); 
	return 0;
}
