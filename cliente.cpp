#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int clienteSock = socket(AF_INET, SOCK_STREAM, 0);
    if (clienteSock < 0) {
        std::cerr << "Error creando el socket.\n";
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    if (inet_pton(AF_INET, "192.168.85.83", &serverAddr.sin_addr) <= 0) {
        std::cerr << "Dirección IP inválida o no soportada.\n";
        return -1;
    }

    if (connect(clienteSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error en la conexión con el servidor.\n";
        return -1;
    }

    const char* message = "hello, server!";
    std::cout << "Mensaje enviado.\n";
    send(clienteSock, message, strlen(message), 0);

    close(clienteSock);
    return 0;
}

