#pragma once

#define SPEED 5

typedef struct NItem
{
	int nKey;		//nr wierzcho�ka s�siada
	double length;	//d�ugo��
	double time;	//czas
	NItem* pNext;	//na kolejny element w liscie sasiedzsta
}List;

typedef struct
{
	List* nList;		//Lista s�siedztw
	int ShopOrNot;			//1 - monopolowy, 0 - dom
	int NearestShop;	//indeks najblizszego monopolowego
	double SumDistance;	//suma dlugosci 
	int* NoNodToNearestShop;		//nr w�z�a prowadz�cy do najbli�szego monopolowego
	double SumTime;		//czas przej�cia ca�o�ci
}Vertex;

double Dijkstra( Vertex*, int, int ); // tu u�ywamy kolejki prior
void DFS( Vertex* City, int p, int* TabVisited );
