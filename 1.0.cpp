#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define n_threads 3
/*
int Create_Thread(char comando[512]){
	pthread_t thread;
	int t;
	
	t = pthread_create (&thread, NULL, comando, NULL);
	if(t){
		printf("Erro: Problema na criação da thread %d\n",t);
		return 1;
	}
	
	return 0;
}
*/
int Contador_Virgulas(char comando[512]){
	int i, countc = 0;
	
	for(i=0; i<strlen(comando); i++){
		if(comando[i] == ','){
			countc++;
		}
	}
	return countc;
}

int Separador_Comandos(char comando[512]){
	int i, j, countv, *p_virgulas, count=0, p1, num;
	char **comandos;
	
	countv = Contador_Virgulas(comando);
	
	p_virgulas = (int *) malloc((countv+1) * sizeof(int));
	
    j=0;
	for(i=0; i<strlen(comando); i++){
		if(comando[i] == ','){
			p_virgulas[j] = i;
			
			j++;
		}
	}
	p_virgulas[countv] = strlen(comando);
	
	comandos = (char **) malloc((countv+1) * sizeof(char*));
	num = p_virgulas[0];
	for (i=0; i < (countv+1); i++){
		printf("%d\n",num);
   		comandos[i] = (char *) malloc (num+1 * sizeof(char));
   		num = p_virgulas[i+1] - p_virgulas[i] - 1;
    }
	
	p1=0;
	for(i=0; i<(countv+1); i++){
		count=0;
		
		for(j=p1; j<p_virgulas[i]; j++){
			
			comandos[i][count] = comando[j];
			count++;
			
		}
		int k = strlen(comandos[i]);
		printf("%c",comandos[i][10]);
		printf("%d\n",k);
		p1 = p_virgulas[i]+1;
		
	}
	
	return 0;
}

int main(){
	int i, t=0, countc=0;
	char comando[512];
	
	printf("digite o comando:\n");
		fflush(stdin);
		gets(comando);
		countc = Separador_Comandos(comando);
	while(t=0){
		
		
		/*
		switch(comando){
			case quit;
				exit(0);
			break;
			
			case 
		}
		*/
	}
	
	
	
	return 0;
}
