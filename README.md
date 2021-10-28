# ep1-grafos

Escreva um programa que receba pela linha de comando o nome de um arquivo contendo a descrição de
um grafo. O arquivo fornecido ao programa deverá ter o seguinte layout:

```
n m
u1 v1 c1
u2 v2 c2
...
um vm cm
```

onde n é a quantidade de vértices, m a quantidade de arestas, ui e vi são as extremidades da aresta i e ci é
o custo da aresta i. 

Arquivo de exemplo (_grafos_):

```
5 7
1 2 5
1 5 10
2 3 4
2 4 13
2 5 2
3 4 7
5 4 6
```

Utilizando o Algoritmo de Kruskal ou o Algoritmo de Prim, seu programa deverá calcular e exibir as arestas
que constituem uma árvore geradora de custo mínimo do grafo. Para o grafo acima, a saída do programa
poderia ser:

```
Árvore geradora de custo mínimo: (2, 5) (2, 3) (1, 2) (5, 4)

Custo: 17
```

---

## Rodando a aplicação

Compile o arquivo ep1.c:

```bash
$gcc ep1.c -o ep1
```

Execute o binário e passe o nome do arquivo quando for solicitado:

```bash
$./ep1
Insira o nome do arquivo e pressione Enter: grafo

Árvore geradora de custo mínimo: (1, 2) (2, 5) (2, 3) (5, 4)

Custo: 17
```

Ao executar podemos passar o nome do arquivo diretamente:
```bash
$./ep1 grafo
```

> obs.: Em ambos os casos, o arquivo deve estar no mesmo diretório da aplicação.

&nbsp;

Também temos a opção de imprimir a matriz de adjacencias que é criada para o grafo, basta passar a flag `-p`:

```bash
$./ep1 grafo -p

Matriz de adjacencias:
        1   2   3   4   5
    1   -   5   -   -  10
    2   5   -   4  13   2
    3   -   4   -   7   -
    4   -  13   7   -   6
    5  10   2   -   6   -

Árvore geradora de custo mínimo: (1, 2) (2, 5) (2, 3) (5, 4)

Custo: 17
```
