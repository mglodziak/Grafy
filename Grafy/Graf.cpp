#include "stdafx.h"
#include "Prior.h"
#include "Graf.h"
#include <stdlib.h>

double Dijkstra( Vertex* City, int nSize, int nFirst )
{
	PQueue* pq = PQInit( nSize ); //inicjujê kolejkê priorytetow¹
	double* Distance = ( double* )calloc( nSize, sizeof( double ) );       //tablica d³ugoœci dróg 
	int* Path = ( int* )calloc( nSize, sizeof( int ) );
	if ( !Distance || !Path )
	{
		perror( "Create error!" );
		return 1;
	}
	City[nFirst].NoNodToNearestShop = Path;

	for ( int i = 0; i < nSize; i++ )
	{
		Distance[i] = INT_MAX;
		Path[i] = -1;
	}

	//------//
	PQEnQueue( pq, nFirst, 0 );
	Distance[nFirst] = 0;												//Odleg³oœæ do siebie

	double dist = 0;

	while ( !( PQisEmpty( pq ) ) )
	{
		int k = PQDeQueue( pq );
		if ( City[k].ShopOrNot )					// jesli sklep 
		{
			City[nFirst].NearestShop = k;			// zapamietuje indeks do najblizszego sklepu
			dist = Distance[k];
			PQRelease( &pq );
			break;
		}

		else										 //kolejny obieg
		{
			NItem* j = City[k].nList;
			while ( j )
			{
				int Node = j->nKey;
				if ( Distance[k] + j->length < Distance[Node] )
				{
					City[nFirst].NoNodToNearestShop[Node] = k;
					Distance[Node] = Distance[k] + j->length;
					PQEnQueue( pq, Node, Distance[Node] );
				}
				j = j->pNext;
			}
		}
	}
	free( Distance );
	return dist;



}



void DFS( Vertex* City, int p, int* TabVisited ) //p - wierzcholek o jakims numerze
{
	TabVisited[p] = 1; //1 - odwiedzony
	NItem* v = City[p].nList;
	while ( v )
	{
		v->time = v->length / SPEED;

		if ( !TabVisited[v->nKey] )
			DFS( City, v->nKey, TabVisited );

		v = v->pNext;
	}
}