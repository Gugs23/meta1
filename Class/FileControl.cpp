#include "FileControl.hpp"

vector<FileControl *> FileControl::allocs;

void FileControl::release(){
	for(int i = 0; i < allocs.size(); i++){
		delete allocs[i];
	}
	allocs.clear();
}

Mapa * FileControl::buildMapa(string &prob, FileControl * &fc){
	if(fc == NULL){
		fc = new FileControl();
		allocs.push_back(fc);
	}
	fc->readProblem(prob);
	return fc->getMapa();
}

Solucao * FileControl::buildSolucao(string &file1, FileControl * &fc, string file2){
	if(fc == NULL){
		fc = new FileControl();
		allocs.push_back(fc);
		fc->readProblem(file2);
	}
	fc->readSolution(file1);
	return fc->getSolution();
}

void FileControl::readProblem(string &fileProblem){
	bool _debug = false;
	fstream arq(fileProblem.c_str());

	if(arq.fail()){
		throw string("Impossível abrir arquivo de entrada (Problema)");
	}

	string leitura, tipo;
	int dim, n_itens, aux_int;
	double aux_double;

	debug("***Leitura***", "Iniciando arquivo prob");

	r(2) arq >> leitura;
	arq >> name;
	debug("Nome", name);
	//Leitura nome da instancia//

	r(3) arq >> leitura;
	getline(arq, tipo);
	debug("Tipo", tipo);
	//Leitura tipo relacao valor-peso//

	arq >> leitura;
	arq >> dim;
	debug("Dim", dim);
	//Leitura dimensão do problema//

	instancia = new Mapa(dim);
	if(tipo == "bounded-strongly-correlated")
		instancia->BSC();
	else if(tipo == "uncorrelated")
		instancia->UNC();
	else if (tipo == "uncorrelated-similar-weights")
		instancia->USW();

	r(3) arq >> leitura;
	arq >> n_itens;
	debug("Nitens", n_itens);
	//Leitura numeor de itens//

	r(3) arq >> leitura;
	arq >> aux_int;
	debug("Capacidade", aux_int);
	instancia->setCapacidade(aux_int);
	//Leitura capacidade//

	r(2) arq >> leitura;
	arq >> aux_int;
	debug("Time", aux_int);
	instancia->setMaxTime(aux_int);
	//Leitura tempo max//

	r(2) arq >> leitura;
	arq >> aux_double;
	debug("maxs", aux_double);
	instancia->setMinSpeed(aux_double);

	r(2) arq >> leitura;
	arq >> aux_double;
	debug("mins", aux_double);
	instancia->setMaxSpeed(aux_double);
	//Leiura velocidades//
	arq.ignore();
	getline(arq, leitura);
	getline(arq, leitura);

	for(int i = 0; i < dim; i++){
		int id;
		double cx, cy;
		arq >> id >> cx >> cy;
		instancia->addPonto(id, cx, cy);
		debug("Ponto", id << " " << cx << " " << cy);
	}
	arq.ignore();
	getline(arq, leitura);
	for(int i = 0; i < n_itens; i++){
		int id, valor, peso, local;
		arq >> id >> valor >> peso >> local;
		instancia->addItem(valor, peso, local, id);
		debug("Item", id << " " << valor << " " << peso << " " << local);
	}

	debug("***Leitura***", "Arquivo Prob finalizado");
	
	instancia->attVConst();

	arq.close();
}

void FileControl::readSolution(string &fileSolution){
	bool _debug = false;
	debug("***Leitura***", "Iniciando Arquivo Sol");
	char c;
	int n;
	fstream arq;
	arq.open(fileSolution.c_str());
	if(arq.fail()){
		throw string("Impossível abrir arquivo de entrada(Solucao)");
	}
	
	debug("Start", "Rota");
	
	solInstancia = new Solucao(instancia);
	
	while(true){
		arq >> c;
		if(c == ']'){
			break;
		}
		arq >> n;
		solInstancia->addPonto(n);
		debug("Ponto", n);
		//Lendo cidade que pertencem a rota//
	}
	
	debug("End", "Rota");
	
	debug("", "");
	
	debug("Start", "Itens");
	
	while(true){
		arq >> c;
		if(c == ']'){
			break;
		}
		arq >> n;
		solInstancia->addItem(n);
		debug("Item", n);
		//Lendo itens que compõe a solução//
	}
	debug("End", "Itens");
	arq.close();
	debug("***Leitura***", "Arquivo Sol Finalizado");
	instancia->addSolution(solInstancia);
}

FileControl::FileControl(){
	instancia = NULL;
	solInstancia = NULL;
}

Mapa * FileControl::getMapa(){
	return instancia;
}

Solucao * FileControl::getSolution(){
	return solInstancia;
}

string FileControl::getName(){
	return name;
}
