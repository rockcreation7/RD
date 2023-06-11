#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "WalletList.h"

bool isRunning = true;

void handleSignal(int signal);

int main()
{
  /*   WalletList walletList;

    // Use the walletList object and its member functions
    walletList.addWallet("Alice", 100);
    walletList.addWallet("Bob", 50);
    walletList.addWallet("Charlie", 200);

    int aliceBalance = walletList.getBalance("Alice");

    walletList.printAllWallets(); */

    int serverSocket;
    struct sockaddr_in serverAddress, clientAddress;
    char buffer[1024];

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Set up server address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8888);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "Failed to bind socket." << std::endl;
        return 1;
    }

    socklen_t clientAddressLength = sizeof(clientAddress);

    while (isRunning)
    {
        // Receive data from client
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddress, &clientAddressLength);

        // Print received data
        std::cout << "Received: " << buffer << std::endl;

        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);
        int clientPort = ntohs(clientAddress.sin_port);
        printf("Client address: %s:%d\n", clientIP, clientPort);

        // Echo back to client
        sendto(serverSocket, buffer, bytesRead, 0, (struct sockaddr *)&clientAddress, clientAddressLength);
    }

    // Close socket
    close(serverSocket);

    return 0;
}

void handleSignal(int signal)
{
    if (signal == SIGINT)
    {
        std::cout << "Ctrl+C signal received. Exiting..." << std::endl;
        isRunning = false;
    }
}

/*

g++ udp_client.cpp -o udp_client
g++ udp_server.cpp -o udp_server


g++ udp_server.cpp WalletList.cpp -o udp_server

*/