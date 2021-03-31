//
// Created by samuel on 3/31/21.
//

#ifndef GRAFO_LISTA_DE_ADJACENCIAS_GRAFOLISTAADJEXERCICIO_H
#define GRAFO_LISTA_DE_ADJACENCIAS_GRAFOLISTAADJEXERCICIO_H


#include <vector>
#include <string>

class GrafoListaAdj {
private:
    std::vector<std::string> vertices;

    //first é o indice do vertice, second é o peso (caso o grafo seja ponderado)
    std::vector<std::vector<std::pair<int, int>>> arestas;

    /**
    * A principio nao temos nenhuma ordenacao usando os rotulos.
    * Portanto, usaremos busca linear.
    **/
    int obterIndiceVertice(std::string rotuloVertice);

    /**
    * O argumento indicesVerticesVisitados serve para controlar quais
    * vertices já foram visitados.
    * Lembrando que DFS é uma função recursiva.
    **/
    void dfs(std::string rotuloVOrigem, bool *indicesVerticesVisitados);

public:
    /**
    * Lembrem-se:
    *       1) nao podemos inserir vertices com mesmo rotulo
    *       2) toda vez que inserirmos um novo vértice, precisaremos
    *          inserir um vetor para representar as conexões daquele
    *          vértice na lista de adjacências
    **/
    void inserirVertice(std::string rotuloVertice);

    /**
    * Sempre que o grafo for não ponderado, adicionaremos o peso 1,
    * por conveniência.
    **/
    void inserirArestaDirecionada(std::string rotuloVOrigem, std::string rotuloVDestino);

    void inserirArestaNaoDirecionada(std::string rotuloVOrigem, std::string rotuloVDestino);

    void inserirArestaNaoDirecionada(std::string rotuloVOrigem, std::string rotuloVDestino, int peso);

    /**
    * Inserir uma aresta entre rotuloVOrigem e rotuloVDestino com o peso
    * especificado.
    **/
    void inserirArestaDirecionada(std::string rotuloVOrigem, std::string rotuloVDestino, int peso);

    /**
    * Verifica se vértice rotuloVOrigem e vértice rotuloVDestino são
    * conectados.
    **/
    bool saoConectados(std::string rotuloVOrigem, std::string rotuloVDestino);

    /**
    * Verifica se há algum caminho entre vértice rotuloVOrigem e
    * vértice rotuloVDestino.
    * A melhor forma de fazer isto é reusando a função dfs.
    **/
    bool haCaminho(std::string rotuloVOrigem, std::string rotuloVDestino);

    /**
    * Muda os rótulos do vértices dos diferentes componentes para
    * cor1, cor2, etc.
    * Procura componentes partindo do vértice v0 ou v1, em ordem
    * crescente. As cores também são atribuídas nessa mesma ordem.
    * Retorna a quantidade de componentes.
    * A melhor forma de fazer isto é reusando a função dfs.
    **/
    int colorir();

    /**
    * Usa a abordagem de navegação BFS para listar as distâncias
    * entre o vértice rotuloVOrigem e cada um dos demais vértices.
    * A função BFS consegue listar a menor distância entre um vértice
    * e os demais se o grafo for NÃO-PONDERADO.
    * Retorna um vetor de inteiros com a quantidade de arestas
    * (distância) e o vértice rotuloVOrigem e cada um dos demais vértices.
    * Não é uma função recursiva.
    * É necessário utilizar a ED fila.
    **/
    int *bfs(std::string rotuloVOrigem);

    std::vector<std::string> getVertices();

    std::vector<std::vector<std::pair<int, int>>> getArestas();
};


#endif //GRAFO_LISTA_DE_ADJACENCIAS_GRAFOLISTAADJEXERCICIO_H
