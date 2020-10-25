#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

//Percorre a linha de comando digitada pelo usuario e retorna a quantidade de virgulas.
int Contador_Virgulas(char comando[512]){
	int i, countv = 0;
	
	for(i=0; i<strlen(comando); i++){
		if(comando[i] == ','){
			countv++;
		}
	}
	return countv;
}

//Funçao que recebe o comando com virgulas e retorna os comandos separados
char **Separador_Comandos(char comando[512]){
	char *comandoToken, **comandos;
	int num,j=0,i=0, countc, *p_virgulas;
	
	strcat(comando,",");
	
	countc = Contador_Virgulas(comando);
	
	p_virgulas = (int *) malloc((countc+1) * sizeof(int));
	if(p_virgulas==NULL){
		printf("Erro de alocação!");
		exit(1);
	}
   
	for(i=0; i<strlen(comando); i++){//Estrutura de repetição que armazena o posição das virgulas no vetor comando
		if(comando[i] == ','){
			p_virgulas[j] = i;
			j++;
		}
	}
	p_virgulas[countc] = strlen(comando);
	
	comandos = (char **) malloc((countc+1) * sizeof(char*));
	if(comandos==NULL){
		printf("Erro de alocação!");
		exit(1);
	}
	
	num = p_virgulas[0];
	for (i=0; i < (countc+1); i++){
   		comandos[i] = (char *) malloc (num * sizeof(char));
   		if(comandos[i]==NULL){
			printf("Erro de alocação!");
			exit(1);
		}
   		num = p_virgulas[i+1] - p_virgulas[i] - 1;
    }
    
	comandoToken = (char *) malloc((countc+1) * sizeof(char*)); 
	if(comandoToken==NULL){
		printf("Erro de alocação!");
		exit(1);
	}
	
	i=0;
	comandoToken = strtok(comando, ",");//separaçao da string comando
	strcpy(comandos[i],comandoToken);
	while(comandoToken != NULL){
		if(i=countc){
			strcpy(comandos[i],comandoToken);
			puts(comandos[i]);
			comandoToken = strtok(NULL, ",");
			i++;
		}
	}
	
	free(comandoToken);
	
	return comandos;
}

//Funçao q libera os vetores alocados
void Libera_Alocacao(char comando[512], char** comandos){
	int i, countc;
  
	countc = Contador_Virgulas(comando);
  
	for(i = 0; i < countc; i++){
		free(comandos[i]);	
	}
  	free(comandos);
}

int main(){
	int i, j, countc;
	char comando[512],**comandos;
	
	while(i==0){
		printf("Digite o comando:\n");
		fflush(stdin);
		gets(comando);
		countc = Contador_Virgulas(comando)+1;
		comandos = Separador_Comandos(comando);
		for(j=0;j<countc+1;j++){
			if(strcmp(comandos[j],"quit")==0){
				i=1;
			}
		}
	}

	Libera_Alocacao(comando, comandos);
	return 0;
}
