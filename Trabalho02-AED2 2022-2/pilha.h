#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#define MAX 50

typedef struct pilha{
    struct nopilha *head;
    int tam;
}Pilha;

typedef struct nopilha{
    struct nopilha *prox;
    char Nome[MAX];
}NoPilha;

Pilha* criarPilha(int tam); // Funçao que retorna um ponteiro da pilha , caso queira uma pilha de tamanho infinito colocar "-1"
void empilhar(Pilha *P,char Nome[]); // funçao que empilha um valor na pilha
char* desempilhar(Pilha *P); // funçao q desempilha um numero
char* top(Pilha *P);
int vazia(Pilha *P);
int cheia(Pilha *P);
int noPresente(Pilha *P, char Nome[]);
void eraser(Pilha *P); // funçao q desaloca e exclui uma pilha da memoria.

#endif // PILHA_H_INCLUDED
