#include "Ponto.hpp"

Ponto::Ponto(double cx, double cy, int cid): x(cx), y(cy), id(cid){
	rank = 0;
	menorPeso = -1;
}

int Ponto::distancia(const Ponto &pp) const {
	double dx = x - pp.x;
	double dy = y - pp.y;
	return ceil(sqrt(dx * dx + dy * dy));
}

void Ponto::attRank(double value){
	rank += value;
}

vector<int> * Ponto::listaItens(){
	return &itens;
}

bool Ponto::operator < (const Ponto &outro) const{
	return rank > outro.rank;
}

void Ponto::addItem(int nItem, int peso){
	if(menorPeso == -1){
		menorPeso = peso;
	}
	
	menorPeso = min(menorPeso, peso);
	itens.push_back(nItem);
}
