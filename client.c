#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#define PORT 3000


int main(void) {
    // printf("%s\n", "samagra");

    int sock = 0;
   struct sockaddr_in serv_addr;
    sock = socket(AF_INET,SOCK_STREAM,0); // returns a socket file descripter and we store it in socket file descriptor //

//    domain
//    type of socket
//    protocol -> it will decide from type of socket as we have passed 0

     if(sock<0){
         printf("\n Socket creation error \n");
         exit(1);
     }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);

    if(connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
         printf("\n Connection Failed \n");
         exit(1);
    }
   
    char message_from_client[1024] = {0};
    char message_from_server[1024] = {0};

   printf(" -> ");
   scanf(" %[^\n]s",message_from_client);

   while(strcmp(message_from_client,"bye")!=0){

      send(sock,message_from_client,1024,0); // last argument is the flag // 
      memset(message_from_client,0,1024);


      read(sock,message_from_server,1024);
      printf("Recieved from server: %s",message_from_server);
      memset(message_from_server,0,1024);
     
   
      
      printf("\n -> ");
      scanf(" %[^\n]s",message_from_client);
   
   }


   close(sock);


    return 0;

   


}