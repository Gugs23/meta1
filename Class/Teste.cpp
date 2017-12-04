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
    Solucao * s = new Solucao(*solution);

    for(int i = 0; i < solution->itensEscolhidos->size(); i++){
        cout << solution->itensEscolhidos->operator[](i) << " ";
        cout << s->itensEscolhidos->operator[](i) << endl;
    }

cout << " ------------- " << endl;
    for(int i = 0; i < solution->pontosEscolhidos->size(); i++){
        cout << solution->pontosEscolhidos->operator[](i) << " ";
        cout << s->pontosEscolhidos->operator[](i) << endl;
    }

        
    solution->checkSolution(valor, tempo);
    for(int i = 0; i < solution->solution.size(); i++){
        cout << solution->solution[i].first << " ";
    }

    cout << endl;

    //s->greedySolution();
    s->checkSolution(valor, tempo);


    for(int i = 0; i < s->solution.size(); i++){
        cout << s->solution[i].first << " ";
    }

    cout << endl;

	FileControl::release();
	
	return 0;
}
