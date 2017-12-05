#include <iostream>
#include <cstdlib>
#include "Mapa.hpp"
#include "FileControl.hpp"
using namespace std;

int main(int argc, char * argv[]){
	if(argc != 2){
		cout << "Use ./Main <Arquivo Problema>" << endl;
		return 1;
	}
	string prob(argv[1]);
	Solucao * solution;
	FileControl * control = NULL;
	
	try{
		solution = new Solucao(FileControl::buildMapa(prob, control));
	} catch (string s){
		cout << s << endl;
	}
	
	int valor;
	double tempo;
	int maxIterations = 1;
	double alfaCidades = 0.1;
	double alfaItens = 0.5;

	srand(time(NULL));
	


	solution->greedySolution();
	int vls;
	double tls;
	//Solucao * k = solution->localSearch();
	//k->checkSolution(vls, tls);
	Solucao * s;
	Solucao * melhor = solution;
	int valorMelhor;
	melhor->checkSolution(valorMelhor, tempo);

	for(int i = 0; i < maxIterations; i++){
		s = new Solucao(FileControl::buildMapa(prob, control));
		s->greedyRandomizedSolution(0, alfaCidades, alfaItens);
		s->localSearch();
		s->checkSolution(valor, tempo);

		if(valor > valorMelhor){
			valorMelhor = valor;
			delete melhor;
			melhor = s;
		} else {
			delete s;
		}
	}
	cout << valorMelhor << endl;

	delete s;
	delete solution;
	//delete k;
	
	FileControl::release();
	
	return 0;
}
