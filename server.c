#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockID1 = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addrPort1;
    addrPort1.sin_family = AF_INET; // sets IPv4
    addrPort1.sin_addr.s_addr = htonl(INADDR_ANY);
    addrPort1.sin_port = htons(5200);
    //htonl - host to network long, htons - host to network short

    if(bind(sockID1, (struct sockaddr *) &addrPort1, sizeof(addrPort1))==-1) {
        printf("\nBind Failed to Port 5200\n\n");
    }
    else printf("\nBind Success to Port 5200\n\n");

    if(listen(sockID1, 10)) {
        printf("Listen Failed\n\n");
    }
    else printf("Listening...\n\n");

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    int sockID2 = accept(sockID1, (struct sockaddr *) &client_addr, &len);
    printf("Accepted a connection\n");

    char msg[50] = "Hello Worldd";
    int countr, counts;

    while(strcmp(msg,"Close\n")) {
        printf("To Client : ");
        fgets(msg, 50, stdin);
        counts = send(sockID2, msg, 50, 0);
        if(!strcmp(msg,"Close\n")) {
            break;
        }
        printf("From Client : ");
        countr = recv(sockID2, msg, 50, 0);
        printf("%s", msg);
    }

    close(sockID1);
    close(sockID2);

    printf("\nSocket connection Closed\n");

    return 0;
}