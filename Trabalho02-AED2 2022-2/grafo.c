#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "grafo.h"
#include "pilha.h"
#include "fila.h"


typedef struct noVert{
  char vertice[50];
  struct noVert *prox;
  struct noAdj *ladj;
}NoVert;

typedef struct noAdj{
  char vertice[50];
  int peso;
  struct noAdj *prox;
}NoAdj;

Grafo* criarGrafo(){
  //int v;
  Grafo *G;
  G = (Grafo*)malloc(sizeof(Grafo));
  G->numArco = 0;
  G->numVert = 0;
  G->vertices = NULL;
  return G;
}

struct noVert *inserirVertice(NoVert *ini, char Nome[]){
  struct noVert *novoVertice;
  novoVertice = (struct noVert *) malloc(sizeof(struct noVert));
  strcpy(novoVertice->vertice, Nome);
  novoVertice->prox = ini;
  novoVertice->ladj = NULL;
  return novoVertice;
}

void inserirArco(Grafo *G, char v1[], char v2[], int peso){
  struct noVert *v;
  struct noAdj *z;
  if(G == NULL)
    return;

  if(verticePresente(G,v1) == 0){
    G->vertices = inserirVertice(G->vertices,v1);
    G->numVert++;
  }
  printf("-");
  if(verticePresente(G,v2) == 0){
    G->vertices = inserirVertice(G->vertices,v2);
    G->numVert++;
  }
  printf("-");
  for(v = G->vertices; v != NULL; v = v->prox){
    if(strcmp(v->vertice, v1) == 0){
      for(z = v->ladj; z != NULL; z = z->prox){
        if(strcmp(z->vertice, v2) == 0)
          return;
      }
      v->ladj = inserirAdjacencia(v2,peso,v->ladj);
      G->numArco++;
    }
  }
}

struct noAdj *inserirAdjacencia(char vdest[], int peso, struct noAdj *l){
  struct noAdj *novo = (struct noAdj*) malloc(sizeof(struct noAdj));
  strcpy(novo->vertice,vdest);
  novo->peso = peso;
  novo->prox = l;
  return novo;
}

void imprimirListaAdj(Grafo *G){
  NoVert *NV;
  NoAdj *NA;
  if(G == NULL)
    return;
  printf("\n --- GRAFO ---\n");
  for(NV = G->vertices; NV != NULL; NV = NV->prox){
    printf("\nCidade %s:",NV->vertice);
    for(NA = NV->ladj; NA != NULL; NA = NA->prox){
      printf(" (%s|%d)", NA->vertice,NA->peso);
    }
  }
  printf("\n");
}

int verticePresente(Grafo *G, char v[]){
  NoVert *NV;
  for(NV = G->vertices; NV != NULL; NV = NV->prox){
    if(strcmp(NV->vertice, v) == 0)
      return 1;
  }
  return 0;
}

void fortConectado(Grafo *G, char nome[]){
  if(G == NULL)
    return;

  //Verifica se o vertice está contido no Grafo
  if(!verticePresente(G,nome))
    return;

  struct noVert *NV;
  struct noAdj *aux2;
  struct noVert *vert;
  struct noAdj *comAdj;

  printf("\nCidades fortemente conectados: ");
  //percorre todo os vertices e acha o vertice de origem
  for(NV = G->vertices; NV != NULL; NV = NV->prox){
    if(strcmp(NV->vertice,nome) == 0){
      comAdj = NV->ladj;
      break;
    }
  }
  //verifica todas as arestas
  for(; comAdj != NULL; comAdj = comAdj->prox){
    if(strcmp(comAdj->vertice,nome) == 0)
      continue;

    //encontra o vertice determinado pelas conexões
    for(NV = G->vertices; NV != NULL; NV = NV->prox){
      if(strcmp(NV->vertice,comAdj->vertice) == 0){
        vert = NV;
        break;
      }
    }

    //verifica se o vertice encontrado está conectado a origem
    for(aux2 = NV->ladj;aux2 != NULL; aux2 = aux2->prox){
      if(strcmp(aux2->vertice,nome) == 0){
        printf("%s ",vert->vertice);
        break;
      }
    }
  }
  printf("\n");
}

Lista diretRelac(Grafo *G, char nome[], int peso){
  Lista lst = criaLista();
  if(G == NULL || !verticePresente(G,nome))
    return lst;

  struct noVert *NV;
  struct noAdj *aux2;

  //Percorre todos os vertices
  for(NV = G->vertices; NV != NULL; NV = NV->prox){
    for(aux2 = NV->ladj; aux2 != NULL; aux2 = aux2->prox){
      if(aux2->peso <= peso){
        //se o vertice for o mesmo do passado pelo usuario insere o nome do usuario em uma lista ligada
        if(strcmp(NV->vertice,nome) == 0 && !elemPresente(lst, aux2->vertice))
          insere(&lst,aux2->vertice);
        //se o vertice tem uma aresta conectando em direção ao vertice passado pelo usuario insere o nome dele na lista
        else if(strcmp(aux2->vertice, nome) == 0 && !elemPresente(lst, NV->vertice)){
          insere(&lst, NV->vertice);
          break;
        }
      }
    }
  }

  return lst;
}

void caminhoMinimo(Grafo *G, char origem[], char destino[]){
  int i,j,elemP;
  struct noVert *NV;
  struct noAdj *aux2;
  int *M, *C;
  char **P, **D;
  char elem[50];

  if(G == NULL){
    return;
  }
  if(!verticePresente(G,origem) || !verticePresente(G,destino)){
    printf("Error: Vertice nao presente");
    return;
  }
  //Variavel que indica se o vertice foi visitado
  M = (int *) malloc(G->numVert * sizeof(int));
  //Preço do caminho minimo de cada vertice
  C = (int *) malloc(G->numVert * sizeof(int));
  //Antecessor de cada vertice
  P = (char **) malloc(G->numVert * sizeof(char *));
  for(i = 0; i < G->numVert; i++){
    P[i] = (char *) calloc(50, sizeof(char));
  }

  for(i = 0; i < G->numVert; i++){
    M[i] = 0;
    C[i] = 99999;
    strcpy(P[i],"SC");
  }

  //procura o vertice de origem
  i = 0;
  for(NV = G->vertices; NV != NULL; NV = NV->prox){
    if(strcmp(NV->vertice,origem) == 0)
      break;
    i++;
  }

  M[i] = 1;
  C[i] = 0;
  strcpy(P[i],NV->vertice);

  for(aux2 = NV->ladj; aux2 != NULL; aux2 = aux2->prox){
    i = 0;
    for(NV = G->vertices; NV != NULL; NV = NV->prox){
      if(strcmp(NV->vertice,aux2->vertice) == 0)
        break;
      i++;
    }
    C[i] = aux2->peso;
    strcpy(P[i],origem);
  }

  int min;
  for(j = 0; j < G->numVert; j++){
    min = 99999;
    for(i = 0; i < G->numVert; i++){
      if(min > C[i] && M[i] != 1){
        min = C[i];
        elemP = i;
      }
    }

    M[elemP] = 1;
    NV = G->vertices;
    for(i = 0; i < elemP; i++){
      NV = NV->prox;
    }
    strcpy(elem,NV->vertice);

    for(aux2 = NV->ladj; aux2 != NULL; aux2 = aux2->prox){
      i = 0;
      for(NV = G->vertices; NV != NULL; NV = NV->prox){
        if(strcmp(NV->vertice, aux2->vertice) == 0)
          break;
        i++;
      }
      if(C[i] > (C[elemP] + aux2->peso) && strcmp(aux2->vertice,elem) != 0){
        C[i] = C[elemP] + aux2->peso;
        strcpy(P[i],elem);
      }
    }
  }

  //Armazena o caminho minimo
  D = (char **) malloc(G->numVert * sizeof(char *));
  for(i = 0; i < G->numVert; i++){
    D[i] = (char *) calloc(50, sizeof(char));
  }

  strcpy(D[0],destino);
  for(i = 1; strcmp(D[i-1],origem); i++){
    j = 0;
    for(NV = G->vertices; NV != NULL; NV = NV->prox){
      if(strcmp(NV->vertice,D[i-1]) == 0)
        break;
      j++;
    }

    //Caso em P tenha SC significa que do vertice de origem não é possivel acessar o vertice correspondente
    if(strcmp("SC",P[j]) == 0){
      printf("%s e %s nao estao conectados", origem, destino);
      return;
    }
    strcpy(D[i],P[j]);
  }

  for(j = i-1; j > 0; j--){
    printf("%s -> ",D[j]);
  }
  printf("%s\n",D[0]);

  free(M);
  free(C);
  for(i = 0; i < G->numVert; i++){
    free(P[i]);
    free(D[i]);
  }
  free(P);
  free(D);
}

void cidadeDist(Grafo *G, char origem[], int dist, Pilha *P, int pesos[], int q){
  if(G == NULL || !verticePresente(G,origem))
    return;
  int i;
  char elem[40];
  //Caso a distância limite tenha sido atingida imprime
  if(dist == 0){
    Pilha  *P1= criarPilha(-1);
    //Coloca os elementos na ordem desejada
    while(vazia(P) == 0){
      strcpy(elem,desempilhar(P));
      empilhar(P1,elem);
    }

    for(i = 0; i < q; i++){
      strcpy(elem,desempilhar(P1));
      empilhar(P,elem);
      printf("%s %d ",elem,pesos[i]);
      strcpy(elem,desempilhar(P1));
      empilhar(P,elem);
      printf("%s ",elem);
      if(i != q-1)
        printf("-> ");
    }
    printf("\n");
    eraser(P1);
    return;
  }

  NoVert *NV;
  NoAdj *aux2;
  empilhar(P,origem);
  for(NV = G->vertices; NV != NULL; NV = NV->prox){
    if(strcmp(NV->vertice,origem) == 0)
      break;
  }
  //percorre as interações até chegar a distância limite
  for(aux2 = NV->ladj; aux2 != NULL; aux2 = aux2->prox){
    //Caso o vertice já tenha sido passado essa interação será ignorada
    if(noPresente(P,aux2->vertice) == 1)
      continue;
    empilhar(P,aux2->vertice);
    pesos[q] = aux2->peso;
    cidadeDist(G,aux2->vertice,dist-1,P,pesos,q+1);
    strcpy(elem,desempilhar(P));
  }
  strcpy(elem,desempilhar(P));

}

int marcaVisitas(char vt[], int pos, char tipo, struct visitaTempo *vet, int tam){
  int i;
  for(i = 0; i < tam; i++){
    if(strcmp(vet[i].vertice,vt) == 0){
      if(tipo == 'D'){
        vet[i].tempoDescoberta = pos;
        return 1;
      }
      else{
        if(vet[i].tempoFinalizacao == -1){
          vet[i].tempoFinalizacao = pos;
          return 1;
        }
        else
          return 0;
      }
    }
  }
  return 0;
}

int foiVisitadoTempo(char vert[], struct visitaTempo *vet, int tam){
  for(int i = 0; i < tam; i++){
    if((strcmp(vet[i].vertice,vert) == 0) && (vet[i].tempoDescoberta != -1))
      return 1;
  }
  return 0;
}

void imprimeVisitaTempo(struct visitaTempo *vet, int tam){
  for(int i = 0; i < tam; i++){
    printf("%s %d|%d\n", vet[i].vertice,vet[i].tempoDescoberta,vet[i].tempoFinalizacao);
  }
}

struct visitaTempo *percursoProfundidadeTempo(Grafo *G, char v[], int *t){
  NoVert *NV;// *aux;
  NoAdj *NA;
  struct visitaTempo *visitados;
  Pilha  *P;
  int tam = 0, tempo = 0, finaliza, r; //i;
  char vt[50];

  visitados = (struct visitaTempo*) malloc(G->numVert*sizeof(struct visitaTempo));

  for(NV = G->vertices; NV != NULL; NV = NV->prox){
    strcpy(visitados[tam].vertice,NV->vertice);
    visitados[tam].tempoDescoberta = -1;
    visitados[tam].tempoFinalizacao = -1;
    tam++;
  }

  P = criarPilha(-1);
  empilhar(P,v);

  while(!vazia(P)){
    strcpy(vt,top(P));
    if(foiVisitadoTempo(vt,visitados,tam) == 0){
      marcaVisitas(vt,tempo,'D',visitados,tam);
      tempo++;
      for(NV = G->vertices; NV != NULL; NV = NV->prox){
        if(strcmp(vt,NV->vertice) == 0){
          finaliza = 1;
          for(NA = NV->ladj; NA != NULL; NA = NA->prox){
            if(foiVisitadoTempo(NA->vertice,visitados,tam) == 0){
              empilhar(P,NA->vertice);
              finaliza = 0;
            }
          }
          if(finaliza == 1){
            r = marcaVisitas(vt,tempo,'F',visitados,tam);
            if(r == 1)
              tempo++;
            strcpy(vt,top(P));
          }
        }
      }
    }
    else{
      r = marcaVisitas(vt,tempo,'F',visitados,tam);
      if(r == 1)
        tempo++;
      strcpy(vt,top(P));

    }
  }
  eraser(P);
  *t=tam;
  return visitados;
}

void grafoTransposto(Grafo *G, Grafo *GT){
  NoVert *NV;
  NoAdj *NA;
  if(G == NULL)
      return;
  for(NV = G->vertices; NV != NULL; NV = NV->prox){
    printf("\nUsuario %s:",NV->vertice);
    for(NA = NV->ladj; NA != NULL; NA = NA->prox){
      printf(" (%s|%d)", NA->vertice,NA->peso);
      inserirArco(GT,NA->vertice,NV->vertice,NA->peso);
    }
  }
}


void ordSelecao(struct visitaTempo *v, int tam){
int maximo, i, j;
struct visitaTempo maior;

  for (i=0;i<tam-1;i++){
      maximo = i;
      for (j=i+1;j<tam;j++){
        if (v[j].tempoFinalizacao > v[maximo].tempoFinalizacao)
            maximo = j;
      }
      maior = v[maximo];
      v[maximo] = v[i];
      v[i] = maior;
  }
}

int FoiVisitado(char *vert, char **vet, int tam){
  int i;
  for (i = 0; i<=tam; i++){
    if(strcmp(vet[i], vert) == 0)
       return 1;
  }
  return 0;
}
int imprimeVisita(char **vet, int tam){
  int i;
  printf("\nOrdem da visita: ");
  for (i = 0; i<=tam; i++){
     printf("(%s) ", vet[i]);
  }
  return 0;
}
void BuscaEmProfundidade (Grafo *G, char v[], char **visitados, int *cont) {
   NoVert *NV;
   NoAdj *NA;
   char *vt;
   Pilha *P;
   //int i=0;


   //Iniciar a fila e inserir o vértice de origem
   //pilha = (Pilha *) malloc (sizeof(Pilha));

  P = criarPilha(-1);
  empilhar(P, v);
 // printf("\n busca em prof3 --> ");

  while(!vazia(P)){
       vt = desempilhar(P);
       if (FoiVisitado(vt,visitados,*cont)==0){
          strcpy(visitados[*cont],vt);
          (*cont)++;
          for (NV = G->vertices; NV!=NULL; NV = NV->prox)
              if(strcmp(vt, NV->vertice) == 0)
                 for (NA = NV->ladj; NA != NULL; NA = NA->prox)
                      if (FoiVisitado(NA->vertice,visitados,*cont)==0){
                           empilhar(P,NA->vertice);
                      }
       }
   }
   //
   imprimeVisita(visitados,(*cont)-1);
   free(P);
}

void CFC(Grafo *G, char componente[]){
  int i, /**j,*/ tam, cont=0;
  Grafo *GT;
  struct visitaTempo *G1;
  char **visitados;
      //Iniciar o vetor de visitados com 'nao' para todos os vértices
   visitados =  (char**)malloc (G->numVert * sizeof (char *)) ;
   for (i=0; i<G->numVert; i++){
      visitados[i] = (char*)malloc (20 * sizeof (char)) ;
      strcpy(visitados[i], "NAO");
   }
  G1 = (struct visitaTempo*) malloc(G->numVert*sizeof(struct visitaTempo));
  G1 = percursoProfundidadeTempo(G,componente,&tam);
  ordSelecao(G1, tam);
  imprimeVisitaTempo(G1, tam);

  GT = criarGrafo();

  grafoTransposto(G,GT);
  printf("\n-- Grafo Transposto --> ");
  imprimirListaAdj(GT);


  for(i=0;i<tam;i++){
      strcpy(visitados[cont], G1[i].vertice);
     printf("\n vertice dfs - %s %s--> ", G1[i].vertice, visitados[cont]);
      cont++;
      BuscaEmProfundidade(GT, G1[i].vertice, visitados, &cont);
  }
}
