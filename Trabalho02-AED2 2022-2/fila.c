#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "fila.h"

struct no{
  char elem[50];
  struct no *prox;
};

Lista criaLista(){
  return NULL;
}

void insere(Lista *lst, char elem[]){
  Lista N = (Lista) malloc(sizeof(struct no));
  if(N == NULL)
    return;

  strcpy(N->elem,elem);
  if(listaVazia(*lst) == 1){
    N->prox = *lst;
    *lst = N;
    return;
  }

  Lista aux = *lst;
  while(aux->prox != NULL){
    aux = aux->prox;
  }
  N->prox = aux->prox;
  aux->prox = N;
}

void remove_lst(Lista *lst, char elem[]){
  if(listaVazia(*lst) == 1)
    return;

  Lista aux = *lst;
  *lst = aux->prox;
  strcpy(elem,aux->elem);
  free(aux);
}

int listaVazia(Lista l){
  if(l == NULL)
    return 1;
  else
    return 0;
}

void imprimiLista(Lista lst){
  if(listaVazia(lst) == 1)
    return;
  Lista aux;
  for(aux = lst; aux != NULL; aux = aux->prox){
    printf("%s ",aux->elem);
  }
  printf("\n");
}

int elemPresente(Lista lst, char elem[]){
  if(listaVazia(lst))
    return 0;

  Lista aux;
  for(aux = lst; aux != NULL; aux = aux->prox){
    if(strcmp(aux->elem,elem) == 0)
      return 1;
  }
  return 0;
}

void apaga_Lista(Lista *lst){
  if(listaVazia(*lst) == 1)
    return;

  Lista aux = *lst;
  while(aux != NULL){
    *lst = aux->prox;
    free(aux);
    aux = *lst;
  }
}
