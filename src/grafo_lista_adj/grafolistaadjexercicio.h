//
// Created by samuel on 3/31/21.
//

#ifndef GRAFO_LISTA_DE_ADJACENCIAS_GRAFOLISTAADJEXERCICIO_H
#define GRAFO_LISTA_DE_ADJACENCIAS_GRAFOLISTAADJEXERCICIO_H

#define POS_INF 1000000000
#define NEG_INF -1000000000

#include <vector>
#include <string>
#include <deque>
#include <list>

typedef struct Aresta {
    int indiceOrigem;
    int indiceDestino;
    int peso;
} Aresta;

class GrafoListaAdj {

public:

    /**
   * A principio nao temos nenhuma ordenacao usando os rotulos.
   * Portanto, usaremos busca linear.
   **/
    int obterIndiceVertice(const std::string& rotuloVertice);

    /**
    * Lembrem-se:
    *       1) nao podemos inserir vertices com mesmo rotulo
    *       2) toda vez que inserirmos um novo vértice, precisaremos
    *          inserir um vetor para representar as conexões daquele
    *          vértice na lista de adjacências
    **/
    void inserirVertice(const std::string& rotuloVertice);

    /**
    * Sempre que o grafo for não ponderado, adicionaremos o peso 1,
    * por conveniência.
    **/
    void inserirArestaDirecionada(const std::string& rotuloVOrigem,const std::string& rotuloVDestino);

    void inserirArestaNaoDirecionada(const std::string& rotuloVOrigem, const std::string& rotuloVDestino);

    void inserirArestaNaoDirecionada(const std::string& rotuloVOrigem, const std::string& rotuloVDestino, int peso);

    /**
    * Inserir uma aresta entre rotuloVOrigem e rotuloVDestino com o peso
    * especificado.
    **/
    void inserirArestaDirecionada(const std::string& rotuloVOrigem, const std::string& rotuloVDestino, int peso);

    /**
    * Verifica se vértice rotuloVOrigem e vértice rotuloVDestino são
    * conectados.
    **/
    bool saoConectados(const std::string& rotuloVOrigem, const std::string& rotuloVDestino);

    /**
    * Verifica se há algum caminho entre vértice rotuloVOrigem e
    * vértice rotuloVDestino.
    * A melhor forma de fazer isto é reusando a função dfs.
    **/
    bool haCaminho(const std::string& rotuloVOrigem, const std::string& rotuloVDestino);

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
    int *bfs(const std::string& rotuloVOrigem);

    std::vector<std::string> getVertices();

    std::vector<std::vector<std::pair<int, int>>> getArestas();

    /**
 * Usamos o BellmanFord para encontrar menor caminho
 * em grafos com arestas com pesos negativos.
 * O BellmanFord consegue detectar ciclos negativos
 * e atribuir o valor NEG_INF (constante definida nesse arquivo)
 * aos vértices que pertençam ao ciclo.
 * POS_INF deve ser atribuído aos vértices inalcançáveis.
 * O aspecto negativo é sua complexidade de tempo: O(V*E).
 * Isto acontece pois, como possui arestas negativas, cada vértice
 * do grafo precisa ser processado V vezes.
 * Pseudo-código: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#bellman-ford
 **/
    int *bellmanFord(const std::string& rotuloVOrigem);


    bool relaxarArestasBellManFord(std::vector<int> *&distancias, std::vector<int> &predecessores);

    /**
    * Usamos o Dijkstra para encontrar menor caminho
    * em grafos sem arestas com pesos negativos.
    * O Dijkstra retorna respostas incorretas caso o grafo
    * possua arestas negativas, e portanto não consegue
    * detectar ciclos negativos. Este é o aspecto negativo.
    * POS_INF deve ser atribuído aos vértices inalcançáveis.
    * O aspecto positivo é sua complexidade de tempo: O(V+E).
    * Isto acontece pois, como o grafo não possui arestas negativas,
    * cada vértice do grafo precisa ser processado apenas 1 vez.
    * Pseudo-código: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#dijkstra
    * Ilustração: https://docs.google.com/drawings/d/1NmkJPHpcg8uVcDZ24FQiYs3uHR5n-rdm1AZwD74WiMY/edit?usp=sharing
    **/
    int *dijkstra(const std::string& rotuloVOrigem);

private:
    std::vector<std::string> vertices;

    //first é o indice do vertice, second é o peso (caso o grafo seja ponderado)
    std::vector<std::vector<std::pair<int, int>>> arestas;

    // um versão de aresta muito melhor de bom
    std::list<Aresta> listaArestas;

    /**
    * O argumento indicesVerticesVisitados serve para controlar quais
    * vertices já foram visitados.
    * Lembrando que DFS é uma função recursiva.
    **/
    void dfs(int indiceVertice, std::vector<bool> &indicesVerticesVisitados, std::string *cor);

    void dfs(int indiceVertice, std::vector<bool> &indicesVerticesVisitados);

    bool filaContemIndice(std::deque<int> &fila, int &elemento);

};


#endif //GRAFO_LISTA_DE_ADJACENCIAS_GRAFOLISTAADJEXERCICIO_H
