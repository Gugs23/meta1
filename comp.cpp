#include <iostream>
#include <fstream>
using namespace std;

int main(){
	fstream a("GreedyCorre.txt");
	fstream b("GreedyTeste.txt");

	int velho, novo;

	while(a >> velho && b >> novo){
		cout << novo - velho << endl;
	}

	return 0;
}
