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

	srand(time(NULL));
	
	solution->greedySolution();
	int vls;
	double tls;
	//Solucao * k = solution->localSearch();
	//k->checkSolution(vls, tls);
	Solucao * s = solution->simulatedAnnealing(100, 20, 0.5, 10, 750);
	Solucao * melhor = s;
	int valorMelhor;
	melhor->checkSolution(valorMelhor, tempo);

	for(int i = 0; i < 5; i++){
		s = solution->simulatedAnnealing(100, 20, 0.5, 10, 750);
		s->checkSolution(valor, tempo);

		if(valor > valorMelhor){
			valorMelhor = valor;
			delete melhor;
			melhor = s;
		}
	}

	cout << valorMelhor << endl;

	delete s;
	delete solution;
	//delete k;
	
	FileControl::release();
	
	return 0;
}
