//
// Created by samuel on 3/31/21.
//

#include "grafolistaadjexercicio.h"
#include <iostream>
#include <queue>

int GrafoListaAdj::obterIndiceVertice(const std::string &rotuloVertice) {
    //IMPLEMENTAR

    auto size = vertices.size();

    for (auto i = 0; i < size; i++) {
        if (vertices[i] == rotuloVertice)
            return i;
    }

    throw std::string("Vertice não encontrado: " + rotuloVertice);

}


void GrafoListaAdj::inserirVertice(const std::string &rotuloVertice) {


    try {
        obterIndiceVertice(rotuloVertice);
    }
    catch (std::string error) {
        vertices.push_back(rotuloVertice);
        arestas.push_back(std::vector<std::pair<int, int>>());
    }
}

void GrafoListaAdj::inserirArestaDirecionada(const std::string& rotuloVOrigem, const std::string& rotuloVDestino) {
    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
}

void GrafoListaAdj::inserirArestaNaoDirecionada(const std::string &rotuloVOrigem, const std::string &rotuloVDestino) {
    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
    inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, 1);
}

void GrafoListaAdj::inserirArestaNaoDirecionada(const std::string &rotuloVOrigem, const std::string &rotuloVDestino,
                                                int peso) {

    if (rotuloVOrigem == rotuloVDestino) {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
        return;
    }

    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
    inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, peso);
}

void GrafoListaAdj::inserirArestaDirecionada(const std::string& rotuloVOrigem, const std::string& rotuloVDestino, int peso) {

    try {
        auto indiceOrigem = obterIndiceVertice(rotuloVOrigem);
        auto indiceDestino = obterIndiceVertice(rotuloVDestino);
        Aresta aresta{indiceOrigem, indiceDestino, peso};

        arestas[indiceOrigem].push_back(std::pair<int, int>(indiceDestino, peso));

        listaArestas.push_back(aresta);
    }
    catch (std::string error) {
        std::cout << "Erro ao inserir Arestas: " << error << std::endl;
    }


}

bool GrafoListaAdj::saoConectados(const std::string& rotuloVOrigem, const std::string& rotuloVDestino) {
    //IMPLEMENTAR4

    try {
        auto indiceOrigem = obterIndiceVertice(rotuloVOrigem);
        auto indiceDestino = obterIndiceVertice(rotuloVDestino);
        auto arestasOrigem = arestas[indiceOrigem];

        for (auto pair : arestasOrigem) {
            if (pair.first == indiceDestino)
                return true;
        }
    }
    catch (std::string error) {
        std::cout << "Erro verificar conexão: " << error << std::endl;
    }

    return false;

}

bool GrafoListaAdj::haCaminho(const std::string& rotuloVOrigem, const std::string& rotuloVDestino) {
    try {
        auto indiceDestino = obterIndiceVertice(rotuloVDestino);
        auto indiceOrigem = obterIndiceVertice(rotuloVOrigem);

        std::vector<bool> visitados(vertices.size(), false);

        dfs(indiceOrigem, visitados);

        return visitados[indiceDestino];

    }
    catch (std::string error) {
        std::cerr << error << std::endl;
        return false;
    }


}

void GrafoListaAdj::dfs(int indiceVertice, std::vector<bool> &indicesVerticesVisitados) {
    dfs(indiceVertice, indicesVerticesVisitados, nullptr);
}

void GrafoListaAdj::dfs(int indiceVertice, std::vector<bool> &indicesVerticesVisitados, std::string *cor) {
    indicesVerticesVisitados[indiceVertice] = true;
    auto vizinhos = arestas[indiceVertice];
    if (cor != nullptr) {
        vertices[indiceVertice] = cor->c_str();
    }

    for (auto aresta : vizinhos) {
        if (!indicesVerticesVisitados[aresta.first])
            dfs(aresta.first, indicesVerticesVisitados, cor);
    }


}

int GrafoListaAdj::colorir() {
    std::vector<bool> visitados(vertices.size(), false);
    auto corAtual = 1;

    for (auto i = 0; i < arestas.size(); i++) {
        if (visitados[i])
            continue;

        auto cor = "cor" + std::to_string(corAtual);
        dfs(i, visitados, &cor);
        corAtual++;
    }

    return corAtual - 1;
}

int *GrafoListaAdj::bfs(const std::string& rotuloVOrigem) {
    auto indiceOrigem{obterIndiceVertice(rotuloVOrigem)};
    std::deque<int> fila;
    std::vector<bool> visitados(vertices.size(), false);
    auto distancias{new std::vector<int>(vertices.size(), 0)};

    fila.push_back(indiceOrigem);
    visitados[indiceOrigem] = true;

    while (!fila.empty()) {
        auto indice{fila.front()};

        for (auto aresta: arestas[indice]) {

            if (!visitados[aresta.first]) {
                visitados[aresta.first] = true;
                fila.push_back(aresta.first);
                distancias->at(aresta.first) = distancias->at(indice) + 1;

            } else if (filaContemIndice(fila, aresta.first)) {
                visitados[aresta.first] = true;
            }
        }

        fila.pop_front();

    }


    return distancias->data();

}

std::vector<std::string> GrafoListaAdj::getVertices() {
    return vertices;
}

std::vector<std::vector<std::pair<int, int>>> GrafoListaAdj::getArestas() {
    return arestas;
}

bool GrafoListaAdj::filaContemIndice(std::deque<int> &fila, int &elemento) {


    for (auto item : fila) {
        if (item == elemento)
            return true;
    }

    return false;
}


int *GrafoListaAdj::dijkstra(const std::string& rotuloVOrigem) {
    auto numeroDeVertices{vertices.size()};
    auto distancias{new std::vector<int>(numeroDeVertices, POS_INF)};
    std::priority_queue<std::pair<int, int>> filaDePrioridade;
    std::vector<bool> processados(numeroDeVertices, false);

    try {
        auto indice{obterIndiceVertice(rotuloVOrigem)};
        distancias->at(indice) = 0;
        filaDePrioridade.push({0, indice});


    }
    catch (std::string error) {
        std::cout << "não foi possivel encontrar o indice da origem " << error << std::endl;
        return distancias->data();
    }


    while (not filaDePrioridade.empty()) {
        auto indice = filaDePrioridade.top().second;
        filaDePrioridade.pop();
        if (processados[indice])continue;

        for (auto &aresta : arestas[indice]) {
            auto indiceDestino{aresta.first};
            auto peso{aresta.second};

            auto distancia = distancias->at(indice) < POS_INF ? distancias->at(indice) + peso : POS_INF;
            if (distancias->at(indiceDestino) > distancia) {
                distancias->at(indiceDestino) = distancia;
                filaDePrioridade.push({-distancias->at(indiceDestino), indiceDestino});
            }
        }
    }

    return distancias->data();

}

int *GrafoListaAdj::bellmanFord(const std::string& rotuloVOrigem) {
    //IMPLEMENTAR
    auto numeroDeVertices{vertices.size()};
    auto distancias{new std::vector<int>(numeroDeVertices, POS_INF)};
    auto predecessores{std::vector<int>(numeroDeVertices - 1)};

    try {
        auto indice{obterIndiceVertice(rotuloVOrigem)};
        distancias->at(indice) = 0;
    }
    catch (std::string error) {
        std::cout << "não foi possivel encontrar o indice da origem " << error << std::endl;
        return distancias->data();
    }


    for (int i = 0; i < numeroDeVertices - 1; i++) {
        if (not relaxarArestasBellManFord(distancias, predecessores))
            break;
    }


    for (auto &aresta: listaArestas) {
        auto distanciaOrigem = distancias->at(aresta.indiceOrigem);
        if (distanciaOrigem < POS_INF and distancias->at(aresta.indiceDestino) > distanciaOrigem + aresta.peso) {
            distancias->at(aresta.indiceDestino) = NEG_INF;

        }
    }


    return distancias->data();


}

bool GrafoListaAdj::relaxarArestasBellManFord(std::vector<int> *&distancias, std::vector<int> &predecessores) {
    auto houveMudanca{false};

    for (auto &aresta: listaArestas) {
        auto distanciaOrigem = distancias->at(aresta.indiceOrigem);
        if (distanciaOrigem < POS_INF or aresta.peso < 0) {

            if (distancias->at(aresta.indiceDestino) > distanciaOrigem + aresta.peso) {
                distancias->at(aresta.indiceDestino) = distanciaOrigem + aresta.peso;
                predecessores[aresta.indiceDestino] = aresta.indiceOrigem;
                houveMudanca = true;
            }

        }
    }

    return houveMudanca;
}



