#ifndef __FILE_CONTROLLER_H
#define __FILE_CONTROLLER_H

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include "Mapa.hpp"
#include "Solucao.hpp"

using std::string;
using std::fstream;
using std::cout;
using std::endl;


#define r(A) for(int i = 0; i < A; i++)
#define debug(K, V) if(_debug) cout << K << " => " << V << endl;

class FileControl{
	private:
		FileControl();
		
		void readProblem(string &);
		
		void readSolution(string &);
		
		Mapa * instancia;
		/**Ponteiro para o ultimo problmea lido**/
		
		Solucao * solInstancia;
		/**Ponteiro para a última solução lida. Solução está vinculada ao último problema lido**/
		
		string name;
		
		static vector<FileControl *> allocs;
	
	public:
		static Mapa * buildMapa(string &, FileControl * &);
		
		static Solucao * buildSolucao(string &, FileControl * &, string = "");
		
		Mapa * getMapa();
		/**Recupera instancia Mapa equivalente ao problema**/
		
		Solucao * getSolution();
		/**Recupera instancia da ultima solucao lida**/
		
		string getName();
			
		static void release();

};


#endif
