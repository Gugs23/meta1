#include "Solucao.hpp"
#include "Mapa.hpp"

Solucao::Solucao(Mapa * inst){
	merged = false;
	state = 5;
	instance = inst;
	itensEscolhidos = new vector<int>;
	pontosEscolhidos = new vector<int>;
}

Solucao::~Solucao(){
	delete instance;
	releaseMem();
}

Solucao::Solucao(const Solucao &base){
	merged = base.merged;
	state = base.state;
	instance = new Mapa(*(base.instance));
	itensEscolhidos = new vector<int>;
	pontosEscolhidos = new vector<int>;
	*itensEscolhidos = *(base.itensEscolhidos);
	*pontosEscolhidos = *(base.pontosEscolhidos);
	solution = base.solution;
}

void Solucao::releaseMem(){
	if(itensEscolhidos){
		delete itensEscolhidos;
		itensEscolhidos = NULL;
	}
	
	if(pontosEscolhidos){
		delete pontosEscolhidos;
		pontosEscolhidos = NULL;
	}
}

int Solucao::mergeData(){
	solution.clear();
	merged = true;
	int pontoAtual = 0;
	int nMerged = 0;
	int tamanho = instance->getDim();
	vector<int> aux[tamanho];
	
	pontoAtual = instance->getPontoItem(itensEscolhidos->operator[](0));
	aux[pontoAtual].push_back(itensEscolhidos->operator[](0));
	
	for(int i = 1; i < itensEscolhidos->size(); i++){
		pontoAtual = instance->getPontoItem(itensEscolhidos->operator[](i));
		aux[pontoAtual].push_back(itensEscolhidos->operator[](i));
		if(itensEscolhidos->operator[](i) == itensEscolhidos->operator[](i-1)){
			return state = 3;
		}
	}
	
	for(int i = 0; i < pontosEscolhidos->size(); i++){
		solution.push_back(make_pair(pontosEscolhidos->operator[](i), aux[pontosEscolhidos->operator[](i)]));
		nMerged += aux[pontosEscolhidos->operator[](i)].size();
	}
	
	if(nMerged != itensEscolhidos->size()){
		return state = 4;
	}

	solution.push_back(make_pair(instance->getDim(), vector<int>()));
	
	return 5;
}

void Solucao::calculaRank(){
	/**Calcula o rank de cada ponto.
	 * O rank é dado de acordo com a colocação do ratio (valor/peso) 
	 * de cada item do ponto.
	 **/
	vector<Item> lista;
	int total = instance->getNItens();
	double rank;
	for(int i = 0; i < total ; i++){
		lista.push_back(instance->getItem(i));
	}
	
	sort(lista.begin(), lista.end());
	
	int j = total;
	
	for(int i = 0; i < total ; i++){
		rank = ((double)i) / total;
		instance->getItem(i).rank = rank;
	}
	
	instance->attRanks();
}

void Solucao::greedySolution(double accp){
	if(accp != 0){
		ACCPT_FACTOR = accp;
	}
	delete itensEscolhidos;
	delete pontosEscolhidos;

	calculaRank();

	itensEscolhidos = new vector<int>();
	pontosEscolhidos = new vector<int>();

	int pontoAtual = 1;
	int pontoDestino = instance->getDim();
	int pesoAcum = 0;
	int valorAcum = 0;
	int dAtual, dFinal;
	double tempoAtualI, tempoIFinal, tempoNess;
	double tempoAcum = 0;
	double timeLimit = instance->getMaxTime();
	double v = instance->getVConst();
	double maxSpeed = instance->getMaxSpeed();
	
	vector<Ponto> aux;
	
	for(int i = 2; i < instance->getDim(); i++){
		aux.push_back(instance->getPonto(i));
	}
	
	sort(aux.begin(), aux.end());
	/**Pontos ordenados de acordo com o rank **/
	for(int i = 0; i < aux.size(); i++){
		//cout << " ------------------------------ " << endl << endl << endl;
		/**Verifica viabilidade de viajar para aquele ponto. Ou seja:
		 * 1: É possível pegar o item de menor peso daquele ponto (capacidade)
		 * 2: Existe tempo o suficiente sobrando para ir até o ponto, pegar o item de menor peso, e ir até o final?
		 **/
		// cout << "Testando cidade " << aux[i].id << endl;
		 dAtual = instance->operator[](pontoAtual)[aux[i].id];
		 dFinal = instance->operator[](aux[i].id)[pontoDestino];
		 tempoAtualI = dAtual/(maxSpeed - v * pesoAcum);
		 tempoIFinal =  dFinal/(maxSpeed - v *(pesoAcum + aux[i].menorPeso));
		 
		 tempoNess = tempoAtualI + tempoIFinal;
		 
		// cout << "Tempo ness " << tempoNess << endl;
		 
		 if(tempoNess + tempoAcum > timeLimit or pesoAcum + aux[i].menorPeso > instance->getCapacidade()){
			 continue;
		 }
		 
		 //cout << "Passei no teste, vou para a cidade " << aux[i].id << endl;
		 
		 /**Cidade escolhida, atualiza tempo*/
		 tempoAcum += tempoAtualI;
		 
		 /**Existe viabilidade de ir para aquela cidade. Faz a viagem, e pega itens.**/
		 
		 pegaItens(aux[i].id, pesoAcum, tempoAcum, valorAcum);
		 pontosEscolhidos->push_back(aux[i].id);
		 pontoAtual = aux[i].id;
	}
	
	//cout << " ----------- SOLUCAO CONSTRUIDA ------------------- " << endl;
	sort(itensEscolhidos->begin(), itensEscolhidos->end());

	mergeData();
	
}

void Solucao::greedyRandomizedSolution(double accp, double alfaCidades, double alfaItens){
	if(accp != 0){
		ACCPT_FACTOR = accp;
	}
	delete itensEscolhidos;
	delete pontosEscolhidos;

	itensEscolhidos = new vector<int>();
	pontosEscolhidos = new vector<int>();

	int pontoAtual = 1;
	int pontoDestino = instance->getDim();
	int pesoAcum = 0;
	int valorAcum = 0;
	int dAtual, dFinal;
	double tempoAtualI, tempoIFinal, tempoNess;
	double tempoAcum = 0;
	double timeLimit = instance->getMaxTime();
	double v = instance->getVConst();
	double maxSpeed = instance->getMaxSpeed();
	
	vector<Ponto> aux;
	
	calculaRank();
	for(int i = 2; i < instance->getDim(); i++){
		aux.push_back(instance->getPonto(i));
	}
	vector< pair <int, Ponto> > rcl;
	sort(aux.begin(), aux.end());
	// for(int i = 0; i < aux.size(); i++){
	// 	cout << "rank" << aux[i].rank << endl;
	// }
	/**Pontos ordenados de acordo com o rank **/

	bool parada = false;
	while(!parada){
		//cout << " ------------------------------ " << endl << endl << endl;
		/**Verifica viabilidade de viajar para aquele ponto. Ou seja:
		 * 1: É possível pegar o item de menor peso daquele ponto (capacidade)
		 * 2: Existe tempo o suficiente sobrando para ir até o ponto, pegar o item de menor peso, e ir até o final?
		 **/
		 
		for(int i = 0; i < aux.size() && rcl.size() <= ((int) (alfaCidades*aux.size())); i++) {
			dAtual = instance->operator[](pontoAtual)[aux[i].id];
			dFinal = instance->operator[](aux[i].id)[pontoDestino];
			tempoAtualI = dAtual/(maxSpeed - v * pesoAcum);
			tempoIFinal =  dFinal/(maxSpeed - v *(pesoAcum + aux[i].menorPeso));
			
			tempoNess = tempoAtualI + tempoIFinal;
			
			// cout << "Tempo ness " << tempoNess << endl;
			
			if(tempoNess + tempoAcum > timeLimit or pesoAcum + aux[i].menorPeso > instance->getCapacidade()){
				continue;
			} else {
				rcl.push_back(make_pair(i,aux[i]));
			}
		}
		if(rcl.size() == 0){
			parada = true;
			break;
		} 
		int lim = rand()%rcl.size();

		dAtual = instance->operator[](pontoAtual)[rcl[lim].second.id];
		dFinal = instance->operator[](rcl[lim].second.id)[pontoDestino];
		tempoAtualI = dAtual/(maxSpeed - v * pesoAcum);
		tempoIFinal =  dFinal/(maxSpeed - v *(pesoAcum + rcl[lim].second.menorPeso));
		
		tempoNess = tempoAtualI + tempoIFinal;
		 
		 //cout << "Passei no teste, vou para a cidade " << aux[i].id << endl;
		 
		 /**Cidade escolhida, atualiza tempo*/
		 tempoAcum += tempoAtualI;
		 
		 /**Existe viabilidade de ir para aquela cidade. Faz a viagem, e pega itens.**/
		 
		 pegaItensRandomized(rcl[lim].second.id, pesoAcum, tempoAcum, valorAcum, alfaItens);
		 pontosEscolhidos->push_back(rcl[lim].second.id);
		 pontoAtual = rcl[lim].second.id;
		 aux.erase(aux.begin()+rcl[lim].first);
		 rcl.clear();
	}
	
	//cout << " ----------- SOLUCAO CONSTRUIDA ------------------- " << endl;
	sort(itensEscolhidos->begin(), itensEscolhidos->end());

	mergeData();
	
}


void Solucao::pegaItens(int nPt, int & pesoAcum, double & tempoAcum, int & valorAcum){
	double timeLimit = instance->getMaxTime();
	double v = instance->getVConst();
	double maxSpeed = instance->getMaxSpeed();
	double ratioBag = 0;
	int capacidade = instance->getCapacidade();
	if(pesoAcum != 0){
		ratioBag = (valorAcum / pesoAcum) * 100;
	}
	double tempoNess;
	//cout << "Final é " << instance->getDim() << endl;
	int dAtual = instance->operator[](nPt)[instance->getDim()];
	//cout << "Dist da cidade " << nPt << " para final " << dAtual << endl;
	vector<Item> itensAux(instance->getItensPonto(nPt));
	sort(itensAux.begin(), itensAux.end());
	for(int i = 0; i < itensAux.size(); i++){
		Item at(itensAux[i]);
		if(at.ratio < ratioBag * ACCPT_FACTOR){//Esse item possui ratio menor que factor do ratio atual da mochila?
			break;
		}
		
		tempoNess = dAtual/(maxSpeed - v * (pesoAcum + at.peso));
		
		if(tempoAcum + tempoNess < timeLimit && pesoAcum + at.peso <= capacidade){//É possível pegar o item e ir para o final?
			//cout << "Peguei item " << at.id << endl;
			itensEscolhidos->push_back(at.id);
			pesoAcum += at.peso;
			valorAcum += at.valor;
			ratioBag = (valorAcum / pesoAcum) * 100;
		}
	}
	
}

void Solucao::pegaItensRandomized(int nPt, int & pesoAcum, double & tempoAcum, int & valorAcum, double & alfaItens){
	double timeLimit = instance->getMaxTime();
	double v = instance->getVConst();
	double maxSpeed = instance->getMaxSpeed();
	double ratioBag = 0;
	int capacidade = instance->getCapacidade();
	if(pesoAcum != 0){
		ratioBag = (valorAcum / pesoAcum) * 100;
	}
	double tempoNess;
	//cout << "Final é " << instance->getDim() << endl;
	int dAtual = instance->operator[](nPt)[instance->getDim()];
	//cout << "Dist da cidade " << nPt << " para final " << dAtual << endl;
	vector<Item> itensAux(instance->getItensPonto(nPt));
	vector<pair <int, Item> > rcl;
	sort(itensAux.begin(), itensAux.end());
	bool parada = false;
	while (!parada) {
		for(int i = 0; i < itensAux.size() && rcl.size() <= ((int) (alfaItens*itensAux.size())); i++){
			Item at(itensAux[i]);
			if(at.ratio < ratioBag * ACCPT_FACTOR){//Esse item possui ratio menor que factor do ratio atual da mochila?
				break;
			}
			
			tempoNess = dAtual/(maxSpeed - v * (pesoAcum + at.peso));
			
			if(tempoAcum + tempoNess < timeLimit && pesoAcum + at.peso <= capacidade){//É possível pegar o item e ir para o final?
				//cout << "Peguei item " << at.id << endl;
				rcl.push_back(make_pair(i,itensAux[i])); // poe item na lista de candidatos
			}
		}
		if(rcl.size() == 0) {
			parada = true;
			break;
		}
		int lim = rand()%rcl.size();
		Item at(itensAux[rcl[lim].first]);

		itensEscolhidos->push_back(rcl[lim].second.id);
		pesoAcum += at.peso;
		valorAcum += at.valor;
		ratioBag = (valorAcum / pesoAcum) * 100;
		itensAux.erase(itensAux.begin()+rcl[lim].first);
		rcl.clear();
	}
}

void Solucao::addItem(int nItem){
	itensEscolhidos->push_back(nItem);
}

void Solucao::addPonto(int nPonto){
	pontosEscolhidos->push_back(nPonto);
}

bool Solucao::validSolution(){
		/**
	 * Código 0: Solução Válida
	 * Código 1: Solucão Inválida Capacidade
	 * Código 2: Solução Inválida Tempo
	 * Código 3: Solução Inválida Item Repetido
	 * Código 4: Solução Inválida Item Fora Rota
	 * Código 5: Solução Não Processada
	 **/
	 
	 switch(state){
		 case 0: 
			cout << "Solução Válida" << endl;
			break;
		case 1: 
			cout << "Solucão Inválida Capacidade" << endl;
			break;
		case 2: 
			cout << "Solucão Inválida Tempo" << endl;
			break;
		case 3: 
			cout << "Solucão Inválida Item Repetido" << endl;
			break;
		case 4: 
			cout << "Solucão Inválida Item Fora Rota" << endl;
			break;
		case 5:
			cout << "Solução não processada" << endl;
			break;
	 }
	 
	 return (state == 0);
}

bool Solucao::checkSolution(int &value, double &tempoAcum){
	if(state != 0 and state != 5){
		return false;
	}
	
	double v = instance->getVConst();
	double vMax = instance->getMaxSpeed();
	double pesoAcum = 0;
	double distancia;
	value = 0;
	tempoAcum = 0;
	
	int previous = 1, atual;
	
	vector<int> * ptsAtual;
	
	for(int i = 0; i < solution.size(); i++){
		atual = solution[i].first;
		ptsAtual = &(solution[i].second);
		
		distancia = instance->operator [](previous)[atual];
		
		tempoAcum += (distancia) / (vMax - v * pesoAcum);
		
		for(int j = 0; j < ptsAtual->size(); j++){
			pesoAcum += instance->getPesoItem(ptsAtual->operator[](j));
			value += instance->getValorItem(ptsAtual->operator[](j));
		}
		previous = atual;

	}
	
	if(pesoAcum > instance->getCapacidade()){
		state = 1;
	} else if (tempoAcum > instance->getMaxTime()){
		state = 2;
	} else {
		state = 0;
	}
	
	return state == 0;
}

Solucao * Solucao::localSearch(){
	Solucao * melhor = this;
	Solucao * vizinho;
	double tempoMelhor, tempoAtual;
	int valorAtual, valorMelhor;
	checkSolution(valorMelhor, tempoMelhor);

	//melhor->mergeData();

	while(true){
		vizinho = melhorVizinho(melhor, valorAtual, tempoAtual, instance->getDim());
		if(!vizinho->checkSolution(valorAtual, tempoAtual)){
			break;
		}

		if(valorAtual > valorMelhor || (valorAtual == valorMelhor && tempoAtual < tempoMelhor)){
			valorMelhor = valorAtual;
			tempoMelhor = tempoAtual;
			if(melhor != this){
				delete melhor;
			}
			melhor = vizinho;
		} else {
			if(vizinho != melhor)
				delete vizinho;
			break;
		}
	}
	return melhor;
}

Solucao * Solucao::melhorIncluiCidade(Solucao * base, vector<int> possiveis, int vBase, double tBase, int pBase){
	Solucao * atual, * melhor;
	melhor = base;
	int vAtual, vMelhor = 0, pAtual, pMelhor = (1 << 25);
	double tAtual, tMelhor = (1 << 25);

	for(int i = 0; i < possiveis.size(); i++){
		atual = new Solucao(*base);
		atual->incluiCidade(possiveis[i], vBase, tBase, pBase);

		if(!atual->checkSolution(vAtual, tAtual)){
			delete atual;
			continue;
		}

		if(vAtual > vMelhor || (vAtual == vMelhor && tAtual < tMelhor)){
			if(melhor != base){
				delete melhor;
			}
			vMelhor = vAtual;
			tMelhor = tAtual;
			melhor = atual;
		} else {
			delete atual;
		}
	}

	return melhor;
}

Solucao * Solucao::melhorTrocaCidade(Solucao * base, vector<int> possiveis, int vBase, double tBase, int pBase){
	Solucao * atual, * melhor;
	melhor = base;
	int vAtual, vMelhor = 0, pAtual, pMelhor = (1 << 25);
	double tAtual, tMelhor = (1 << 25);

	for(int i = 0; i < base->solution.size() - 1; i++){
		for(int j = 0; j < possiveis.size(); j++){
			atual = new Solucao(*base);
			atual->removeCidade(i);
			if(!atual->checkWithWeight(vAtual, tAtual, pAtual)){
				delete atual;
				continue;
			}

			atual->incluiCidade(possiveis[j], vAtual, tAtual, pAtual);

			if(!atual->checkSolution(vAtual, tAtual)){
				delete atual;
				continue;
			}
	
			if(vAtual > vMelhor || (vAtual == vMelhor && tAtual < tMelhor)){
				if(melhor != base){
					delete melhor;
				}
				vMelhor = vAtual;
				tMelhor = tAtual;
				melhor = atual;
			} else {
				delete atual;
			}
		}
	}

	return melhor;
}

Solucao * Solucao::melhorTrocaItem(Solucao * base, vector<int> possiveis, int vBase, double tBase, int pBase){
	Solucao * atual, * melhor;
	melhor = base;
	int vAtual, vMelhor = 0, pAtual, pMelhor = (1 << 25);
	double tAtual, tMelhor = (1 << 25);
	

	for(int i = 0; i < base->solution.size() - 1; i++){
		atual = new Solucao(*melhor);
		atual->trocaItens(i);
		if(!atual->checkSolution(vAtual, tAtual)){
			delete atual;
			continue;
		}

		if(vAtual > vMelhor || (vAtual == vMelhor && tAtual < tMelhor)){
			if(melhor != base){
				delete melhor;
			}
			vMelhor = vAtual;
			tMelhor = tAtual;
			melhor = atual;
		} else {
			delete atual;
		}
	}

	return melhor;
}

Solucao * Solucao::melhorTrocaOrdem(Solucao * base, vector<int> possiveis, int vBase, double tBase, int pBase){
	Solucao * atual, * melhor;
	melhor = base;
	int vAtual, vMelhor = 0, pAtual, pMelhor = (1 << 25);
	double tAtual, tMelhor = (1 << 25);

	for(int i = 0; i < base->solution.size() - 1; i++){
		for(int j = i + 1; j < base->solution.size() - 1; j++){
			atual = new Solucao(*base);
			atual->trocaPontos(i, j);
			if(!atual->checkSolution(vAtual, tAtual)){
				delete atual;
				continue;
			}

			if(tAtual < tMelhor){
				if(melhor != base){
					delete melhor;
				}
				tMelhor = tAtual;
				melhor = atual;
			} else {
				delete atual;
			}
		}
	}
	return melhor;
}

vector<int> Solucao::calcPossiveis(int d){
	vector<int> possiveis;

	for(int i = 1; i < d; i++){
		bool dentro = false;
		for(int j = 0; j < solution.size(); j++){
			if(i == solution[j].first){
				dentro = true;
				break;
			}
		}

		if(dentro){
			continue;
		}

		possiveis.push_back(i);//Cidade i não está na solucao atualmente
	}

	return possiveis;

}

Solucao * Solucao::melhorVizinho(Solucao *base, int &valor, double &tempo, int d){
	double tBase;
	int vBase, pBase;
	base->checkWithWeight(vBase, tBase, pBase);

	bool melhora = false;

	vector<int> possiveis = base->calcPossiveis(d);

	Solucao * sol[4];

	sol[0] = melhorIncluiCidade(base, possiveis, vBase, tBase, pBase);
	sol[1] = melhorTrocaCidade(base, possiveis, vBase, tBase, pBase);
	sol[2] = melhorTrocaItem(base, possiveis, vBase, tBase, pBase);
	sol[3] = melhorTrocaOrdem(base, possiveis, vBase, tBase, pBase);
/* 	base->print();
	for(int i = 0; i < 4; i++){
		sol[i]->print();
	}

	int s;
	std::cin >> s; */

	Solucao * melhor = NULL;

	int vAtual;
	double tAtual;
	int index = -1;

	valor = 0;
	tempo = (1 << 25);

	for(int i = 0; i < 4; i++){
		sol[i]->checkSolution(vAtual, tAtual);
		if(sol[i] == base){
			continue;
		}
		if(vAtual > valor || (vAtual == valor && tAtual < tempo)){
			melhor = sol[i];
			index = i;
			valor = vAtual;
			tempo = tAtual;
		}
	}

	for(int i = 0; i < 4; i++){
		if(i != index && sol[i] != base){
			delete sol[i];
		}
	}

	return melhor;

}

void Solucao::trocaPontos(int i, int j){//Troca as cidades i e j
	swap(solution[i], solution[j]);
}

void Solucao::incluiCidade(int cidade, int & valorAcum, double & tempoAcum, int & pesoAcum){
	solution[solution.size() - 1] = make_pair(cidade, vector<int>());
	solution.push_back(make_pair(instance->getDim(), vector<int>()));

	double timeLimit = instance->getMaxTime();
	double v = instance->getVConst();
	double maxSpeed = instance->getMaxSpeed();
	double ratioBag = 0;
	int capacidade = instance->getCapacidade();
	if(pesoAcum != 0){
		ratioBag = (valorAcum / pesoAcum) * 100;
	}
	double tempoNess;
	//cout << "Final é " << instance->getDim() << endl;
	int dAtual = instance->operator[](cidade)[instance->getDim()];
	//cout << "Dist da cidade " << nPt << " para final " << dAtual << endl;
	vector<Item> itensAux(instance->getItensPonto(cidade));
	sort(itensAux.begin(), itensAux.end());
	for(int i = 0; i < itensAux.size(); i++){
		Item at(itensAux[i]);
		tempoNess = dAtual/(maxSpeed - v * (pesoAcum + at.peso));
		
		if(tempoAcum + tempoNess < timeLimit && pesoAcum + at.peso <= capacidade){//É possível pegar o item e ir para o final?
			//cout << "Peguei item " << at.id << endl;
			solution[solution.size() - 2].second.push_back(at.id);
			pesoAcum += at.peso;
			valorAcum += at.valor;
			ratioBag = (valorAcum / pesoAcum) * 100;
		}
	}
}

bool Solucao::checkWithWeight(int &value, double &tempoAcum, int &pesoAcum){
	
	if(state != 0 and state != 5){
		return false;
	}
	
	double v = instance->getVConst();
	double vMax = instance->getMaxSpeed();
	pesoAcum = 0;
	double distancia;
	value = 0;
	tempoAcum = 0;
	
	int previous = 1, atual;
	
	vector<int> * ptsAtual;
	
	for(int i = 0; i < solution.size(); i++){
		atual = solution[i].first;
		ptsAtual = &(solution[i].second);
		
		distancia = instance->operator [](previous)[atual];
		
		tempoAcum += (distancia) / (vMax - v * pesoAcum);
		
		for(int j = 0; j < ptsAtual->size(); j++){
			pesoAcum += instance->getPesoItem(ptsAtual->operator[](j));
			value += instance->getValorItem(ptsAtual->operator[](j));
		}
		previous = atual;
	}
	
	if(pesoAcum > instance->getCapacidade()){
		state = 1;
	} else if (tempoAcum > instance->getMaxTime()){
		state = 2;
	} else {
		state = 0;
	}
	
	return state == 0;
}

void Solucao::removeCidade(int cidade){
	solution.erase(solution.begin() + cidade);
}

void Solucao::trocaItens(int cidade){
	int id = solution[cidade].first;
	vector<Item> aux = instance->getItensPonto(id);
	int somaAtual = 0;
	for(int i = 0; i < solution[cidade].second.size(); i++){
		somaAtual += instance->getItem(solution[cidade].second[i]).peso;
	}

	int somaNova = 0;
	int lim = aux.size();
	int index;

	solution[cidade].second.clear();

	while(true){
		if(lim == 0){
			break;
		}
		index = rand() % lim;
		somaNova += aux[index].peso;
		if(somaNova >= somaAtual){
			break;
		}
		solution[cidade].second.push_back(aux[index].id);
		lim--;
		aux.erase(aux.begin() + index);
	}
}

Solucao * Solucao::simulatedAnnealing(int iterations, int perturb, double factor, int sucessLim, double temperature){
	Solucao * atual = this, * melhor = this;
	int i = 0, j = 0, nSucess = 0;
	int melhorValor, atualValor, atualPeso, melhorPeso;
	double melhorTempo, atualTempo;
	int delta;
	double rnd, ex;
	int stop;
	int r;
	melhor->checkWithWeight(melhorValor, melhorTempo, melhorPeso);

	while(i < iterations){
		j = 0;
		nSucess = 0;

		while(j < perturb && nSucess < sucessLim){
			atual = melhor->perturbar();
			atual->checkSolution(atualValor, atualTempo);

			delta = melhorValor - atualValor;
			r = rand();
			rnd = (double)r / RAND_MAX;
			ex = exp(-delta/(double)temperature);
/* 			if(delta <= 0){
				cout << "Accp improve " << atualValor << endl;
			} else if (ex > rnd){
				cout << "Accp worst " << atualValor << endl;
			} */
			if(delta <= 0 || ex > rnd){
				if(melhor != this){
					delete melhor;
				}
				melhor = atual;
				melhorValor = atualValor;
				melhorTempo = atualTempo;
				melhorPeso = atualPeso;
				nSucess++;
			} else {
				delete atual;
			}
			j++;
		}

		temperature *= factor;
		i++;
	}

	melhor = melhor->localSearch();

	return melhor;

}

Solucao * Solucao::perturbar(){
	vector<int> possiveis = calcPossiveis(instance->getDim());
	
	int qtdPerturb = rand() % solution.size();
	qtdPerturb /= 2;

	if(qtdPerturb == 0){
		qtdPerturb = 1;
	}

	Solucao * perturbada = new Solucao(*this);
	Solucao *anterior = new Solucao(*perturbada);

	for(int i = 0; i < qtdPerturb; i++){
		if(solution.size() - 1 <= 0){
			break;
		}
		int atual = rand() % (solution.size() - 1);
		perturbada->removeCidade(atual);
	}

	int vAtual, pAtual;
	double tAtual;

	while(perturbada->checkWithWeight(vAtual, tAtual, pAtual)){
		if(possiveis.size() == 0){
			break;
		}
		
		delete anterior;

		anterior = new Solucao(*perturbada);

		int inserida = rand() % (possiveis.size());
		
		int cidadeNova = possiveis[inserida];
		perturbada->incluiCidade(cidadeNova, vAtual, tAtual, pAtual);

		possiveis.erase(possiveis.begin() + inserida);
	}

	int tam = anterior->solution.size() - 1;

	for(int i = 0; i < qtdPerturb; i++){
		if(tam <= 0){
			break;
		}
		int cidadeTroca = rand() % tam;
		anterior->trocaItens(cidadeTroca);
	}

	delete perturbada;

	return anterior;
}

void Solucao::print(){
	for(int i = 0; i < solution.size(); i++){
		cout << solution[i].first << "[ ";
		for(int j = 0; j < solution[i].second.size(); j++){
			cout << solution[i].second[j] << ", ";
		}
		cout << "]" << endl << endl;
	}
	cout << "-----------------------END------------------------" << endl;
}


