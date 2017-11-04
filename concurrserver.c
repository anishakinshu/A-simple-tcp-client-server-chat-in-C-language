#include<stdio.h>
#include<sys/types.h>//socket
#include<sys/socket.h>//socket
#include<string.h>//memset
#include<stdlib.h>//sizeof
#include<netinet/in.h>//INADDR_ANY
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<pthread.h>


void *fun(void* dp){
   int sock = *(int*)dp;
   int n1, i;
   char msgrcv[1024], msgsnd[1024];
   
   while(1){
      n1 = recv(sock, msgrcv, sizeof(msgrcv), 0);
      msgrcv[n1] = '\0';
      printf("received string :%s\n",msgrcv);
      
      send(sock, msgrcv, strlen(msgrcv), 0);
   }
   close(sock);
   
}

int main() {
    int sock, i, j, n, newsock,*new_sock;
    struct sockaddr_in servaddr, clientaddr;
    char msgrcv[1024], msgsnd[1024];
    pid_t pid;

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
           perror("connection failed\n");
           exit(1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8889);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
          perror("not able to bind\n");
          exit(1);
    }
    
    listen(sock, 5);
    
    while(1){
        int len = sizeof(clientaddr);
        newsock = accept(sock, (struct sockaddr*)&clientaddr, &len);

        /*thread is used to handle multiple clients at a time*/
        pthread_t th;
        new_sock = malloc(1);
        *new_sock = newsock;
        pthread_create(&th, NULL, fun, (void*)new_sock);
        
       /*pid = fork();
        
        if(pid < 0){
           perror("process  not created\n");
           exit(1);
        }
        if(pid == 0){
           while(1){
               n = recv(newsock, msgrcv, sizeof(msgrcv), 0);
               msgrcv[n] ='\0';
               printf("message received by client whose ip and port is %s %d\n",inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
               printf("received string is %s\n",msgrcv);
               send(newsock, msgrcv, strlen(msgrcv), 0);
           }
        
        }
        else{
            //waitpid(pid, NULL, 0);
            close(newsock);
        }  
        */
    }
    close(sock);
    return 0;
}
