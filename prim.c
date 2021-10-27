/*                         Ep1 da disciplina de Grafos                                          */ 
/* Implementação do Algoritmo de Prim                                                           */
/* Implementado pelos alunos:Luan Martins, Pedro Furtado, Hayber Gabriel e Lucas Magalhães      */
/* Data: 21/10/2021									                                            */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITO 9999
#define TRUE 1
#define FALSE 0


typedef struct {
    int **matrizAdjacencias;
    int numVertices;
	int numArestas;
} Grafo;



void prim(Grafo *grafo){ 
	int i, j, a, b;
	int u = 0, v = 0, x = 0, total = 0;
	int minimo, custoMinimo=0;
	int verticeAtual = 1;

	int vertices = grafo->numVertices;
	int visitados[vertices+1];
	
	for (x = 0; x <= vertices; x++) visitados[x] = 0;
   	visitados[1] = 1;

	printf("\nÁrvore geradora de custo mínimo:");

	while (verticeAtual < vertices) {
		for (i = 0, minimo = INFINITO; i <= vertices; i++)
			for (j = 0; j <= vertices; j++){
				if (grafo->matrizAdjacencias[i][j] < minimo)
					if (visitados[i] != 0){
						minimo = grafo->matrizAdjacencias[i][j];
						a = u = i;
						b = v = j;
					}
			}

			if (visitados[u] == 0 || visitados[v] == 0){
				printf(" (%d, %d)", a, b);
				verticeAtual++;
				custoMinimo += minimo;
				visitados[b] = 1;
			}
			

		grafo->matrizAdjacencias[a][b] = grafo->matrizAdjacencias[b][a] = INFINITO;

	}
	printf("\n\nCusto: %d\n\n", custoMinimo);


}


int **alocaMatriz(int qttVertices){
	int **M;
	int i;

	M = (int **) malloc(sizeof(int *) * (qttVertices + 1));

	if(M == NULL){
		printf("Memoria insuficiente.\n");
		exit(1);
	}

	for(i = 0; i <= qttVertices; i++){
		M[i] = (int *) malloc(sizeof(int) * (qttVertices + 1));
		
		if(M[i] == NULL){
			printf("Memoria insuficiente.\n");
			exit(1);
		}
	}

	return M;
}


void liberaGrafo(Grafo *grafo){
	int i;

	for(i = 0; i <= grafo->numVertices; i++)
		free(grafo->matrizAdjacencias[i]);

	free(grafo->matrizAdjacencias);
}


void criaGrafo(Grafo *grafo, char filename[]){
	FILE *arquivo;
	
	int vertices, arestas, i, j, k, u, v, custo;
	arquivo = fopen(filename, "r");

	if(arquivo == NULL){
		printf("%s: arquivo não encontrado.\n", filename);
		exit(1);
	}

	fscanf(arquivo, "%d %d", &vertices, &arestas);
	grafo->numVertices = vertices;
	grafo->numArestas = arestas;

	grafo->matrizAdjacencias = alocaMatriz(vertices);

	for(i = 0; i <= vertices; i++){
		for (j = 0; j <= vertices; j++){
			grafo->matrizAdjacencias[i][j] = INFINITO;
		}
	}

	for (k = 0; k <= vertices+1; k++) {
		fscanf(arquivo, "%d %d %d", &u, &v, &custo);
		grafo->matrizAdjacencias[u][v] = custo;
		grafo->matrizAdjacencias[v][u] = custo;
	}
	
	fclose(arquivo);
}

void imprimeMatrizAdjacencias(Grafo *grafo){
	int i, j;

	printf("\nMatriz de adjacencias:\n     ");
	for (int k = 1; k <= grafo->numVertices; k++) {
		printf(" %4d", k);
	}
	
	printf("\n");

	for(i = 1; i <= grafo->numVertices; i++){
		for(j = 1; j <= grafo->numVertices; j++) {
			if(j == 1) printf(" %4d", i);

			printf(" %4d", grafo->matrizAdjacencias[i][j]);
		}

			
		printf("\n");
		
	}
}

typedef struct{
    int caminhoDoArquivo;
    int imprimirGrafo;
} Args;

Args parsearArgumentos(int argc, char **argv) {
	Args argumentos;

	argumentos.caminhoDoArquivo = 0;
	argumentos.imprimirGrafo = 0;

	switch (argc) {
		case 1:
			break;
		
		case 2:
			argumentos.caminhoDoArquivo = TRUE;
			break;

		case 3:
			if(strcmp("-p", argv[2]) == 0) {
				argumentos.caminhoDoArquivo = TRUE;
				argumentos.imprimirGrafo = TRUE;
				break;

			} else {
				printf("%s: argumento desconhecido!\n", argv[2]);
				exit(1);
			}
			break;

		default:
			printf("Muitos argumentos!\n");
			exit(1);
			break;
	}

	return argumentos;
}

int main(int argc, char **argv){
	Grafo grafo;
	Args argumentos;
	char nomeArquivo[50];

	argumentos = parsearArgumentos(argc, argv);

	if(argumentos.caminhoDoArquivo) criaGrafo(&grafo, argv[1]);
	else {
		printf("Insira o caminho do arquivo e pressione Enter: \n");
		scanf("%s", nomeArquivo);
		criaGrafo(&grafo, nomeArquivo);
	}

	if(argumentos.imprimirGrafo) imprimeMatrizAdjacencias(&grafo);

	prim(&grafo);
	liberaGrafo(&grafo);

 	return 0;
}