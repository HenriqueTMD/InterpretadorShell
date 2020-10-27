#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>

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

//Percorre a linha de comando digitada pelo usuario e retorna a quantidade de espaços.
int Contador_Espacos(char comando[512]){
	int i, counte = 0;
	
	for(i=0; i<strlen(comando); i++){
		if(comando[i] == ' '){
			counte++;
		}
	}
	return counte;
}

//Funçao que recebe o comando com virgulas e retorna os comandos separados
char** Separador_Comandos(char comando[512]){
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
   		comandos[i] = (char *) malloc ((num+1) * sizeof(char));
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
		if(i!=countc){
			strcpy(comandos[i],comandoToken);
			comandoToken = strtok(NULL, ",");
			i++;
		}
	}
	
	
	
	free(comandoToken);
	
	return(comandos);
}

char** Tratamento_Comando(char* comando){
	int i=0,j=0, counte, *p_espacos, num;
	char **argv, *comandoToken;
	
	strcat(comando," ");
	
	counte = Contador_Espacos(comando);
	
	p_espacos = (int *) malloc(counte * sizeof(int));
	if(p_espacos==NULL){
		printf("Erro de alocação!");
		exit(1);
	}
   
	for(i=0; i<strlen(comando); i++){
		if(comando[i] == ' '){
			p_espacos[j] = i;
			j++;
		}
	}
	
	argv = (char **) malloc((counte) * sizeof(char*));
	if(argv==NULL){
		printf("Erro de alocação!");
		exit(1);
	}
	
	num = p_espacos[0];
	for (i=0; i < counte; i++){
   		argv[i] = (char *) malloc (num * sizeof(char));
   		if(argv[i]==NULL){
			printf("Erro de alocação!");
			exit(1);
		}
   		num = p_espacos[i+1] - p_espacos[i] - 1;
    }
    
    comandoToken = (char *) malloc((counte+1) * sizeof(char*)); 
	if(comandoToken==NULL){
		printf("Erro de alocação!");
		exit(1);
	}
	
	i=0;
	comandoToken = strtok(comando, " ");//separaçao da string comando
	strcpy(argv[i],comandoToken);
	while(comandoToken != NULL){
		if(i!=counte){
			strcpy(argv[i],comandoToken);
			puts(argv[i]);
			comandoToken = strtok(NULL, " ");
			i++;
		}
	}
	
	return(argv);	
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

void exec(char **comandos){
	
}

int main(){
	int i, j, countc;
	char comando[512],**comandos,**argv, cmd[3];
	pid_t pid;
	
	while(i==0){
		printf("Digite o comando:\n");
		fflush(stdin);
		gets(comando);
		countc = Contador_Virgulas(comando)+1;
		comandos = Separador_Comandos(comando);
		for(j=0;j<countc;j++){
			
			if(strcmp(comandos[j],"quit")==0){
				i=1;
				break;
			}
			argv = Tratamento_Comando(comandos[j]);
			strcpy(cmd,argv[0]);
			
			/*
			if ((pid = fork()) < 0) {     
            	printf("*** ERROR: forking child process failed\n");
            	exit(1);
        	}
        	else if (pid == 0) {          
            	if (execvp("ls", comandos[j]) < 0) {     
            	    printf("*** ERROR: exec failed\n");
            	    exit(1);
            	}
        	} 
        	*/
		}
	}

	Libera_Alocacao(comando, comandos);
	Libera_Alocacao(comandos[j], argv);
	return 0;
}
