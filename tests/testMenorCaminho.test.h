
#include "../src/grafo_lista_adj/grafolistaadjexercicio.h"
#include "gtest/gtest.h"

#ifndef TEST_MENOR_CAMINHO_H
#define TEST_MENOR_CAMINHO_H


class MenorCaminhoTest : public ::testing::Test {
protected:
    virtual void TearDown() {
        delete (grafo);
    }

    virtual void SetUp() {
        grafo = new GrafoListaAdj();
    }

    void inserirVertices(GrafoListaAdj *grafo, int ini, int fim) {
        for (int i = ini; i <= fim; i++) {
            string rotulo;
            std::stringstream sstm;
            sstm << "v" << i;
            rotulo = sstm.str();
            grafo->inserirVertice(rotulo);
        }
    }

    GrafoListaAdj *grafo;
};

void construirGrafoPonderado(GrafoListaAdj *grafo) {
    //este é o grafo ponderado
    //https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-ponderado-representacao-matriz-preenchido.png
    //embora não estamos representando com matriz de adjacências

    grafo->inserirArestaNaoDirecionada("v1", "v2", 6);
    grafo->inserirArestaNaoDirecionada("v1", "v3", 4);
    grafo->inserirArestaNaoDirecionada("v2", "v4", 5);
    grafo->inserirArestaNaoDirecionada("v3", "v4", 2);
    grafo->inserirArestaNaoDirecionada("v3", "v5", 4);
    grafo->inserirArestaNaoDirecionada("v4", "v6", 5);
    grafo->inserirArestaNaoDirecionada("v4", "v7", 5);
    grafo->inserirArestaNaoDirecionada("v5", "v9", 9);
    grafo->inserirArestaNaoDirecionada("v6", "v8", 6);
    grafo->inserirArestaNaoDirecionada("v8", "v9", 8);
}


TEST_F(MenorCaminhoTest, BellmanFordGrafoSemCicloNegativo) {
    inserirVertices(grafo, 1, 9);
    construirGrafoPonderado(grafo);

    int *distancias = grafo->bellmanFord("v1");
    EXPECT_EQ(distancias[0], 0);
    EXPECT_EQ(distancias[1], 6);
    EXPECT_EQ(distancias[2], 4);
    EXPECT_EQ(distancias[3], 6);
    EXPECT_EQ(distancias[4], 8);
    EXPECT_EQ(distancias[5], 11);
    EXPECT_EQ(distancias[6], 11);
    EXPECT_EQ(distancias[7], 17);
    EXPECT_EQ(distancias[8], 17);
    free(distancias);

    distancias = grafo->bellmanFord("v7");
    EXPECT_EQ(distancias[0], 11);
    EXPECT_EQ(distancias[1], 10);
    EXPECT_EQ(distancias[2], 7);
    EXPECT_EQ(distancias[3], 5);
    EXPECT_EQ(distancias[4], 11);
    EXPECT_EQ(distancias[5], 10);
    EXPECT_EQ(distancias[6], 0);
    EXPECT_EQ(distancias[7], 16);
    EXPECT_EQ(distancias[8], 20);
    free(distancias);

    distancias = grafo->bellmanFord("v9");
    EXPECT_EQ(distancias[0], 17);
    EXPECT_EQ(distancias[1], 20);
    EXPECT_EQ(distancias[2], 13);
    EXPECT_EQ(distancias[3], 15);
    EXPECT_EQ(distancias[4], 9);
    EXPECT_EQ(distancias[5], 14);
    EXPECT_EQ(distancias[6], 20);
    EXPECT_EQ(distancias[7], 8);
    EXPECT_EQ(distancias[8], 0);
    free(distancias);
}

TEST_F(MenorCaminhoTest, BellmanFordGrafoComLacoNegativo) {
    inserirVertices(grafo, 1, 9);
    construirGrafoPonderado(grafo);
    grafo->inserirArestaNaoDirecionada("v1", "v1", -2);

//grafo com laço com peso negativo em v1
//como o grafo só tem um componente
//então todas as distâncias podem ser diminuídas

    int *distancias = grafo->bellmanFord("v1");
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(distancias[i], NEG_INF);
    free(distancias);

//não interessa o vértice de origem,
//todas as distâncias sempre podem ser diminuídas
    distancias = grafo->bellmanFord("v5");
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(distancias[i], NEG_INF);
    free(distancias);

//não interessa o vértice de origem,
//todas as distâncias sempre podem ser diminuídas
    distancias = grafo->bellmanFord("v9");
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(distancias[i], NEG_INF);
    free(distancias);
}

TEST_F(MenorCaminhoTest, BellmanFordGrafoCom2ComponentesECicloNegativo) {
//componente 1
    inserirVertices(grafo, 1, 9);
    construirGrafoPonderado(grafo);
    grafo->inserirArestaNaoDirecionada("v1", "v1", -2);

//grafo com laço com peso negativo em v1
//como o grafo tem dois componentes
//então NÃO SÃO todas as distâncias QUE podem ser diminuídas
//as distâncias QUE podem ser diminuídas envolvem
//todos os vértices que são alcancáveis a partir de v1
//ou seja: v1, v2, v3, v4, v5, v6, v7, v8, v9

//componente 2
    inserirVertices(grafo, 10, 12);
    grafo->inserirArestaNaoDirecionada("v10", "v11", 10);
    grafo->inserirArestaNaoDirecionada("v10", "v12", 15);

    int *distancias = grafo->bellmanFord("v10");
//componente com ciclos negativos
//{v1,v2,v3,v4,v5,v6,v7,v8,v9}
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(distancias[i], NEG_INF);
/* EXPLICAÇÃO PARA RESULTADO ACIMA */
//infelizmente, o BellmanFord não retorna POS_INF
//pois se o algoritmo encontrar um ciclo negativo
//no grafo, então todos os nós do ciclo negativo
//recebem NEG_INF
//isso acontece mesmo que não exista caminho entre
//v10 e {v1,v2,v3,v4,v5,v6,v7,v8,v9}
//===============================================
//componente sem ciclos negativos
//{v10,v11,v12}
    EXPECT_EQ(distancias[9], 0);
    EXPECT_EQ(distancias[10], 10);
    EXPECT_EQ(distancias[11], 15);
    free(distancias);

    distancias = grafo->bellmanFord("v11");
//componente com ciclos negativos
//{v1,v2,v3,v4,v5,v6,v7,v8,v9}
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(distancias[i], NEG_INF);
//componente sem ciclos negativos
//{v10,v11,v12}
    EXPECT_EQ(distancias[9], 10);
    EXPECT_EQ(distancias[10], 0);
    EXPECT_EQ(distancias[11], 25);
    free(distancias);

    distancias = grafo->bellmanFord("v12");
//componente com ciclos negativos
//{v1,v2,v3,v4,v5,v6,v7,v8,v9}
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(distancias[i], NEG_INF);
//componente sem ciclos negativos
//{v10,v11,v12}
    EXPECT_EQ(distancias[9], 15);
    EXPECT_EQ(distancias[10], 25);
    EXPECT_EQ(distancias[11], 0);
    free(distancias);

    distancias = grafo->bellmanFord("v1");
//componente com ciclos negativos
//{v1,v2,v3,v4,v5,v6,v7,v8,v9}
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(distancias[i], NEG_INF);
//componente sem ciclos negativos
//{v10,v11,v12}
    for (int i = 9; i < 12; i++)
        EXPECT_EQ(distancias[i], POS_INF);
    free(distancias);

    distancias = grafo->bellmanFord("v5");
//componente com ciclos negativos
//{v1,v2,v3,v4,v5,v6,v7,v8,v9}
    for (int i = 0; i < 9; i++)
        EXPECT_EQ(distancias[i], NEG_INF);
//componente sem ciclos negativos
//{v10,v11,v12}
    for (int i = 9; i < 12; i++)
        EXPECT_EQ(distancias[i], POS_INF);
    free(distancias);
}

TEST_F(MenorCaminhoTest, DijkstraGrafoSemCicloNegativo) {
    inserirVertices(grafo, 1, 9);
    construirGrafoPonderado(grafo);

    int *distancias = grafo->dijkstra("v1");
    EXPECT_EQ(distancias[0], 0);
    EXPECT_EQ(distancias[1], 6);
    EXPECT_EQ(distancias[2], 4);
    EXPECT_EQ(distancias[3], 6);
    EXPECT_EQ(distancias[4], 8);
    EXPECT_EQ(distancias[5], 11);
    EXPECT_EQ(distancias[6], 11);
    EXPECT_EQ(distancias[7], 17);
    EXPECT_EQ(distancias[8], 17);
    free(distancias);

    distancias = grafo->dijkstra("v7");
    EXPECT_EQ(distancias[0], 11);
    EXPECT_EQ(distancias[1], 10);
    EXPECT_EQ(distancias[2], 7);
    EXPECT_EQ(distancias[3], 5);
    EXPECT_EQ(distancias[4], 11);
    EXPECT_EQ(distancias[5], 10);
    EXPECT_EQ(distancias[6], 0);
    EXPECT_EQ(distancias[7], 16);
    EXPECT_EQ(distancias[8], 20);
    free(distancias);

    distancias = grafo->dijkstra("v9");
    EXPECT_EQ(distancias[0], 17);
    EXPECT_EQ(distancias[1], 20);
    EXPECT_EQ(distancias[2], 13);
    EXPECT_EQ(distancias[3], 15);
    EXPECT_EQ(distancias[4], 9);
    EXPECT_EQ(distancias[5], 14);
    EXPECT_EQ(distancias[6], 20);
    EXPECT_EQ(distancias[7], 8);
    EXPECT_EQ(distancias[8], 0);
    free(distancias);
}

#endif