#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Vincula la biblioteca de sockets de Windows

int main() {
    WSADATA wsaData;
    int iResult;

    // Inicializar WinSock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("Error al iniciar WSAStartup: %d\n", iResult);
        return 1;
    }

    // Crear un socket
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        printf("Error al crear el socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Configurar la dirección del servidor
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    // Enlazar el socket
    if (bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Error al hacer bind: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Escuchar conexiones
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Error al escuchar: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    printf("Esperando conexiones...\n");

    // Aceptar conexiones
    SOCKET clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        printf("Error al aceptar conexión: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    printf("Cliente conectado\n");

    // Enviar y recibir datos (simple ejemplo de envío de mensaje)
    const char* msg = "Hola desde el servidor!";
    send(clientSocket, msg, (int)strlen(msg), 0);

    // Cerrar sockets
    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();

    return 0;
}
