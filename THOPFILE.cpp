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
	string file1, file2, com;
	
	while(fname >> tipo){
		cout << "Exec " << count++ << endl;
		switch(tipo){
			case 2:
				fname >> file1;
				break;
			case 1:
				fname >> file1 >> file2;
				com = "Class/ExecInstance " + file1 + " " + file2;
				cout << "    " << file1 << " " << file2 << endl;
				system(com.c_str());
				break;
			default:
				getline(fname, file1);
				break;
		}
		cout << "-------------------------" << endl;
	}

	return 0;
}
