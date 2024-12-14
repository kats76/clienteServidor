#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
int main() {

  int serverSock = socket(AF_INET, SOCK_STREAM, 0);

  if (serverSock < 0) {
    std::cerr << "Error creating socket.\n";
    return -1;
  }

  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr));

  listen(serverSock, 5);
  std::cout << "Server listening...\n";

  int clientSock = accept(serverSock, nullptr, nullptr);

  char buffer[1024];
  read(clientSock, buffer, sizeof(buffer));
  std::cout << "Received: " << buffer << "\n";
  close(clientSock);
  close(serverSock);
  return 0;
}
