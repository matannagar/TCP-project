#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
//MYTIMER//
    struct timeval t1, t2;
    double elapsedTime;
//TIMER//
    int sfd = 0, n = 0, b;
    char rbuff[1024];
    char sendbuffer[100];
    char buf[256];
    socklen_t len;

    struct sockaddr_in serv_addr;

    memset(rbuff, '0', sizeof(rbuff));
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = inet_addr("10.0.2.15");

    b = connect(sfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (b == -1) {
        perror("Connect");
        return 1;
    }

    len=sizeof(buf);
    if(getsockopt(sfd, IPPROTO_TCP, TCP_CONGESTION, buf, &len)!=0){
        perror("getsockopt");
        return -1;
    }
    printf("Current: %s\n", buf);

    strcpy(buf, "reno");
    len= strlen(buf);
    if(setsockopt(sfd, IPPROTO_TCP, TCP_CONGESTION, buf, len)!=0){
        perror("setsockopt");
        return -1;
    }
    len = sizeof(buf);
    if(getsockopt(sfd, IPPROTO_TCP, TCP_CONGESTION, buf, &len)!=0){
        perror("getsockopt");
        return -1;
    }
    printf("New: %s\n",buf);
    FILE *fp = fopen("1gb.txt", "rb");
    if (fp == NULL) {
        perror("File");
        return 2;
    }
    //TIMER
    gettimeofday(&t1, NULL);
    //TIMER
    while ((b = fread(sendbuffer, 1, sizeof(sendbuffer), fp)) > 0) {
        send(sfd, sendbuffer, b, 0);
    }
//TIMER
    gettimeofday(&t2, NULL);
    //TIMER
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("It took %f ms to send this file.\n", elapsedTime);
    // printf("FILE WAS SUCCESFULLY SENT!\n");
//TIMER
    fclose(fp);

    return 0;

}
