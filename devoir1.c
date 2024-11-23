#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>
int comptprincipal  = 0,comptsecondaire = 0;
int i =1;
sem_t sem;

void *fnthead(void *arg)
{
	int n =	*((int*)arg);
	
	while(1){
		sem_wait(&sem);
		if(n<i){
		    i=1;
		}
		printf("Thread  %d\n",i++);
		sem_post(&sem);
	}
	
	pthread_exit(NULL);

}


int main(int argc ,char* argv[])
{	

	if(argc<2){
		printf("Erreur : arguments insuffisants\n");
		printf("Usage: %s <number_of_threads>\n",argv[0]);
		exit(-1);
	}
	int n =atoi(argv[1]);

	if(n<=0){
		printf("Le nombre de threads doit être un nombre non null et positif.\n");
		exit(-1);
	}

	pthread_t th[n];
	int resultat;
	 resultat = sem_init(&sem,0,1);

	if(resultat == -1){
		perror ("Erreur d'initialisation du semaphoresecondaire\n");
		return 0;
	}


	for(int j =1;j<=n;j++){
		
		resultat = pthread_create (th+j,NULL,fnthead,&n);
		
		if(resultat == -1){
			perror ("Erreur de lancement du thread\n");
			return 0;
		}
		else{
			printf("thread %d est creer \n",j);
		}
	}
	for (int j =1;j<=n;j++){
		pthread_join(th[j],NULL);
	}
	sem_destroy(&sem);
	return 0;
}