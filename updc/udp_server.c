#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int serverSocket;
    struct sockaddr_in serverAddress, clientAddress;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failed to create socket");
        return 1;
    }

    // Set up server address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Failed to bind socket");
        return 1;
    }

    socklen_t clientAddressLength = sizeof(clientAddress);

    while (1) {
        // Receive data from client
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytesRead = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddress, &clientAddressLength);

        // Print received data
        printf("Received: %s\n", buffer);

        // Echo back to client
        sendto(serverSocket, buffer, bytesRead, 0, (struct sockaddr *)&clientAddress, clientAddressLength);
    }

    // Close socket
    close(serverSocket);

    return 0;
}

/*

gcc udp_server.c -o udp_server
./udp_server

gcc udp_client.c -o udp_client
./udp_client

*/