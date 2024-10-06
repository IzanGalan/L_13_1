#include <stdio.h>
#include <string.h>
#include <ctype.h>  

int es_palindromo(const char *nombre) {
	int len = strlen(nombre);
	for (int i = 0; i < len / 2; i++) {
		if (nombre[i] != nombre[len - i - 1]) {
			return 0; 
		}
	}
	return 1; 
}

void a_mayusculas(char *nombre) {
	for (int i = 0; nombre[i]; i++) {
		nombre[i] = toupper(nombre[i]);
	}
}

int main() {
	char nombre[100];
	
	printf("Introduce tu nombre: ");
	scanf_s("%s", nombre);
	
	
	if (es_palindromo(nombre)) {
		printf("El nombre '%s' es un pali­ndromo.\n", nombre);
	} else {
		printf("El nombre '%s' no es un palindromo.\n", nombre);
	}
	
	
	a_mayusculas(nombre);
	printf("Tu nombre en mayusculas es: %s\n", nombre);
	
	return 0;
}
