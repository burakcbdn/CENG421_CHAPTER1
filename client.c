#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]) {
    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    char buffer[256] = "";
    struct sockaddr_in simpleServer;
    if (3 != argc) {
        fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
        exit(1);
    }
    /* create a streaming socket */
    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    } else {
        fprintf(stderr, "Socket created!\n");
    }



    /* retrieve the port number for connecting */
    simplePort = atoi(argv[2]);


    /* set up the address structure */
    /* use the IP address argument for the server address */
    bzero(&simpleServer, sizeof(simpleServer));


    simpleServer.sin_family = AF_INET;


    inet_addr(argv[2]);


    simpleServer.sin_port = htons(simplePort);




    /* connect to the address and port with our socket */
    returnStatus = connect(simpleSocket,
                           (struct sockaddr *)&simpleServer,
                           sizeof(simpleServer));

    
    if (returnStatus == 0) {
        printf("\n== REQUEST DATA==\n");
        printf("Socket address: %d\n", simpleServer.sin_addr.s_addr);
        printf("Address type: %hhu\n", simpleServer.sin_family);
        printf("Port: %hu\n", simpleServer.sin_port);
        printf("Request length: %hhu\n", simpleServer.sin_len);
        printf("== == == == == == == == ==\n");
    } else {
        fprintf(stderr, "Could not connect to address!\n");
        close(simpleSocket);
        exit(1);
    }
    /* get the message from the server */
    returnStatus = read(simpleSocket, buffer, sizeof(buffer));
    if (returnStatus > 0) {
        printf("\nRESPONSE MESSAGE\n");
        printf("%d: %s", returnStatus, buffer);

    } else {
        fprintf(stderr, "Return Status = % d \n", returnStatus);
    }
    close(simpleSocket);
    return 0;
}