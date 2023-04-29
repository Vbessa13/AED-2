#include "fila.h"
#include "grafo.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *fp = fopen("rotas.txt", "r");

  char Nome1[40];
  char Nome2[40];
  int z, peso, op, dist;
  char nome[50], nome2[50];
  Grafo *G;
  Lista lst;

  G = criarGrafo();

  while (fscanf(fp, "%s %s %d", &Nome1, &Nome2, &z) > 0) {
    inserirArco(G, Nome1, Nome2, z);
  }

  fclose(fp);

  do {
    printf("\n=== MENU ===\n");
    printf("[1] Imprimir o grafo\n");
    printf("[2] Cidades a ate 'K' de distancia\n");
    printf("[3] Todas as cidades ligadas(distancia 1) ate 100 km de distancia\n");
    printf("[4] Mostrar as cidades fortemente conectados a uma outra\n");
    printf("[5] Caminho de custo minimo entre duas cidades\n");
    printf("[6] Sair\n");
    scanf("%d", &op);
    fflush(stdin);
    switch (op) {
    case 1: {
      imprimirListaAdj(G);
      break;
    }
    case 2: {
      printf("\nDigite o nome da cidade: ");
      scanf("%s", nome);
      fflush(stdin);
      printf("Digite a distancia: ");
      scanf("%d", &dist);
      fflush(stdin);
      Pilha *P = criarPilha(100);
      int *pesos;
      pesos = (int *)malloc(dist * sizeof(int));
      cidadeDist(G, nome, dist, P, pesos, 0);
      free(pesos);
      eraser(P);
      break;
    }
    case 3: {
      lst = criaLista();
      printf("\nDigite o nome da cidade: ");
      scanf("%s", nome);
      fflush(stdin);
      peso = 100;
      fflush(stdin);
      lst = diretRelac(G, nome, peso);
      printf("Vertices: ");
      imprimiLista(lst);
      apaga_Lista(&lst);
      break;
    }
    case 4: {
      printf("\nDigite o nome da cidade: ");
      scanf("%s", nome);
      fflush(stdin);
      fortConectado(G, nome);
      break;
    }
    case 5: {
      printf("\nDigite o nome da cidade de origem: ");
      scanf("%s", nome);
      fflush(stdin);
      printf("Digite o nome da cidade de destino: ");
      scanf("%s", nome2);
      fflush(stdin);
      caminhoMinimo(G, nome, nome2);
      break;
    }
    case 6: {
      printf("Saindo...\n");
      break;
    }
    }
  } while (op != 6);
  return 0;
}
