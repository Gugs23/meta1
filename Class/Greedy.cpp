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
	
	if(!solution->checkSolution(valor, tempo)){
		solution->validSolution();
	}

	Solucao * s = solution->localSearch();

	if(s->checkSolution(valor, tempo)){
		cout << valor << endl;
	} else {
		solution->validSolution();
	}

	delete s;
	delete solution;
	
	FileControl::release();
	
	return 0;
}
