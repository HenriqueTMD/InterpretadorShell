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

//Percorre a linha de comando digitada pelo usuario e retorna a quantidade de espacos.
int Contador_Espacos(char comando[512]){
	int i, counte = 0;
	
	
	for(i=0; i<strlen(comando); i++){
		if(comando[i] == ' '){
			counte++;
		}
	}
	return counte;
}

//Funcao que recebe o comando com virgulas e retorna os comandos separados
char** Separador_Comandos(char comando[512]){
	char *comandoToken, **comandos;
	int num,j=0,i=0, countc, countcv=0, *p_virgulas;
	
	
	strcat(comando,",");//concatenaçao com uma virgula para melhorar a separacao
	
	countc = Contador_Virgulas(comando);
	
	p_virgulas = (int *) malloc(countc * sizeof(int));//aloca um vetor para armazenar a posiçao das virgulas para alocacao
	if(p_virgulas==NULL){
		printf("Erro de alocacao!");
		exit(1);
	}
   	
	for(i=0; i<strlen(comando); i++){//Estrutura de repeticao que armazena a posicao das virgulas
		if(comando[i] == ','){
			p_virgulas[j] = i;
			j++;
		}

	}
	
	countcv = j;
	for(i=0; i<countc; i++){//Estrutura de repeticao que armazena a posicao das virgulas
		if((p_virgulas[i+1] - p_virgulas[i]) == 1 ){
			countcv--;
		}
	}
	
	comandos = (char **) malloc(countcv * sizeof(char*));//alocaçao vetor de comandos separados por virgula
	if(comandos==NULL){
		printf("Erro de alocacao!");
		exit(1);
	}
	
	j=0;
	num = p_virgulas[0];//tamanho inicial do comando
	for (i=0; i < countc; i++){
		if(num>0){
   			comandos[j] = (char *) malloc (num * sizeof(char));//alocacao da string que armazenara os comandos separados
   			if(comandos[j]==NULL){
				printf("Erro de alocacao!");
				exit(1);
			}
			j++;
		}
   		num = p_virgulas[i+1] - p_virgulas[i] - 1;//calculo do tamanho do proximo comando
    }
    
	comandoToken = (char *) malloc(j * sizeof(char*)); //alocacao do token para fazer a copia do vetor de comandos final
	if(comandoToken==NULL){
		printf("Erro de alocacao!");
		exit(1);
	}
	
	i=0;

	comandoToken = strtok(comando, ",");//separacao da string comando atravez do comando strtok
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

//Funcao que recebe o comando separado trata os espaços e retorna os argumentos
char** Tratamento_Comando(char* comando){
	int i=0,j=0, counte,countev, *p_espacos, num, control=0;
	char **argv, *comandoToken;
	
	if(comando == NULL || strlen(comando)<2){
		return NULL;
	}
	
	strcat(comando," ");//concatenaçao com um espaco para melhorar a separação
	counte = Contador_Espacos(comando);
	
	p_espacos = (int *) malloc(counte * sizeof(int));//aloca um vetor para armazenar a posiçao das espacos para alocacao
	if(p_espacos==NULL){
		printf("Erro de alocacao!");
		exit(1);
	}
    
	for(i=0; i<strlen(comando); i++){//Estrutura de repeticao que armazena a posicao dos espacos
		if(comando[i] == ' '){
			p_espacos[j] = i;
			j++;
		}
		printf("%c ",comando[i]);
		if(comando[i] != ' '){
			
			control = 1;
		}
	}
	printf("\ncontrol %d\n",control);
	if(control == 0){
		return NULL;
	}
	countev = j;

	argv = (char **) malloc(countev * sizeof(char*));//alocacao vetor de argumentos separados por espaco
	if(argv==NULL){
		printf("Erro de alocacao!");
		exit(1);
	}
	
	j=0;
	num = p_espacos[0];//tamanho inicial do argumento
	for (i=0; i < counte; i++){
		if(num>1){
   			argv[j] = (char *) malloc (num * sizeof(char));//alocacao da string que armazenara os argumentos
   			if(argv[j]==NULL){
				printf("Erro de alocacao!");
				exit(1);
			}
			j++;	
		}
   		num = p_espacos[i+1] - p_espacos[i] - 1;//calculo do tamanho do proximo argumento
    }
    
    comandoToken = (char *) malloc(countev * sizeof(char*)); //alocacao do token para fazer a copia do vetor de comandos final
	if(comandoToken==NULL){
		printf("Erro de alocacao!");
		exit(1);
	}
	
	i=0;
	comandoToken = strtok(comando, " ");//separacao da string comando atravez do comando strtok
	while(comandoToken != NULL){
		if(i!=countev){
			strcpy(argv[i],comandoToken);
			comandoToken = strtok(NULL, " ");
			i++;
		}
	}
	argv[countev] = NULL;
	return(argv);	
}

//Funcao que libera os vetores alocados
void Libera_Alocacao(int count, char** comandos){
	int i;
  
  
	for(i = 0; i < count; i++){
		free(comandos[i]);	
	}
  	free(comandos);
}


int main(){
	int i=0, j, countc, counte, ch;
	char comando[512],**comandos,**argv, cmd[3];
	char s[100];
	pid_t pid;
	char *ponteiro= NULL;	
	
		
	while(i==0){
		
		printf("%s\n", getcwd(s, 100));//Imprime o local no qual esta sendo executado
		printf("Digite o comando:\n");
		fflush(stdin);
		fgets(comando,512,stdin);
		
		ponteiro = strstr(comando,"quit");//verificacao do comando quit
		if(ponteiro){
			exit(0);
		}
		
		comando[strlen(comando)-1] = 0;
		countc = Contador_Virgulas(comando)+1;
		comandos = Separador_Comandos(comando);
		
		for(j=0;j<countc;j++){
			
			argv = Tratamento_Comando(comandos[j]);
			if(argv == NULL){
				break;
			}
			
			if(strcmp(argv[0],"cd")==0){
				ch = chdir(argv[1]);
				break;
				if(ch == -1){
					printf("Erro no comando cd!\n"); 
					i=1;
					break;
				}
			}
			if ((pid = fork()) < 0) {     
    			printf("*** ERROR: forking child process failed\n");
       			exit(1);
    		}
    		else if (pid == 0) {  
   
      		 	if (execvp(argv[0], argv) < 0) {     
            		printf("*** ERROR: exec failed\n");
            		exit(1);
        		}
   			} 
		}
		
		sleep(1);
		
	}
	
	Libera_Alocacao(countc, comandos);
	counte = Contador_Espacos(comandos[j]);
	Libera_Alocacao(counte, argv);
	return 0;
}
