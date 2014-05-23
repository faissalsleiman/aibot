#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>

// link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

class tcpClient {
public:
	tcpClient(char* servername);
	bool Start() ;

	// Free the resouces
	void Stop() ;
	
	// Send message to server
	bool Send(char* szMsg) ;

	// Receive message from server
	bool Recv() ;

private:
	char* szServerName;
	SOCKET ConnectSocket;
};
