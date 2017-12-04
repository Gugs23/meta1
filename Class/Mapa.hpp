#ifndef __MAPA_H
#define __MAPA_H

#include <vector>
#include <utility>
#include <cmath>
#include <iostream>
using std::vector;
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

#include "Item.hpp"
#include "Solucao.hpp"
#include "Ponto.hpp"

#define debug(K, V) if(_debug) cout << K << " => " << V << endl;
#define CoordX(A) itens_ponto[A].first.first
#define CoordY(A) itens_ponto[A].first.second
#define Itens(A) itens_ponto[A].second

class Mapa{
	
	friend class FileControl;

	public:
		
		Mapa(int);
		
		~Mapa();

		Mapa(const Mapa &);
		
		void setCapacidade(int);
		
		int getCapacidade();
		
		void setMaxTime(int);
		
		int getMaxTime();
		
		void setMinSpeed(double);
		
		double getMinSpeed();
		
		void setMaxSpeed(double);
		
		double getMaxSpeed();
		
		void addPonto(int, double, double);
		
		void addItem(int, int, int, int);
		
		int * operator [] (int);
		
		int getDim();
		
		int getNItens();
		
		int getPontoItem(int);
		
		int getPesoItem(int);
		
		int getValorItem(int);
		
		Ponto & getPonto(int);
		
		Item & getItem(int);
		
		double getVConst();
		
		void attVConst();
		
		void addSolution(Solucao *);
		
		void attRanks();
		
		vector<Item> getItensPonto(int);
	
	private:
		vector<Ponto> itens_ponto;
		/** Para cada ponto, cria uma lista com
		 * os itens naquele ponto;
		 **/
		 
		 vector<Item> itens;
		 /**Lista dos itens disponíveis**/
		 
		int ** distancia;
		/** Armazena a distância entre dois pontos **/
		
		unsigned int dataType;
		/** Relação peso<->valor
		 *  1 => correlated
		 *  2 => uncorrelated
		 *  3 => similar-weight
		 **/
		 
		 int dim;
		 /**Quantidade de pontos max**/
		 
		 int nPontos;
		 /**quantidade de pontos em uso**/

		int capacidade;
		/**Capacidade da mochila**/
		
		int max_time;
		/**Tempo max disponível**/
		
		double min_speed, max_speed;
		/**Velocidade max(mochila vazia) e min (mochila cheia)**/
		
		double v;
		/**Constante v decréscimo vel por unidade peso**/
		
		vector<Solucao *> solutions;
		/**Contem as cidades e itens em uma solucao lida em arquivo**/
		
		void BSC() { dataType = 1; };
		void UNC() { dataType = 2; };
		void USW() { dataType = 3; };
		
		
};

#endif
