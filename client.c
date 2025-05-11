#include "sock.h"

int main(int argc, char **argv){

        int     srvfd, a;
        char    buffer[255];

        struct sockaddr_in      servsock;

        if ((srvfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
                printf("Socket creation failed\n");
                exit(1);
        }

        bzero(&servsock, sizeof(servsock));

        servsock.sin_family = AF_INET;
        servsock.sin_port   = htons(5002);
        servsock.sin_addr.s_addr = inet_addr(argv[1]);

        a = connect(srvfd, (struct sockaddr*)&servsock,  sizeof(servsock));

        if(a == 0){
                printf("connection successfull");
        }
        else{
                printf("connect error");
                exit(1);
        }

        for( ;; ){

         bzero(buffer,255);

         printf("\nEnter the mesege: ");
         fgets(buffer, 255, stdin);

         write(srvfd, buffer, strlen(buffer));

         bzero(buffer,255);

         read(srvfd, buffer, 255);

         //display buffer
         printf("server: %s\n", buffer);

        }


}

