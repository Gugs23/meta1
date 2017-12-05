#include "Mapa.hpp"

Mapa::Mapa(int cdim){
	dim = cdim + 1;
	distancia = new int * [dim];
	for(int i = 0; i < dim; i++){
		distancia[i] = new int [dim];
		for(int j = 0; j < dim; j++){
			distancia[i][j] = -1;
		}
	}
	nPontos = 1;
	capacidade = -1;
	max_speed = -1;
	max_time = -1;
	min_speed = -1;
	itens.push_back(Item());
	itens_ponto.push_back(Ponto());
	
}

Mapa::Mapa(const Mapa &ori){
	dim = ori.dim;
	distancia = new int * [dim];
	for(int i = 0; i < dim; i++){
		distancia[i] = new int [dim];
		for(int j = 0; j < dim; j++){
			distancia[i][j] = ori.distancia[i][j];
		}
	}
	nPontos = ori.nPontos;
	capacidade = ori.capacidade;
	max_speed = ori.max_speed;
	max_time = ori.max_time;
	min_speed = ori.min_speed;
	itens = ori.itens;
	itens_ponto = ori.itens_ponto;
	attVConst();
}

Mapa::~Mapa(){
	for(int i = 0;i < dim; i++){
		delete [] distancia[i];
	}
	delete [] distancia;
}

int Mapa::getCapacidade(){
	return capacidade;
}

int Mapa::getMaxTime(){
	return max_time;
}

double Mapa::getMaxSpeed(){
	return max_speed;
}

double Mapa::getMinSpeed(){
	return min_speed;
}

void Mapa::setCapacidade(int cCap){
	capacidade = cCap;
}

void Mapa::setMaxTime(int cTime){
	max_time = cTime;
}

void Mapa::setMaxSpeed(double cspeed){
	max_speed = cspeed;
}

void Mapa::setMinSpeed(double cspeed){
	min_speed = cspeed;
}

void Mapa::addPonto(int id, double cx, double cy){
	itens_ponto.push_back(Ponto(cx, cy, id));
	/**insere ponto na lista**/
	
	int atual = nPontos++;
	for(int i = 1; i < nPontos; i++){
		distancia[i][atual] = distancia[atual][i] = itens_ponto[atual].distancia(itens_ponto[i]);
	}
	/**Calculando as distancias**/
}

void Mapa::addItem(int valor, int peso, int ponto, int id){
	itens.push_back(Item(valor, peso, ponto, id));
	itens_ponto[ponto].addItem(id, valor);
}

void Mapa::addSolution(Solucao * nova){
	solutions.push_back(nova);
}

int * Mapa::operator [] (int i){
	return distancia[i];
}

int Mapa::getDim(){
	return dim - 1;
}

vector<Item> Mapa::getItensPonto(int nPt){
	vector<int> * itPt = itens_ponto[nPt].listaItens();
	vector<Item> aux;
	for(int i = 0; i < itPt->size(); i++){
		aux.push_back(itens[itPt->operator[](i)]);
	}
	return aux;
}

int Mapa::getNItens(){
	return itens.size();
}

int Mapa::getPontoItem(int nItem){
	return itens[nItem].ponto;
}

int Mapa::getPesoItem(int nItem){
	return itens[nItem].peso;
}

int Mapa::getValorItem(int nItem){
	return itens[nItem].valor;
}

Item & Mapa::getItem(int nItem){
	return itens[nItem];
}

Ponto & Mapa::getPonto(int nPonto){
	return itens_ponto[nPonto];
}

double Mapa::getVConst(){
	return v = (max_speed - min_speed)/capacidade;
}

void Mapa::attVConst(){
	v = (max_speed - min_speed)/capacidade;
}

void Mapa::attRanks(){
	vector<int> * lista;
	for(int i = 0; i < itens_ponto.size(); i++){
		lista = itens_ponto[i].listaItens();
		cout << i << " " << lista->size() << endl;
		for(int j = 0; j < lista->size(); j++){
			itens_ponto[i].attRank(itens[lista->operator[](j)].rank);
		}
		cout << itens_ponto[i].rank << endl;
	}
}
