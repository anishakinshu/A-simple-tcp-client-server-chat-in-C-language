
#include<stdio.h>
#include<sys/types.h>//socket
#include<sys/socket.h>//socket
#include<string.h>//memset
#include<stdlib.h>//sizeof
#include<netinet/in.h>//INADDR_ANY
#include<arpa/inet.h>

#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define MAXSZ 100
int main()
{
 int sockfd;//to create socket

 struct sockaddr_in serverAddress;//client will connect on this

 int n;
 char msg1[MAXSZ];
 char msg2[MAXSZ];

 //create socket
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 //initialize the socket addresses
 //memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=inet_addr(SERVER_IP);
 serverAddress.sin_port=htons(8889);

 //client  connect to server on port
 connect(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));
 //send to sever and receive from server
 while(1)
 {
  printf("\nEnter message to send to server:\n");
  //fgets(msg1,MAXSZ,stdin);
   gets(msg1);
  

  //n=strlen(msg1)+1;
  send(sockfd,msg1,strlen(msg1),0);

  n=recv(sockfd,msg2,MAXSZ,0);
  msg2[n] = '\0';
  printf("Receive message from  server::%s\n",msg2);
 }
close(sockfd);
 return 0;
}
