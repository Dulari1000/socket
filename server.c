#include	"sock.h"


int main(int argc, char **argv){

        int srvfd, connfd;
        char buffer[255];
	socklen_t clilen;
	pid_t	childpid;


        struct sockaddr_in servsock;


        if ((srvfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
                printf("Socket creation failed\n");
                exit(1);
        }

        bzero(&servsock,sizeof(servsock));

        servsock.sin_family = AF_INET;
        servsock.sin_port = htons(5002);
        servsock.sin_addr.s_addr = inet_addr(argv[1]);

        if ((bind(srvfd, (struct sockaddr*)&servsock, sizeof(servsock))) < 0){
                printf("bind failed\n");
                exit(1);
        }

        if(listen(srvfd,5) < 0){
                printf("listen failed\n");
                exit(1);
        }


        for( ;; ){

		connfd = accept(srvfd,NULL,NULL);

		if((childpid = fork()) == 0){
		
			close(srvfd);

			for ( ; ; ){

				bzero(buffer,255);
				read(connfd, buffer, 255);

				write(connfd, buffer, strlen(buffer));
			}
		
		exit(0);
		}

		close(connfd);

        }
        return 0;

}

