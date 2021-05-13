#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>	//strlen
#include <arpa/inet.h>	//inet_addr

int main(int argc, char *argv[])
{
	
	if (argc < 3)
  {
		fprintf(stderr,"Usage: %s [hostname] [port]\n", argv[0]);
    return(1);
  }

	char *ipaddress = argv[1];
	int port_number = atoi(argv[2]);

	int sock, mlen;
	struct sockaddr_in server;
	char message[40], buf[80];
	printf("\nEnter a string to send to a server and be reversed: ");
	fgets(message, sizeof message, stdin);
	// removes newline character from end of string
	message[strcspn(message, "\n")] = 0;
	// removes newline character from end of string
	printf("\nThe orginal string is  : %s\n", message);
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	
	server.sin_addr.s_addr = inet_addr( ipaddress );
	server.sin_family = AF_INET;
	server.sin_port = htons( port_number );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
		
	puts("\nConnected\n");
		
	//Send some data
	if( send(sock , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Sent\n");

	// Receieve response from server
	mlen = recv(sock, buf, 80, 0);
	printf("The Message returned from the server is : %.*s\n\n", mlen, buf);

	close(sock);

  return 0;
}


