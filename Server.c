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
   int server_fd = 0;

   struct sockaddr_in server_address,client_address;
   server_fd = socket(AF_INET,SOCK_STREAM,0); // returns a socket file descripter and we store it in socket file descriptor //

//    domain
//    type of socket
//    protocol -> it will decide from type of socket as we have passed 0

     if(server_fd<0){
         printf("\n Socket creation error \n");
         exit(1);
     }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address))<0){
         printf("\n Bind Failed \n");
         exit(1);
    }
   
    if(listen(server_fd, 3)<0){
           printf("\n Listen Failed \n");
           exit(1);
    }
 
    int addrlen;

    int new_socket = accept(server_fd,(struct sockaddr *)&client_address,(socklen_t *)&addrlen);


    if(new_socket<0){
          printf("\nAccept Failed \n");
           exit(1);
    }else{
        printf("connected to client with Address %s\n",inet_ntoa(client_address.sin_addr));
    }

   char message_from_client[1024] = {0};
   char message_from_server[1024] = {0};

   while(1){
      read(new_socket,message_from_client,1024);
      if(strlen(message_from_client)==0){
        break;
      }
      printf("from connected user: %s",message_from_client);
      memset(message_from_client,0,1024);
      printf("\n -> ");
      scanf(" %[^\n]s",message_from_server);
      send(new_socket,message_from_server,1024,0); // last argument is the flag // 
     memset(message_from_server,0,1024);
   }


   close(server_fd);


    return 0;

   


}