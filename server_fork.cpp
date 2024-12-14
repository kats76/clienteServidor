#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

void handleClient(int clientSock){
  char buffer[1024];
  read(clientSock, buffer, sizeof(buffer));
  std::cout << "Received: " << buffer << "\n";
  close(clientSock);
}

int main() {

  //Crea el socket
  int serverSock = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSock < 0) {
    std::cerr << "Error creating socket.\n";
    return -1;
  }

  //Configurando la direccion en el servidor
  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  if(bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr))<0){
    std::cerr<<"Error al bindiar el socket. \n";
    return -1;
  };


  if(listen(serverSock, 5)<0){
    std::cerr<<"Error al poner el servidor en listening. \n";
    return -1;
  };

  std::cout << "Server listening...\n";

  while(true){

    int clientSocket = accept(serverSock,nullptr,nullptr);
    if(clientSocket<0){
      std::cerr<<"Error en el cliente. \n";
      continue;
    }

    pid_t pid =fork();
    if(pid<0){
      std::cerr<<"Error al crear fork \n";
      close(clientSocket);
    } else if(pid==0){
      close(serverSock);
      handleClient(clientSocket);
      exit(0);
    }else{
      close(clientSocket);
    }
  }


  close(serverSock);
  return 0;
}
