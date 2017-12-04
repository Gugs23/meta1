#ifndef __PONTO_H
#define __PONTO_H

#include <iostream>
using std::min;
#include <vector>
using std::vector;
#include <cmath>

class Ponto{
	private:
	
	
	public:
		int id;
	
		double x, y;
		
		int menorPeso;
		
		vector<int> itens;
		
		double rank;
		
		Ponto(double = 0, double = 0, int = -1);
		
		int distancia(const Ponto &) const;
		
		void attRank(double);
		
		vector<int> * listaItens();
		
		bool operator < (const Ponto &) const;
		
		void addItem(int, int);

};

#endif
