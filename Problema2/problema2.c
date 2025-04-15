#include <stdio.h>

/*
	Alumno: Angel Gonzalez - 30.366.096
	
	Problema 2:
	
	Dado un número entero no negativo n, a) genere los coeficientes del polinomio (x+1)n, 
	muestre elresultado de polinomio y b) muestre por pasos el cálculo para x 
	dado, f(x) = (x+1)n ,según el polinomio generado.
	
	Programado en: Lenguaje C
*/

void generar_coleccion_coeficientes(int n) {
    long long coef[n+1];  


    for (int i = 0; i <= n; i++) {
        coef[i] = 0;
    }
    coef[0] = 1; 


    for (int i = 1; i <= n; i++) {
        for (int j = i; j > 0; j--) {
            coef[j] += coef[j-1]; 
        }
        coef[0] = 1; 
    }


    printf("Coeficientes del polinomio (x+1)^%d: ", n);
    for (int i = 0; i <= n; i++) {
        printf("%lld ", coef[i]);
    }
    printf("\n");
}


void evaluar_polynomial(int n, int x) {
    long long coef[n+1];


    for (int i = 0; i <= n; i++) {
        coef[i] = 0;
    }
    coef[0] = 1;  

 
    for (int i = 1; i <= n; i++) {
        for (int j = i; j > 0; j--) {
            coef[j] += coef[j-1];
        }
        coef[0] = 1;
    }


    long long resultado = coef[n]; 
    printf("Calculo paso a paso para f(x) = (x+1)^%d, donde x = %d:\n", n, x);
    for (int i = n-1; i >= 0; i--) {
        resultado = resultado * x + coef[i];  
        printf("Paso %d: resultado = %lld * %d + %lld = %lld\n", n-i, resultado / x, x, coef[i], resultado);
    }

    printf("Resultado final f(%d) = %lld\n", x, resultado);
}

int main() {
    int n, x;

    printf("Ingrese un numero entero no negativo n: ");
    scanf("%d", &n);

    printf("Ingrese el valor de x: ");
    scanf("%d", &x);

    generar_coleccion_coeficientes(n);

    evaluar_polynomial(n, x);

    return 0;
}
