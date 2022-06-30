#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUMBER_OF_THREADS 100

void *say_hello_thread(void *tid) {
	// Precisamos converter a variável tid que está como ptr para void em ptr para int
	int *iptr = (int *) tid;
	printf("Alo do filho %d\n", *iptr);
	sleep(1);
	printf("Tchau do filho %d\n", *iptr);

	return NULL;
}

void main(void) {
	printf("Alo do pai!\n");
	pthread_t threads[NUMBER_OF_THREADS];
	int status, i;

	for(i = 0; i < NUMBER_OF_THREADS; i++) {
		status = pthread_create(&threads[i], NULL, say_hello_thread, &i);

		if (status != 0) {
			printf("Erro na criacao da thread. Status code: %d \n", status);
			exit(-1);
		}
		// Espera até que a thread criada (threads[i]) tenha finalizado para dar prosseguimento

		pthread_join(threads[i], NULL);
	}

	printf("Tchau do pai!\n");
}
