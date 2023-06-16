#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[1024];

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Set up server address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8888);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address

    while (1) {
        // Read input from user
        std::cout << "Enter message: ";
        std::cin.getline(buffer, sizeof(buffer));

        // Send data to server
        ssize_t bytesSent = sendto(clientSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

        // Receive response from server
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0, NULL, NULL);

        // Print server response
        std::cout << "Server response: " << buffer << std::endl;
    }

    // Close socket
    close(clientSocket);

    return 0;
}
