#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define PORT 37
#define BUFF_SIZE 200
#define FROM_1900_TO_1970 2208988800


int main(int argc, char** argv) {

    unsigned short port;
    struct sockaddr_in server;
    int s;

    if(argc != 3) {
        printf("Format ./client {server} {port}\n");
        exit(EXIT_FAILURE);
    }

    port = htons(atoi(argv[2]));

    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket failure");
        exit(EXIT_FAILURE);
    }
    memset(&server, 0, sizeof(server));
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = port;
    server.sin_family = AF_INET;

    if(sendto(s, "", 0, 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Send To error");
        exit(EXIT_FAILURE);
    }

    int n;
    socklen_t len;
    __uint32_t received_time;
    if((n = recvfrom(s, &received_time, sizeof(received_time), MSG_WAITALL,
                (struct sockaddr*) &server, &len)) < 0) {
        perror("Recvfrom error");
        exit(EXIT_FAILURE);
    }

    received_time = ntohl(received_time);
    time_t time_seconds = (time_t)(received_time - FROM_1900_TO_1970);

    printf("%s\n", ctime(&time_seconds));

    close(s);
    exit(EXIT_SUCCESS);
}