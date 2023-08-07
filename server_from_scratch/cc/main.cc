#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <iostream>
#include <sstream>

void log(const std::string &message)
{
    std::cout << message << std::endl;
}

void exitWithError(const std::string &errorMessage)
{
    log("ERROR: " + errorMessage);
    exit(1);
}

int main()
{
    const int BUFFER_SIZE = 30720;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    listen(server_fd, 128);
    printf("Server Listen Started ! \n");
    int bytesReceived;
    while (true)
    {
        int client_fd = accept(server_fd, NULL, NULL);
        printf(" Request Accepted \n");
        char buffer[BUFFER_SIZE] = {0};
        bytesReceived = read(client_fd, buffer, BUFFER_SIZE);
        if (bytesReceived < 0)
        {
            exitWithError("Failed to read bytes from client socket connection");
        }
        printf("%s\n", buffer); 
        char response[] = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\nConnection: close\r\n\r\nHello, world!";
        for (int sent = 0; sent < sizeof(response); sent += send(client_fd, response + sent, sizeof(response) - sent, 0));
        close(client_fd);
    }
    return 0;
}


// https://jameshfisher.com/2016/12/20/http-hello-world/
// https://trungams.github.io/2020-08-23-a-simple-http-server-from-scratch/
// clang++ main.cc -o main
// https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa