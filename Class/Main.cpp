#include <iostream>
#include "Mapa.hpp"
#include "FileControl.hpp"
using namespace std;

int main(int argc, char * argv[]){
	if(argc != 3){
		cout << "Use ./Main <Arquivo Problema> <Arquivo Solucao>" << endl;
		return 1;
	}
	string prob(argv[1]);
	string sol(argv[2]);
	Solucao * solution;
	FileControl * control = NULL;
	
	try{
		solution = FileControl::buildSolucao(sol, control, prob);
		if(control == NULL){
			cout << "Que" << endl;
		}
	} catch (string s){
		cout << s << endl;
	}
	
	int valor;
	double tempo;
	
	if(solution->checkSolution(valor, tempo)){
		cout << "Valor => " << valor << " Tempo => " << tempo << endl;
	} else {
		solution->validSolution();
	}
	
	FileControl::release();
	
	return 0;
}
