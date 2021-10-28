/*                         Ep1 da disciplina de Grafos                                          */ 
/* Implementação do Algoritmo de Prim                                                           */
/* Implementado pelos alunos: Luan Martins, Pedro Furtado, Hayber Gabriel e Lucas Magalhães     */
/* Data: 27/10/2021									                                            */

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

void prim(Grafo *grafo) {
    /* Algoritmo de Prim. 
    Dado um grafo, imprime as arestas que constituem uma árvore geradora de custo mínimo do grafo. */

    int i, j;
    int u = 0, v = 0, x = 0, total = 0;
    int minimo, custoMinimo = 0;
    int verticeAtual = 1;

    int vertices = grafo->numVertices;
    int visitados[vertices + 1];

    for (x = 0; x <= vertices; x++) visitados[x] = 0;
    visitados[1] = 1;

    printf("\nÁrvore geradora de custo mínimo:");

    while (verticeAtual < vertices) {
        for (i = 0, minimo = INFINITO; i <= vertices; i++)
            for (j = 0; j <= vertices; j++) {
                if (grafo->matrizAdjacencias[i][j] < minimo) {
                    if (visitados[i] != 0) {
                        minimo = grafo->matrizAdjacencias[i][j];
                        u = i;
                        v = j;
                    }
                }
            }

        if (visitados[u] == 0 || visitados[v] == 0) {
            printf(" (%d, %d)", u, v);
            verticeAtual++;
            custoMinimo += minimo;
            visitados[v] = 1;
        }

        grafo->matrizAdjacencias[u][v] = grafo->matrizAdjacencias[v][u] = INFINITO;
    }

    printf("\n\nCusto: %d\n\n", custoMinimo);
}

int **alocaMatriz(int qttVertices) {
    /* Se houver memória suficiente, aloca espaço para a matriz de adjacências de um grafo com qttVertices vértices.
    A matriz é criada com 1 linha e 1 coluna a mais, pois não existe vértice 0, portando linha 0 e coluna 0 serão desconsideradas. */

    int **M;
    int i;

    M = (int **) malloc(sizeof(int*)*(qttVertices + 1));

    if (M == NULL) {
        printf("Memoria insuficiente.\n");
        exit(1);
    }

    for (i = 0; i <= qttVertices; i++) {
        M[i] = (int*) malloc(sizeof(int)*(qttVertices + 1));

        if (M[i] == NULL) {
            printf("Memoria insuficiente.\n");
            exit(1);
        }
    }

    return M;
}

void liberaGrafo(Grafo *grafo) {
    int i;

    for (i = 0; i <= grafo->numVertices; i++)
        free(grafo->matrizAdjacencias[i]);

    free(grafo->matrizAdjacencias);
}

void criaGrafo(Grafo *grafo, char filename[]) {
    /* Se houver memória suficiente, cria um grafo com n vértices e m arestas.
     n e m, bem como os pesos para cada aresta são informados através de um arquivo cujo nome deverá ser passado. 
     O grafo será representado através de uma matriz de adjacências dentro da estrutura 'Grafo'*/

    FILE *arquivo;

    int vertices, arestas, i, j, k, u, v, custo;
    arquivo = fopen(filename, "r");

    if (arquivo == NULL) {
        printf("%s: arquivo não encontrado.\n", filename);
        exit(1);
    }

    fscanf(arquivo, "%d %d", &vertices, &arestas);
    grafo->numVertices = vertices;
    grafo->numArestas = arestas;

    grafo->matrizAdjacencias = alocaMatriz(vertices);

    /* Todos os pares de vértices são preechidos com um custo muito alto, o que significa dizer que não existe caminho entre eles. */
    for (i = 0; i <= vertices; i++) {
        for (j = 0; j <= vertices; j++) {
            grafo->matrizAdjacencias[i][j] = INFINITO;
        }
    }

    for (k = 0; k < arestas; k++) {
        fscanf(arquivo, "%d %d %d", &u, &v, &custo);
        grafo->matrizAdjacencias[u][v] = custo;
        grafo->matrizAdjacencias[v][u] = custo;
    }

    fclose(arquivo);
}

void imprimeMatrizAdjacencias(Grafo *grafo) {
    /* Imprime matriz de adjacencias de um dado grafo. (vértice 0 é desconsiderado) */

    int i, j;

    printf("\nMatriz de adjacencias:\n     ");
    for (int k = 1; k <= grafo->numVertices; k++) {
        printf(" %3d", k);
    }

    printf("\n");

    for (i = 1; i <= grafo->numVertices; i++) {
        for (j = 1; j <= grafo->numVertices; j++) {
            if (j == 1) printf(" %4d", i);

            if(grafo->matrizAdjacencias[i][j] == INFINITO)
                printf("   -");
            else
                printf(" %3d", grafo->matrizAdjacencias[i][j]);
        }

        printf("\n");

    }
}

typedef struct {
    int nomeArquivo;
    int imprimirGrafo;
} Args;

Args parsearArgumentos(int argc, char **argv) {
    /* Função utilitária para checar os argumentos. Ela verifica se o nome do arquivo foi passado e se o grafo deve ser impresso na tela.
    Retorna uma estrutura 'Args' com duas flags. */

    Args argumentos;

    argumentos.nomeArquivo = FALSE;
    argumentos.imprimirGrafo = FALSE;

    switch (argc) {
    case 1:
        break;

    case 2:
        argumentos.nomeArquivo = TRUE;
        break;

    case 3:
        if (strcmp("-p", argv[2]) == 0) {
            argumentos.nomeArquivo = TRUE;
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

int main(int argc, char **argv) {
    Grafo grafo;
    Args argumentos;
    char nomeArquivo[50];

    argumentos = parsearArgumentos(argc, argv);

    if (argumentos.nomeArquivo) criaGrafo(&grafo, argv[1]);
    else {
        printf("Insira o nome do arquivo e pressione Enter: ");
        scanf("%s", nomeArquivo);
        criaGrafo(&grafo, nomeArquivo);
    }

    if (argumentos.imprimirGrafo) imprimeMatrizAdjacencias(&grafo);

    prim(&grafo);
    liberaGrafo(&grafo);

    return 0;
}
