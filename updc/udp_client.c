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
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failed to create socket");
        return 1;
    }

    // Set up server address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address

    while (1) {
        // Read input from user
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        // Send data to server
        ssize_t bytesSent = sendto(clientSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

        // Receive response from server
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytesRead = recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, NULL, NULL);

        // Print server response
        printf("Server response: %s\n", buffer);
    }

    // Close socket
    close(clientSocket);

    return 0;
}
