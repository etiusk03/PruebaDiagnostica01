#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_EXPR 1000

/*
	Alumno: Angel Gonzalez - 30.366.096
	
	Problema 3:
	
	implemente la evaluación de expresiones aritméticas considerando los operadores +,-,*,/ y los
	operandos pueden ser ingresados en notación científica (125E25,5E-8 para denotar 12x1025 , 5x10-8
	respectivamente), la entrada al programa será una cadena de caracteres con la expresión, ejemplo
	de expresión a evaluar: (125E10 – 1e15)/5E-85*15.
	
	Programado en: Lenguaje C
*/


int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


double aplicar_operador(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}


double leer_numero(const char* expr, int* i) {
    char numero[100];
    int j = 0;
    
    while (isdigit(expr[*i]) || expr[*i] == '.' || expr[*i] == 'e' || expr[*i] == 'E' || 
           (expr[*i] == '-' && (expr[*i-1] == 'e' || expr[*i-1] == 'E')) || 
           (expr[*i] == '+' && (expr[*i-1] == 'e' || expr[*i-1] == 'E'))) {
        numero[j++] = expr[*i];
        (*i)++;
    }

    numero[j] = '\0';
    return strtod(numero, NULL);
}

double evaluar(const char* expr) {
    double valores[MAX_EXPR];
    char operadores[MAX_EXPR];
    int top_valores = -1, top_operadores = -1;
    int i = 0;

    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (isdigit(expr[i]) || expr[i] == '.' || expr[i] == 'e' || expr[i] == 'E' ||
            ((expr[i] == '+' || expr[i] == '-') && (i == 0 || expr[i - 1] == '('))) {
            double num = leer_numero(expr, &i);
            valores[++top_valores] = num;
        }

        else if (expr[i] == '(') {
            operadores[++top_operadores] = expr[i];
            i++;
        }

        else if (expr[i] == ')') {
            while (top_operadores != -1 && operadores[top_operadores] != '(') {
                char op = operadores[top_operadores--];
                double b = valores[top_valores--];
                double a = valores[top_valores--];
                valores[++top_valores] = aplicar_operador(a, b, op);
            }
            top_operadores--; 
            i++;
        }

        else if (strchr("+-*/", expr[i])) {
            while (top_operadores != -1 && precedencia(operadores[top_operadores]) >= precedencia(expr[i])) {
                char op = operadores[top_operadores--];
                double b = valores[top_valores--];
                double a = valores[top_valores--];
                valores[++top_valores] = aplicar_operador(a, b, op);
            }
            operadores[++top_operadores] = expr[i];
            i++;
        }
        else {
            printf("Carácter inválido: %c\n", expr[i]);
            return 0;
        }
    }


    while (top_operadores != -1) {
        char op = operadores[top_operadores--];
        double b = valores[top_valores--];
        double a = valores[top_valores--];
        valores[++top_valores] = aplicar_operador(a, b, op);
    }

    return valores[top_valores];
}


int main() {
    char expresion[MAX_EXPR];
    printf("Ingrese la expresión a evaluar: ");
    fgets(expresion, sizeof(expresion), stdin);
    expresion[strcspn(expresion, "\n")] = '\0';

    double resultado = evaluar(expresion);
    printf("Resultado: %.10e\n", resultado);

    return 0;
}
