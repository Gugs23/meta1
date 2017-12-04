#ifndef __ITEM_H
#define __ITEM_H

class Item{
	public:
		static int count;
		int id, valor, peso, ponto;
		double rank, ratio;
		Item(int, int, int, int = -1);
		Item() { };
		
		bool operator < (const Item &) const;
};


#endif
