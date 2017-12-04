#include <iostream>
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
	
	solution->greedySolution();
	
	if(solution->checkSolution(valor, tempo)){
		cout <<"Greedy => "<< valor;
	} else {
		solution->validSolution();
	}

	Solucao * s = solution->localSearch();

	if(s->checkSolution(valor, tempo)){
		cout <<"      LS => "<< valor << endl;
	} else {
		solution->validSolution();
    }
    
    delete solution, s;
	
	FileControl::release();
	
	return 0;
}
