#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*
	Alumno: Angel Gonzalez - 30.366.096
	
	Problema 1:
	
	Dado una cadena C, valide si C se encuentra en notación FEN (Forsyth-Edwards Notation),
	Forsyth–Edwards Notation. FEN es un sistema estándar para describir posiciones específicas en
	partidas de ajedrez, permitiendo reiniciar el juego desde una posición dada. Desarrollado
	inicialmente por David Forsyth y ampliado por Steven J. Edwards, FEN se utiliza en la Notación
	de Juego Portátil para definir posiciones iniciales distintas a la estándar
	
	Programado en: Lenguaje C
*/

bool fila_valida(const char *fila) {
    int suma = 0;
    while (*fila) {
        if (isdigit(*fila)) {
            suma += *fila - '0';
        } else if (strchr("rnbqkpRNBQKP", *fila)) {
            suma += 1;
        } else {
            return false;
        }
        fila++;
    }
    return suma == 8;
}

bool validar_fen(const char *fen) {
    char copia[200];
    strncpy(copia, fen, sizeof(copia) - 1);
    copia[sizeof(copia) - 1] = '\0';

    char *campos[6];
    int i = 0;

    char *token = strtok(copia, " ");
    while (token && i < 6) {
        campos[i++] = token;
        token = strtok(NULL, " ");
    }

    if (i != 6) return false;

    char *fila = strtok(campos[0], "/");
    int filas = 0;
    while (fila) {
        if (!fila_valida(fila)) return false;
        filas++;
        fila = strtok(NULL, "/");
    }
    if (filas != 8) return false;


    if (strcmp(campos[1], "w") != 0 && strcmp(campos[1], "b") != 0) return false;

    return true;  
}

int main() {
    char entrada[200];

    printf("Ingrese una cadena en notacion FEN:\n");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = 0;

    if (validar_fen(entrada)) {
        printf("La cadena ES una notacion FEN valida.\n");
    } else {
        printf("La cadena NO es una notacion FEN valida.\n");
    }

    return 0;
}
