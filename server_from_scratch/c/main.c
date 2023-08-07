#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(8080);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(server_fd, (struct sockaddr*) &server, sizeof(server));
  listen(server_fd, 128);
  printf( "Server Listen Started ! \n" );
  for (;;) {
    int client_fd = accept(server_fd, NULL, NULL);
    printf( " Request Accepted \n" );
    char response[] = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\nConnection: close\r\n\r\nHello, world!";
    for (int sent = 0; sent < sizeof(response); sent += send(client_fd, response+sent, sizeof(response)-sent, 0));
    close(client_fd);
  }
  return 0;
}

// https://jameshfisher.com/2016/12/20/http-hello-world/