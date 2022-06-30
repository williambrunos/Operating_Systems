#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

double factorial(double n) {
	if (n == 0.0) {
		return 1.0;
	} else {
		return n * factorial(n - 1);
	}
}

double geral_term(double x, int i) {
	double geral_term = (pow(-1, i) * pow(x, 2*i + 1)) / factorial(2*i + 1);
	return geral_term;
}

void *termos_negativos(void* x) {
	double* xptr = (double *) x;
	int i;
	// Criando espaço em memória alocado pela thread
	double* negative_sum = (double *) malloc(sizeof(double));
	*negative_sum = 0;

	for (i = 1; i <= 10; i+=2) {
		double g_term = geral_term(*xptr, i);
		*negative_sum += g_term;
	}

	// A thread irá retornar o endereço para o espaço que ela alocou
	// em memória

	return negative_sum;
}

void *termos_positivos(void* x) {
	double* xptr = (double *) x;
	int i;
	// Thread aloca um espaço na memória para seu retorno
	double* positive_sum = (double *) malloc(sizeof(double));
	*positive_sum = 0;

	for (i = 0; i <= 10; i+=2) {
		double g_term = geral_term(*xptr, i);
		*positive_sum += g_term;
	}
	// A thread irá retornar o endereço para o espaço que ela alocou
	// em memória
	
	return positive_sum;
}

void main(void) {
	double x;
	double* negative_sum;
	double* positive_sum;

	printf("Por favor, digite o angulo (x) em graus: ");
	scanf("%lf", &x);
	
	printf("x (degrees) = %lf\n", x);
	// Transforma-se o ângulo x de graus para radianos
	x = x * (M_PI / 180.0);

	printf("x (radians) = %lf\n", x);
	
	pthread_t threads[2];
	
	// A primeira thread cuida da soma dos termos negativos
	pthread_create(&threads[0], NULL, termos_negativos, (void *) &x);
	pthread_join(threads[0], (void *)  &negative_sum);

	// A segunda thread cuida da soma dos termos positivos
	pthread_create(&threads[1], NULL, termos_positivos, (void *) &x);
	pthread_join(threads[1], (void *) &positive_sum);
	
	// Por fim, as somas são unificadas em 'total_sum'
	double total_sum = *positive_sum + *negative_sum;
	printf("Sin(x) = %lf\n", total_sum);
}
