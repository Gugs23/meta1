#include "Item.hpp"

int Item::count = 1;

Item::Item(int cvalor, int cpeso, int cponto, int cid) : valor(cvalor), peso(cpeso), ponto(cponto){
	if(cid == -1){
		cid = count++;
	}
	id = cid;
	ratio = (cvalor / cpeso) * 100;
	rank = 0;
}

bool Item::operator < (const Item &outro) const{
	return ratio > outro.ratio;
}
