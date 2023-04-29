#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "fila.h"
#include "pilha.h"

typedef struct grafo{
  int numVert;
  int numArco;
  struct noVert  *vertices;
}Grafo;

struct visitaTempo{
  char vertice[50];
  int tempoDescoberta;
  int tempoFinalizacao;
};

Grafo* criarGrafo();
struct noVert *inserirVertice(struct noVert *ini, char name[]);
void inserirArco(Grafo *G, char v1[], char v2[], int peso);
struct noAdj *inserirAdjacencia(char vdest[], int peso, struct noAdj *l);
void imprimirListaAdj(Grafo *G);
int verticePresente(Grafo *G, char v[]);
void fortConectado(Grafo *G, char nome[]);
Lista diretRelac(Grafo *G, char nome[], int peso);
void caminhoMinimo(Grafo *G, char origem[], char destino[]);
void cidadeDist(Grafo *G, char origem[], int dist, Pilha *P, int pesos[], int q);
int marcaVisitas(char vt[], int pos, char tipo, struct visitaTempo *vet, int tam);
int foiVisitadoTempo(char vert[], struct visitaTempo *vet, int tam);
void imprimeVisitaTempo(struct visitaTempo *vet, int tam);
struct visitaTempo *percursoProfundidadeTempo(Grafo *G, char v[], int *t);
void grafoTransposto(Grafo *G, Grafo *GT);
void CFC(Grafo *G, char componente[]);

#endif // GRAFO_H_INCLUDED
