#include <stdio.h> 
#include <stdlib.h>
#if defined(WIN32)
	#include <windows.h>
#elif defined(__unix__)
	#include <time.h>
	#include <unistd.h>
#else
#endif

#include "EstruturaVetores.h"

int menu();
void limparTela();
int aguardar(unsigned ms);

int main(int argc, char const *argv[]){
	int opcao;
	inicializar();
	do{
		opcao = menu();
		switch(opcao){
			case 1: gerenciarInsercao(); break;
			case 2:
			break;
			case 3:
			break;
			case 4:
			break;
			case 5:
			break;
			case 6:
			break;
			case 7: finalizar(); break;
			default:
				printf("Valor invalido...\n");
			break;
		}
		aguardar(1000);
	}while(opcao != 7);
	return 0;
}

void gerenciarInsercao(){
	int posicao = 0, valor = 0, retorno;
	printf("Digite a posicao onde deseja inserir: "); scanf("%d", &posicao);
	printf("Digite o valor que deseja inserir: "); scanf("%d", &valor);
	retorno = inserirNumeroEmEstrutura(valor, posicao);
	if (retorno == SUCESSO){
		printf("Estrutura criada com sucesso!");
	}
}

int menu(){
	limparTela();
	int opcao = 0;
	printf("==============================================\n");
	printf("\t1. Inserir elemento;\n");
	printf("\t2. Listar os numeros de todas as estruturas;\n");
	printf("\t3. Listar os numeros de todas as estruturas ordenados;\n");
	printf("\t4. Listar todos os numeros de forma ordenada;\n");
	printf("\t5. Excluir um elemento;\n");
	printf("\t6. Aumentar o tamanho de uma estrutura auxiliar;\n");
	printf("\t7. Sair;\n");
	printf("--> "); scanf("%d", &opcao);
	return opcao;
}

void limparTela(){
	#ifdef WIN32
		system ("cls");
	#else
		printf("\e[H\e[2J");
	#endif
}

int aguardar(unsigned ms){
	#if defined(WIN32)
		SetLastError(0);
		Sleep(ms);
		return GetLastError() ?-1 :0;
	#elif _POSIX_C_SOURCE >= 199309L
		const struct timespec ts = {
			ms / 1000, /* seconds */
			(ms % 1000) * 1000 * 1000 /* nano seconds */
		};
		return nanosleep(&ts, NULL);
	#elif _BSD_SOURCE || \
		(_XOPEN_SOURCE >= 500 || \
			_XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED) && \
		!(_POSIX_C_SOURCE >= 200809L || _XOPEN_SOURCE >= 700)
		return usleep(1000 * ms);
	#else
		# error ("No millisecond sleep available for this platform!")
		return -1;
	#endif
}