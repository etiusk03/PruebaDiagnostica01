#include <stdio.h>
#include <string.h>

/*
	Alumno: Angel Gonzalez - 30.366.096
	
	Problema 4:
	
	Para un programa en un lenguaje L, dado un cadena C escrito en L, muestre y cuente la
	ocurrencia de la palabra E en C.
	
	Programado en: Lenguaje C
*/

int main() {
    char texto[1000];       
    char objetivo[100];       
    int ocurrencias = 0;  

    printf("Escribir el texto a analizar: ");
    fgets(texto, sizeof(texto), stdin);

    printf("Escribir la palabra a contar: ");
    scanf("%s", objetivo);

    char *ubicacion = texto;

    while ((ubicacion = strstr(ubicacion, objetivo)) != NULL) {
        printf("Coincidencia localizada en la posicion: %ld\n", ubicacion - texto);
        ocurrencias++;
        ubicacion += strlen(objetivo);
    }

    printf("\nLa palabra '%s' se encontro %d veces en el texto.\n", objetivo, ocurrencias);

    return 0;
}
