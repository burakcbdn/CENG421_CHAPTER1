#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

const char APRESSMESSAGE[] = "APRESS - For Professionals, By Professionals!\n";
int main(int argc, char *argv[]) {
    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    struct sockaddr_in simpleServer;
    if (2 != argc) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    } else {
        fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for listening */
    simplePort = atoi(argv[1]);
    /* set up the address structure */
    /* use INADDR_ANY to bind to all local addresses */
    bzero(&simpleServer, sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
    simpleServer.sin_port = htons(simplePort);
    /* bind to the address and port with our socket */
    returnStatus = bind(simpleSocket,
                        (struct sockaddr *)&simpleServer,
                        sizeof(simpleServer));
    if (returnStatus == 0) {
        fprintf(stderr, "Bind completed!\n");
    } else {
        fprintf(stderr, "Could not bind to address!\n");
        close(simpleSocket);
        exit(1);
    }
    /* let's listen on the socket for connections */
    returnStatus = listen(simpleSocket, 5);
    if (returnStatus == -1) {
        fprintf(stderr, "Cannot listen on socket!\n");
        close(simpleSocket);
        exit(1);
    }

    while (1) {
        struct sockaddr_in clientName = {0};
        int simpleChildSocket = 0;
        socklen_t clientNameLength = sizeof(clientName);
        /* wait here */

        simpleChildSocket = accept(simpleSocket,
                                   (struct sockaddr *)&clientName,
                                   &clientNameLength);
        if (simpleChildSocket == -1) {
            fprintf(stderr, "Cannot accept connections!\n");
            close(simpleSocket);
            exit(1);
        }
        printf("\n== INCOMING REQUEST DATA ==\n");
        printf("Socket address: %d\n", clientName.sin_addr.s_addr);
        printf("Address type: %hhu\n", clientName.sin_family);
        printf("Port: %hu\n", clientName.sin_port);
        printf("Request length: %hhu\n", clientName.sin_len);
        printf("== == == == == == == == ==\n");

        printf("\nResponse message:\n");
        printf("%lu: %s\n",strlen(APRESSMESSAGE), APRESSMESSAGE);

        printf("Response sent successfully! Closing connection. \n");

        /* handle the new connection request */
        /* write out our message to the client */
        write(simpleChildSocket, APRESSMESSAGE, strlen(APRESSMESSAGE));
        close(simpleChildSocket);
    }
    close(simpleSocket);
    return 0;
}