#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    

    


    while (true) {
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

        std::string mensaje;

        std::cout << "Escribe un mensaje (o 'salir' para terminar): ";
        std::getline(std::cin, mensaje);

        // Salir si el usuario escribe "salir"
        if (mensaje == "salir") {
            std::cout << "Conexión terminada.\n";
            break;
        }

        // Enviar el mensaje al servidor
        ssize_t bytes_sent = send(clienteSock, mensaje.c_str(), mensaje.length(), 0);
        if (bytes_sent < 0) {
            std::cerr << "Error al enviar el mensaje.\n";
            break; // Salir del bucle si hubo un error al enviar el mensaje
        }

        std::cout << "Mensaje enviado.\n";
    }

    return 0;
}

