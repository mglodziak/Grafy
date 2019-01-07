#pragma once

#define SPEED 5

typedef struct NItem
{
	int nKey;		//nr wierzcho³ka s¹siada
	double length;	//d³ugoœæ
	double time;	//czas
	NItem* pNext;	//na kolejny element w liscie sasiedzsta
}List;

typedef struct
{
	List* nList;		//Lista s¹siedztw
	int ShopOrNot;			//1 - monopolowy, 0 - dom
	int NearestShop;	//indeks najblizszego monopolowego
	double SumDistance;	//suma dlugosci 
	int* NoNodToNearestShop;		//nr wêz³a prowadz¹cy do najbli¿szego monopolowego
	double SumTime;		//czas przejœcia ca³oœci
}Vertex;

double Dijkstra( Vertex*, int, int ); // tu u¿ywamy kolejki prior
void DFS( Vertex* City, int p, int* TabVisited );
