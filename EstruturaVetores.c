#include <stdio.h>
#include <stdlib.h>

#include "EstruturaVetores.h"

#define TAM 10

void dobrar(int *x){ *x = *x * 2; }

Celula *estruturaPrincipal = NULL;

/*
    Objetivo: criar estrutura auxiliar na posição 'posicao'.
    com tamanho 'tamanho'

    Retorno (int)
        SUCESSO - criado com sucesso
        JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
        SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
        TAMANHO_INVALIDO - o tamanho tem inteiro maior ou igual a 1
*/
int criarEstruturaAuxiliar(int tamanho, int posicao){
    if (!ehPosicaoValida(posicao))
        return POSICAO_INVALIDA;

    if (!ehTamanhoValido(tamanho))
        return TAMANHO_INVALIDO;

    posicao -= 1;
    if (existeEstruturaAuxiliar(posicao))
        return JA_TEM_ESTRUTURA_AUXILIAR;

    estruturaPrincipal[posicao].estruturaAuxiliar = (int *) malloc(tamanho * sizeof(int));

    if (estruturaPrincipal[posicao].estruturaAuxiliar == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    estruturaPrincipal[posicao].tamanho = tamanho;

    return SUCESSO;
}

/*
    Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
    
    Retorno (int)
        SUCESSO - inserido com sucesso
        SEM_ESPACO - não tem espaço
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int inserirNumeroEmEstrutura(int valor, int posicao){
    if (!ehPosicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (!temEspaco(posicao))
        return SEM_ESPACO;

    int iAuxiliar = estruturaPrincipal[posicao].espacoUtilizado;
    estruturaPrincipal[posicao].estruturaAuxiliar[iAuxiliar] = valor;
    estruturaPrincipal[posicao].espacoUtilizado += 1;
    
    return SUCESSO;
}

/*
    Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
    ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
    Obs. Esta é uma exclusão lógica

    Retorno (int)
        SUCESSO - excluido com sucesso
        ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao){
    if (!ehPosicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (estruturaAuxiliarEstaVazia(posicao))
        return ESTRUTURA_AUXILIAR_VAZIA;

    estruturaPrincipal[posicao].espacoUtilizado -= 1;

    return SUCESSO;
}

/*
    Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
    Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
    ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
    Obs. Esta é uma exclusão lógica
    
    Retorno (int)
        SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
        ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        NUMERO_INEXISTENTE - Número não existe
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroEspecificoDeEstrutura(int valor, int posicao){
    return excluirNumeroDeEstrutura(valor, posicao, 0);
}

/*
    Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'. Caso 'removerTodasOcorrencias'
    seja 1 todas as ocorrências do numero 'valor' serão excluídas, caso contrário apenas a primeira ocorrência será excluída
    Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
    ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
    Obs. Esta é uma exclusão lógica
    
    Retorno (int)
        SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
        ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        NUMERO_INEXISTENTE - Número não existe
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDeEstrutura(int valor, int posicao, int removerTodasOcorrencias){
    if (!ehPosicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (estruturaAuxiliarEstaVazia(posicao))
        return ESTRUTURA_AUXILIAR_VAZIA;

    int i, j;
    int quantidadeRemovida = 0;

    for (i = 0, j = 0; j < estruturaPrincipal[posicao].espacoUtilizado;){
        int continuarApagando = removerTodasOcorrencias || quantidadeRemovida == 0;
        int valorEncontrado = estruturaPrincipal[posicao].estruturaAuxiliar[i] == valor;
        if (valorEncontrado && continuarApagando){ j += 1; quantidadeRemovida += 1; }
        else{ i += 1; j += 1; }
        estruturaPrincipal[posicao].estruturaAuxiliar[i] = estruturaPrincipal[posicao].estruturaAuxiliar[j];
    }

    if (quantidadeRemovida == 0)
        return NUMERO_INEXISTENTE;

    estruturaPrincipal[posicao].espacoUtilizado -= quantidadeRemovida;

    return SUCESSO;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao){
    if (posicao < 1 || posicao > 10)
        return 0;
    return 1;
}

// se tamanho é um valor válido {entre 1 e 10}
int ehTamanhoValido(int tamanho){
    if (tamanho <= 0)
        return 0;
    return 1;
}

/*
    Objetivo: verificar se a estrutura principal possui uma estrutura auxiliar
    na posição determinada.

    Retorno (int)
        1 - existe
        0 - não existe
*/
int existeEstruturaAuxiliar(int posicao){
    if (estruturaPrincipal[posicao].estruturaAuxiliar == NULL)
        return 0;
    return 1;
}

/*
    Objetivo: verificar se a estrutura auxiliar determinada está vazia.

    Retorno (int)
        1 - vazia
        0 - possui algum elemento
*/
int estruturaAuxiliarEstaVazia(int posicao){
    if (estruturaPrincipal[posicao].espacoUtilizado == 0)
        return 1;
    return 0;
}

/*
    Objetivo: verificar se a estrutur auxiliar informada ainda tem espaço para inserir
    valores.

    Retorno (int)
        1 - tem espaço
        0 - não tem espaço
*/
int temEspaco(int posicao){
    if (estruturaPrincipal[posicao].espacoUtilizado == estruturaPrincipal[posicao].tamanho)
        return 0;
    return 1;
}

/*
    Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
    os números devem ser armazenados em vetorAux

    Retorno (int)
        SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    if (!ehPosicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    int i;
    for (i = 0; i < estruturaPrincipal[posicao].espacoUtilizado; i += 1)
        vetorAux[i] = estruturaPrincipal[posicao].estruturaAuxiliar[i];

    return SUCESSO;
}

/*
    Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
    os números devem ser armazenados em vetorAux

    Retorno (int)
        SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    if (!ehPosicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    int i, totalDeItens = estruturaPrincipal[posicao].espacoUtilizado;

    getDadosEstruturaAuxiliar(posicao, vetorAux);

    Ordenar(vetorAux, totalDeItens);

    return SUCESSO;
}

/*
    Objetivo: ordenar um vetor 'vetor' que tem um tamanho 'tamanho' em ordem crescente
    utilizando o algoritmo selection sort

    Retorno void
*/
void Ordenar(int vetor[], int tamanho){ 
  int i, j, min, aux;
  for (i = 0; i < (tamanho - 1); i += 1){
     min = i;
     for (j = (i + 1); j < tamanho; j += 1)
       if(vetor[j] < vetor[min]) 
         min = j;
     if (vetor[i] != vetor[min]){
       aux = vetor[i];
       vetor[i] = vetor[min];
       vetor[min] = aux;
     }
  }
}

/*
    Objetivo: retorna os números de todas as estruturas auxiliares.
    os números devem ser armazenados em vetorAux

    Retorno (int)
        SUCESSO - recuperado com sucesso os valores de todas as estruturas
        TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - quando nenhuma posição da estrutura principal possui um auxiliar com valor
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]){
    int _;
    return getValoresDeTodasEstruturasAuxiliares(vetorAux, &_);
}

/*
    Objetivo: retorna os números de todas as estruturas auxiliares.
    os números devem ser armazenados em vetorAux e a quantidade total de itens obtidos devem ser
    inseridos no ponteiro total

    Retorno (int)
        SUCESSO - recuperado com sucesso os valores de todas as estruturas
        TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - quando nenhuma posição da estrutura principal possui um auxiliar com valor
*/
int getValoresDeTodasEstruturasAuxiliares(int vetorAux[], int *total){
    int algumaEstruturaAuxiliarTemItem = 0, i, j, vetorAuxIndex = 0;
    for (i = 0; i < TAM; i += 1){
        int auxiliarNaoNula = estruturaPrincipal[i].estruturaAuxiliar != NULL;
        int temItem = estruturaPrincipal[i].espacoUtilizado > 0;
        if (auxiliarNaoNula && temItem){
            algumaEstruturaAuxiliarTemItem = 1;
            for (j = 0; j < estruturaPrincipal[i].espacoUtilizado; j += 1, vetorAuxIndex += 1)
                vetorAux[vetorAuxIndex] = estruturaPrincipal[i].estruturaAuxiliar[j];
        }
    }
    *total = vetorAuxIndex;
    if (algumaEstruturaAuxiliarTemItem) return SUCESSO;
    else return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
}

/*
    Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
    os números devem ser armazenados em vetorAux

    Retorno (int)
        SUCESSO - recuperado com sucesso os valores de todas as estruturas
        TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - quando nenhuma posição da estrutura principal possui um auxiliar com valor
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){
    int totalDeItens;
    if (getValoresDeTodasEstruturasAuxiliares(vetorAux, &totalDeItens) == TODAS_ESTRUTURAS_AUXILIARES_VAZIAS)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    Ordenar(vetorAux, totalDeItens);

    return SUCESSO;
}

/*
    Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
    Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

    Retorno (int)
        SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
        SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
        POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
        NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
        SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){
    if (!ehPosicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    novoTamanho += estruturaPrincipal[posicao].tamanho;
    if (!ehTamanhoValido(novoTamanho))
        return NOVO_TAMANHO_INVALIDO;

    estruturaPrincipal[posicao].estruturaAuxiliar = (int *) realloc(estruturaPrincipal[posicao].estruturaAuxiliar, novoTamanho * sizeof(int));
    if (estruturaPrincipal[posicao].estruturaAuxiliar == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    estruturaPrincipal[posicao].tamanho = novoTamanho;
    int _espacoUtilizado = estruturaPrincipal[posicao].espacoUtilizado;
    estruturaPrincipal[posicao].espacoUtilizado = novoTamanho < _espacoUtilizado ? novoTamanho : _espacoUtilizado;

    return SUCESSO;
}

/*
    Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

    Retorno (int)
        POSICAO_INVALIDA - posição inválida
        SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
        ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
        Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao){
    if (!ehPosicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (estruturaAuxiliarEstaVazia(posicao))
        return ESTRUTURA_AUXILIAR_VAZIA;

    return estruturaPrincipal[posicao].espacoUtilizado;
}

/*
    Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

    Retorno (No*)
        NULL, caso não tenha nenhum número nas listas
        No*, ponteiro para o início da lista com cabeçote
*/
No* montarListaEncadeadaComCabecote(){
    No *inicio = NULL, *fim = NULL;
    int algumaEstruturaAuxiliarTemItem = 0, i, j;
    for (i = 0; i < TAM; i += 1){
        int auxiliarNaoNula = estruturaPrincipal[i].estruturaAuxiliar != NULL;
        int temItem = estruturaPrincipal[i].espacoUtilizado > 0;
        if (auxiliarNaoNula && temItem){
            algumaEstruturaAuxiliarTemItem = 1;
            for (j = 0; j < estruturaPrincipal[i].espacoUtilizado; j += 1){
                No * novoNo = (No *) malloc(sizeof(No *));
                novoNo->conteudo = estruturaPrincipal[i].estruturaAuxiliar[j];
                novoNo->prox = NULL;
                if (inicio == NULL) inicio = novoNo;
                else fim->prox = novoNo;
                fim = novoNo;
                fim->prox = NULL;
            }
        }
    }
    if (algumaEstruturaAuxiliarTemItem) return inicio;
    else return NULL;
}

/*
    Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.

    Retorno void
*/
void getDadosListaEncadeadaComCabecote(No* inicio, int vetorAux[]){
    No* item = inicio; int vetorAuxindex;
    for (vetorAuxindex = 0; item != NULL; vetorAuxindex += 1, item = item->prox)
        vetorAux[vetorAuxindex] = item->conteudo;
}

/*
    TODO: ta errado isso aqui ó... tem que mudar isso po, da pra ficar assim não
    suspeita: a função getDadosListaEncadeadaComCabecote deve estar alterando o ponteiro inicio

    Objetivo: Destruir a lista encadeada com cabeçote a partir de início.

    Retorno void.
*/
void destruirListaEncadeadaComCabecote(No* inicio){
    for (; inicio != NULL;){
        No* auxiliar = inicio->prox;
        free(inicio);
        inicio = auxiliar;
    }
}

/*
    Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 
*/
void inicializar(){
    int i;
    estruturaPrincipal = (Celula *) malloc(TAM * sizeof(Celula));
    for(i = 0; i < TAM; i += 1){
        estruturaPrincipal[i].tamanho = 0;
        estruturaPrincipal[i].espacoUtilizado = 0;
        estruturaPrincipal[i].estruturaAuxiliar = NULL;
    }
}

/*
    Objetivo: finaliza o programa. deve ser chamado ao final do programa 
    para poder liberar todos os espaços de memória das estruturas auxiliares.
*/
void finalizar(){
    int i;
    for(i = 0; i < TAM; i += 1)
        free(estruturaPrincipal[i].estruturaAuxiliar);
    free(estruturaPrincipal);
}

