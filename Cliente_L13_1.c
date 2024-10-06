#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
	int cliente_fd;
	struct sockaddr_in direccion_servidor;
	char buffer[1024] = {0};
	char tipo_conversion[10];
	float temperatura;
	
	if ((cliente_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\nError en la creacion del socket\n");
		return -1;
	}
	
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(8080);
	
	if (inet_pton(AF_INET, "192.168.0.25", &direccion_servidor.sin_addr) <= 0) {
		printf("\nDireccion invalida o no soportada\n");
		return -1;
	}
	
	if (connect(cliente_fd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0) {
		printf("\nConexion fallida\n");
		return -1;
	}
	
	printf("Elija la conversacionn (CtoF o FtoC): ");
	scanf("%s", tipo_conversion);
	printf("Ingrese la temperatura: ");
	scanf("%f", &temperatura);
	
	sprintf(buffer, "%s %f", tipo_conversion, temperatura);
	send(cliente_fd, buffer, strlen(buffer), 0);
	
	read(cliente_fd, buffer, 1024);
	printf("Respuesta del servidor: %s\n", buffer);
	
	close(cliente_fd);
	
	return 0;
}
