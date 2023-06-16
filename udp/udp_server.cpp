#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "WalletList.h"

bool isRunning = true;

void handle_signal(int signal);
int format_response(char *buffer, int balance, int amount, char operation, char userId[]);

int main()
{
    /*   WalletList walletList;

      // Use the walletList object and its member functions
      walletList.addWallet("Alice", 100);
      walletList.addWallet("Bob", 50);
      walletList.addWallet("Charlie", 200);

      int aliceBalance = walletList.getBalance("Alice");

      walletList.printAllWallets(); */
    WalletList walletList;
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
        char userId[20];
        char operation;
        int resp_size;
        // std::string message(buffer, bytesRead);
        // std::string userId, operation;
        int amount;

        // std::string input = "112233 + 10";
        std::sscanf(buffer, "%s %s %d", &userId, &operation, &amount);
        // userId = buffer;

        switch (operation)
        {
        case '?':
            std::cout << "User ID Balance: " << walletList.getBalance(userId) << std::endl;
            resp_size = format_response(buffer, walletList.getBalance(userId), 0, operation, userId);
            break;
        case '+':
            std::cout << "User ID: " << userId << ", Amount: " << amount << ", operation: " << operation << std::endl;
            walletList.addWallet(userId, amount);
            resp_size = format_response(buffer, walletList.getBalance(userId), amount, operation, userId);
            break;
        case '-':
            std::cout << "User ID: " << userId << ", Amount: " << amount << ", operation: " << operation << std::endl;
            walletList.addWallet(userId, -amount);
            resp_size = format_response(buffer, walletList.getBalance(userId), amount, operation, userId);
            break;
        default:
            std::cout << "User ID: " << userId << ", Amount: " << amount << ", operation: " << operation << std::endl;
            // std::snprintf(buffer, sizeof(buffer), "success balance %d operation %c amount %d user %s ", walletList.getBalance(userId), operation, amount, userId);
            resp_size = format_response(buffer, walletList.getBalance(userId), amount, operation, userId);
            std::cout << "Invalid operation" << std::endl;
        }

        std::cout << "debug " << buffer << std::endl;

        /*
            // Process the operation
            if (operation[0] == *"+")
            {
                std::cout << "User ID: " << userId << ", Amount: " << amount << ", operation: " << operation << std::endl;
                walletList.addWallet(userId, 100);
                // Process addition logic here
            }
            else if (operation[0] == *"-")
            {
                std::cout << "User ID: " << userId << ", Amount: " << amount << ", operation: " << operation << std::endl;
                // Process subtraction logic here
            }
            else
            {
                std::cout << "User ID: " << userId << ", Amount: " << amount << ", operation: " << operation << std::endl;
                std::cout << "Invalid operation" << std::endl;
            }
        */

        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);
        int clientPort = ntohs(clientAddress.sin_port);
        printf("Client address: %s:%d\n", clientIP, clientPort);

        // Echo back to client
        sendto(serverSocket, buffer, resp_size, 0, (struct sockaddr *)&clientAddress, clientAddressLength);
    }

    // Close socket
    close(serverSocket);

    return 0;
}

void handle_signal(int signal)
{
    if (signal == SIGINT)
    {
        std::cout << "Ctrl+C signal received. Exiting..." << std::endl;
        isRunning = false;
    }
}

int format_response(char *buffer, int balance, int amount, char operation, char userId[])
{
    return std::snprintf(buffer, 1024, "success balance %d operation %c amount %d user %s ", balance, operation, amount, userId);
}

/*

g++ udp_client.cpp -o udp_client
./udp_client

g++ udp_server.cpp -o udp_server


g++ udp_server.cpp WalletList.cpp -o udp_server
./udp_server

112233 + 10

*/