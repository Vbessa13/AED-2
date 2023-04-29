#include <stdlib.h>
#include<string.h>
#include "pilha.h"

#define true	1
#define false	0

Pilha* criarPilha(int tam){
    Pilha *P;
    P = (Pilha*)malloc(sizeof(Pilha));
    if(P != NULL){
        P->head = NULL;
        P->tam = tam;
    }
    return P;
}

void empilhar(Pilha *P,char Nome[]){
    if(!cheia(P)){
        NoPilha *NP;
        NP = (NoPilha*)malloc(sizeof(NoPilha));
        if(NP != NULL){
            NP->prox = P->head; // insiro sempre o novo no na cabeça.
            strcpy(NP->Nome,Nome);
            P->tam--;
            P->head = NP;
        }
    }
}

char* desempilhar(Pilha *P){ // nessa funçao criarmo um auxliliar que vai receber o topo da pilha, feiot isso epgamos o valor dela e desalocamos da memoria
    char *valor;
    valor = (char*)malloc(MAX*sizeof(char));
    if(!vazia(P)){
        NoPilha *aux;
        aux = P->head;
        strcpy(valor,aux->Nome);
        P->head = aux->prox;
        free(aux);
    }
    return valor;
}

int vazia(Pilha *P){
    if(P->head == NULL)
        return true;
    else
        return false;
}

int cheia(Pilha *P){
    if(P->tam == 0)
        return true;
    else
        return false;
}

char* top(Pilha *P){
    return P->head->Nome;
}

int noPresente(Pilha *P, char Nome[]){
    if(vazia(P) == 1)
        return 0;
}


void eraser(Pilha *P){
    if(vazia(P))
        return;

    NoPilha *aux = P->head;
  while(aux != NULL){
    P->head = aux->prox;
    free(aux);
    aux = P->head;
  }
}
