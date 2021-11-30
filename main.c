//AVISO: COMPILAR COM A OPÇÃO -lm 

#ifdef WINDOWS
#include <direct.h>
#else
#include <unistd.h>
#endif
//includes de plataforma aqui.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define NOME_SIZE 51 //arbitrário + 1 terminador de string
#define PRONT_SIZE 8 //de acordo com os números de prontuário da IF + um terminador de string

struct aluno{
	char prontuario[PRONT_SIZE];
	float nota1, nota2;
	char nome[NOME_SIZE];
};

void cleanup_func1(DIR* cwd, FILE* f_handle, char handle_opened){
	if(handle_opened) fclose(f_handle);
	closedir(cwd);
	getchar();
}

void enter_to_continue(){
	printf("Aperte ENTER para continuar.");
	while( getchar() != '\n' );
}

int main(){
 char input;
 FILE *f_handle;
 const int _zero = 0;
 struct dirent* entry;
 int len = 0;

 while(1){
    printf("\n1. Criar arquivo\n2. Incluir alunos\n3. Consultar todos alunos\n4. Consultar alunos por curso\n5. Consultar alunos aprovados\n6. Consultar alunos reprovados\n7. Consultar alunos de exame\n8. Finalizar\n");	
    if((input = getchar()) != EOF){
	switch(input){
		case '1':
		{
			char handle_opened = 0;
		    DIR* cwd = opendir(".");
			while((entry = readdir(cwd)) != NULL){
				if(!strcmp(entry->d_name, "Alunos.dat")){
					printf("O arquivo Alunos.dat já existe. Deseja apagar e criar de novo o arquivo? [s/n]\n");
					while((input = getchar()) != EOF){
						if(input == 'S' || input == 's'){
							remove("./Alunos.dat");
							f_handle = fopen("./Alunos.dat", "w");
							handle_opened = 1;
							fwrite(&_zero, sizeof(int), 1, f_handle);
							printf("Arquivo criado.\n");
							break;
						}
						else if(input == 'N' || input == 'n'){
							printf("Cancelado.\n");
							break;
						}
					}
					break;
				}
			}
			if(entry == NULL){
				f_handle = fopen("./Alunos.dat", "w");
				fwrite(&_zero, sizeof(int), 1, f_handle);
				handle_opened = 1;
				printf("Arquivo criado.\n");
			}	
			cleanup_func1(cwd, f_handle, handle_opened);
			break;
		}
		case '2':
		    {
			struct aluno a = {"1234567", 1.0, 1.0, "Jacington P."};
			//TODO: ler os dados aqui...
			//tamanho de nome: definido nos #defines
			//tamanho de prontuário: tá nos #defines também
			
			
			if((f_handle = fopen("./Alunos.dat", "rb+")) ==  NULL){
				printf("Erro na abertura do arquivo Alunos.dat! Certifique-se que o arquivo foi criado usando a função 1.");
				break;
			}
			fread(&len, sizeof(int), 1, f_handle);
			len++;
			fseek(f_handle, 0, SEEK_SET);
            fwrite(&len, sizeof(int), 1, f_handle);
			fclose(f_handle);

			f_handle = fopen("./Alunos.dat", "ab");
			fwrite(&a, sizeof(struct aluno), 1, f_handle);
			fclose(f_handle);

			printf("Aluno inserido com sucesso!\n");
			getchar();
			break;
			}
		case '3':
		{
			if((f_handle = fopen("./Alunos.dat", "rb")) ==  NULL){
				printf("Erro na abertura do arquivo Alunos.dat! Certifique-se que o arquivo foi criado usando a função 1.");
				break;
			}
			struct aluno a;
			fread(&len, sizeof(int), 1, f_handle);
			
			if(len){
			printf("| Nome do Aluno | Prontuário | Média |\n" );
			for(int i = 0; i < len; i++){
				fread(&a, sizeof(struct aluno), 1, f_handle);
				printf("%s %s %.2f\n", a.nome, a.prontuario, (a.nota1+a.nota2)/2);
			}}
			else{
				printf("Nada consta.\n");
			}
			enter_to_continue();
			getchar();
			break;
		}
		case '4':
			break;

		case '5':
			break;

		case '6':
			break;

		case '7':
			break;

		case '8':
			return 0;
	}
    }
    else{
	break;
    }
  }
}

