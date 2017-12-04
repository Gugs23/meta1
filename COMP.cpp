#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

int main(int argc, char * argv[]){
	if(argc != 2){
		cout << "Use ./THOPFILE <Arquivo Lista Execs>" << endl;
		return 1;
	}
	
	fstream fname(argv[1]);
	
	if(fname.fail()){
		cout << "Impossível abrir arquivo de entrada" << endl;
	}
	
	int tipo;
	int count = 0;
	string file1, com;
	while(fname >> file1){
		//cout << "Exec " << count++ << endl;
		com = "Class/Greedy \"Files/instances/" + file1 + "\"";
		//cout << "    " << file1;
		system(com.c_str());
		//cout << "-------------------------" << endl;
        com = "Class/SimAnn \"Files/instances/" + file1 + "\"";
		//cout << "    " << file1;
		system(com.c_str());
		//cout << "-------------------------" << endl;
	}

	return 0;
}
