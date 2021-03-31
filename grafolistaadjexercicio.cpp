//
// Created by samuel on 3/31/21.
//

#include "grafolistaadjexercicio.h"

int GrafoListaAdj::obterIndiceVertice(std::string rotuloVertice) {
    //IMPLEMENTAR
}

void GrafoListaAdj::dfs(std::string rotuloVOrigem, bool *indicesVerticesVisitados) {
    //IMPLEMENTAR
}

void GrafoListaAdj::inserirVertice(std::string rotuloVertice) {
    //IMPLEMENTAR
}

void GrafoListaAdj::inserirArestaDirecionada(std::string rotuloVOrigem, std::string rotuloVDestino) {
    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
}

void GrafoListaAdj::inserirArestaNaoDirecionada(std::string rotuloVOrigem, std::string rotuloVDestino) {
    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
    inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, 1);
}

void GrafoListaAdj::inserirArestaNaoDirecionada(std::string rotuloVOrigem, std::string rotuloVDestino, int peso) {
    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
    inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, peso);
}

void GrafoListaAdj::inserirArestaDirecionada(std::string rotuloVOrigem, std::string rotuloVDestino, int peso) {
    //IMPLEMENTAR
}

bool GrafoListaAdj::saoConectados(std::string rotuloVOrigem, std::string rotuloVDestino) {
    //IMPLEMENTAR
}

bool GrafoListaAdj::haCaminho(std::string rotuloVOrigem, std::string rotuloVDestino) {
    //IMPLEMENTAR
}

int GrafoListaAdj::colorir() {
    //IMPLEMENTAR
}

int *GrafoListaAdj::bfs(std::string rotuloVOrigem) {
    //IMPLEMENTAR
}

std::vector<std::string> GrafoListaAdj::getVertices() {
    return vertices;
}

std::vector<std::vector<std::pair<int, int>>> GrafoListaAdj::getArestas() {
    return arestas;
}

