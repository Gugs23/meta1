#ifndef __SOLUCAO_H
#define __SOLUCAO_H

#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using std::vector;
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;


class Mapa;

class Solucao{
	friend class Mapa;
	
	private:

		Mapa * instance;
		
		vector<int> * itensEscolhidos;
		
		vector<int> * pontosEscolhidos;
		
		vector<pair<int, vector<int> > > solution;
		
		int mergeData();
		
		void releaseMem();
		
		int state;
		
		void calculaRank();
		
		void pegaItens(int, int &, double &, int &);

		double ACCPT_FACTOR;

		void trocaPontos(int , int);
		
		void incluiCidade(int , int &, double &, int &);

		void trocaItens(int);
		
		bool checkWithWeight(int &, double &, int &);
		
		void removeCidade(int);

		bool merged;

		static Solucao * melhorIncluiCidade(Solucao *, vector<int>, int, double, int);
			
		static Solucao * melhorTrocaCidade(Solucao *, vector<int>, int, double, int);
		
		static Solucao * melhorTrocaItem(Solucao *, vector<int>, int, double, int);
		
		static Solucao * melhorTrocaOrdem(Solucao *, vector<int>, int, double, int);

		vector<int> calcPossiveis(int);

		Solucao * perturbar();

	public:

		static Solucao * melhorVizinho(Solucao *, int &, double &, int);

		Solucao(Mapa *);
		
		~Solucao();

		Solucao(const Solucao &);
		
		void addItem(int);
		
		void addPonto(int);
		
		bool checkSolution(int &, double &);
		
		bool validSolution();
		
		void greedySolution(double = 0);

		void print();

		Solucao * localSearch();

		Solucao * simulatedAnnealing(int iteratio, int perturb, double factor, int sucessLim, double temperature);
		
};

#endif
