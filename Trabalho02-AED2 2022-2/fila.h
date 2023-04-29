#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

typedef struct no * Lista;
Lista criaLista();
void insere(Lista *lst, char elem[]);
void remove_lst(Lista *lst, char elem[]);
int listaVazia(Lista l);
void imprimiLista(Lista lst);
int elemPresente(Lista lst, char elem[]);
void apaga_Lista(Lista *lst);


#endif // FILA_H_INCLUDED
