#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockID1 = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addrPort1;
    addrPort1.sin_family = AF_INET;
    addrPort1.sin_addr.s_addr = htonl(INADDR_ANY);
    addrPort1.sin_port = htons(5200);

    if(connect(sockID1, (struct sockaddr *) &addrPort1, sizeof(addrPort1))) {
        printf("\nConnect Failed\n\n");
    }
    else printf("\nConnected via Port 5200\n\n");

    char msg[50] = "Hello World";
    int countr, counts;

    while(strcmp(msg,"Close\n")) {
        printf("From Server : ");
        countr = recv(sockID1, msg, 50, 0);
        printf("%s", msg);
        if(!strcmp(msg,"Close\n")) {
            break;
        }
        printf("To Server : ");
        fgets(msg, 50, stdin);
        counts = send(sockID1, msg, 50, 0);
    }

    close(sockID1);
    printf("\nSocket connection Closed\n");

    return 0;
}