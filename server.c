#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define PORT 37
#define BUFF_SIZE 200
#define FROM_1970_TO_1900 2208988800

int main() {

    printf("Hello, Server is starting!\n");

    int s_fd;
    struct sockaddr_in serv_addr, client_addr;


    if((s_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;

    if(bind(s_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Binding error");
        exit(EXIT_FAILURE);
    }

    socklen_t client_addr_size = sizeof (client_addr);
    char buff[BUFF_SIZE];
    while(1) {
        if(recvfrom(s_fd, buff, BUFF_SIZE - 1, 0,
        (struct sockaddr*) &client_addr,&client_addr_size) < 0) {
            perror("Recvfrom error");
            exit(EXIT_FAILURE);
        }


        time_t raw_time = FROM_1970_TO_1900 + time(NULL);
        __uint32_t time_seconds = __builtin_bswap32(raw_time);

        printf("Sending Time to client!\n");

        if(sendto(s_fd, &time_seconds, sizeof(time_seconds), MSG_CONFIRM, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
            perror("Send To error");
            exit(EXIT_FAILURE);
        }
    }
    close(s_fd);
    return 0;
}
