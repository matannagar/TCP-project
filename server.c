//
// Created by matanbn on 18/12/2020.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
//MYTIMER//
    struct timeval t1, t2;
    double elapsedTime;
//TIMER//
    int fd =0, confd = 0,b,tot;
    struct sockaddr_in serv_addr;

    char buff[1025];
    int num;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created\n");

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(buff, '0', sizeof(buff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(fd, 10);

    while(1){
        confd = accept(fd, (struct sockaddr*)NULL, NULL);
        if (confd==-1) {
            perror("Accept");
            continue;
        }
        FILE* fp = fopen( "provacopy.txt", "rb");
        tot=0;
        if(fp != NULL){
            //TIMER
            gettimeofday(&t1, NULL);
            //TIMER
            while( (b = recv(confd, buff, 1024,0))> 0 ) {
                tot+=b;
                fwrite(buff, 1, b, fp);
            }

            printf("Received byte: %d\n",tot);
            //TIMER
            gettimeofday(&t2, NULL);
            //TIMER
            elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
            elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
            printf("It took %f ms to receive this file.\n", elapsedTime);
//TIMER
            if (b<0)
                perror("Receiving");

            fclose(fp);
        } else {
            perror("File");
        }
        close(confd);
    }

    return 0;
}
