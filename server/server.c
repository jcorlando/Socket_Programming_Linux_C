#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include<string.h>	//strlen
#include<arpa/inet.h>	//inet_addr


int main()
{
  int sock, clientsock, mlen, addrsize;
	struct sockaddr_in addr;
	char ch, buf[80];
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sock == -1)
	{
		perror("opening socket");
		exit(-1);
	}

	
	// Bind a name to the socket. Since the server will bind with
	// any client, the machine address is zero or INADDR_ANY.
	
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5011);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	
	if(bind(sock, &addr, sizeof(struct sockaddr_in)) == -1)
	{
		perror("on bind");
		exit(-1);
	}

	
	if(listen(sock, 1) == -1)  // make socket available
	{
		perror("on listen");
		exit(-1);
	}
	
	
	// Wait for a client to connect. When this happens, 
	// print out a message.
	
	
	addrsize = sizeof(struct sockaddr_in);
	clientsock = accept(sock, &addr, &addrsize);
	if(clientsock == -1)
	{
		perror("on accept");
		exit(-1);
	}
	
	printf("\nconnection made with client %s\n\n", inet_ntoa(addr.sin_addr));



	// Receive and print a client message where a null character terminates.
	// Note that a single receieve may not work in some cases, but is OK for
	// a simple example. 
	
	mlen = recv(clientsock, buf, 80, 0);

	printf("The Message is : %.*s\n\n", mlen, buf);
	
	
	// Reverse String
	char str[mlen];
	int i, j, len;
	for(i = 0; i < mlen; i++) { str[i] = buf[i]; }
	char RevStr[mlen];
	j = 0;
	len = strlen(str);
	for (i = mlen - 1; i >= 0; i--)
	{
		RevStr[j++] = buf[i];
	}
	RevStr[i] = '\0';
	printf("The reversed string is : %s\n\n", RevStr);
  // Reverse String

	if( send(clientsock, RevStr, strlen(RevStr), 0) < 0)
	{
		perror("Reverse String Send Failed");
		exit(-1);
	}
	else
	{
		printf("Reverse String Successfully Sent Back to Client\n\n");
	}

	printf("Server - all messages read - connection being closed\n\n");

	// Close the client socket and also the server socket
	
	close(clientsock);
	close(sock);

	return 0;
}

