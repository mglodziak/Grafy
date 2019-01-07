#include "Prior.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


void UpdateDown( PQueue*, int l, int p );	//to mamy z sorta
void UpdateUp( PQueue*, int l, int p );


PQueue* PQInit( int nSize ) // na podstawie kolejki tablicowej 
{
	PQueue* q = ( PQueue* )calloc( 1, sizeof( PQueue ) ); // mamy strukturê, dlatego wiêcej kodu, czy to potrzebne??
	if ( !q )
	{
		printf( "Error: brak pamieci\n" );
		return NULL;
	}

	q->PQueue = ( PQItem* )calloc( nSize, sizeof( PQItem ) );
	if ( !q->PQueue )
	{
		printf( "Error: brak pamieci\n" );
		return NULL;
	}

	q->PQSize = nSize;
	return q;
}


//----------
int PQisEmpty( PQueue* q )
{
	return ( !q->PQCurrSize ); // podobnie jak w kolejce tablicowej
}

//----------
void PQEnQueue( PQueue* q, int nKey, double nPrior )
{

	if ( q->PQCurrSize == q->PQSize )
	{
		printf( "Kolejka jest pelna\n" );
		return;
	}
	q->PQueue[q->PQCurrSize].nKey = nKey; // do kolejki PQueue o indeksie CurrSize (czyli ostatnim) do pola piêtro ni¿ej wpisujê odpowiedni¹ wartoœæ 
	q->PQueue[q->PQCurrSize].nPrior = nPrior;

	UpdateUp( q, 0, q->PQCurrSize );
	q->PQCurrSize++;

}

//----------
int  PQDeQueue( PQueue* q )
{
	if ( PQisEmpty ( q ) )
	{
		printf ( "Kolejka jest pusta!!\n" );
		return -1; //-1 kod b³êdu
	}
	int zdjety_element = q->PQueue[0].nKey;
	q->PQCurrSize--;

	q->PQueue[0] = q->PQueue[q->PQCurrSize]; // do zdjetego elementu wstaw ostatni

	UpdateDown ( q, 0, q->PQCurrSize );
	return zdjety_element;
}

//----------
void pQClearQueue ( PQueue* q )
{
	q->PQCurrSize = 0;
}

//----------
void PQRelease( PQueue** q ) // wziête z kolejki tablicowej
{
	free( ( *q )->PQueue );
	free( *q );
	*q = NULL;

}

//----------
void PQPrint( PQueue* q )
{
	if ( PQisEmpty ( q ) )
	{
		printf ( "Error: Kolejka jest pusta!!\n" );
		return;
	}

	for ( int i = 0; i < q->PQCurrSize; i++ )
		printf( "Wartosc: %d -> Priorytet: %d\n", q->PQueue[i].nKey, q->PQueue[i].nPrior );

	printf ( "\n" );
}

//----------
void DecreaseKey( PQueue* q, int nKey, int nowyPrior )
{
	if ( ( nowyPrior > q->PQueue[nKey].nPrior ) )
	{
		printf ( "Priorytet jest ju¿ mniejszy!!\n" );
		return;
	}
	q->PQueue[nKey].nPrior = nowyPrior;
	UpdateDown( q, nKey, q->PQCurrSize );
}


void IncreaseKey( PQueue* q, int nKey, int nowyPrior )
{
	if ( ( nowyPrior < q->PQueue[nKey].nPrior ) )
	{
		printf ( "Priorytet jest ju¿ wiekszy!!\n" );
		return;
	}
	q->PQueue[nKey].nPrior = nowyPrior;
	UpdateUp( q, nKey, q->PQCurrSize - 1 );
}

void UpdateDown( PQueue* q, int l, int p ) //wziête z update, z sorta
{
	if ( l == p ) return; // nic nie trzeba zmieniaæ
	int i = l;
	int j = 2 * i + 1; // zamiast ( i + 1 ) * 2 - 1, to jest to samo
	PQItem tmp = q->PQueue[i];

	while ( j <= p )
	{
		if ( j < p )
			if ( q->PQueue[j].nPrior > q->PQueue[j + 1].nPrior )
				j++;

		if ( tmp.nPrior < q->PQueue[j].nPrior ) break;	//jeœli true, jest na swoim miejscu

		q->PQueue[i] = q->PQueue[j];
		i = j;
		j = 2 * i + 1;
	}
	q->PQueue[i] = tmp; //warunek kopca zachowany
}


void UpdateUp( PQueue* q, int l, int p )
{

	if ( l == p ) return; // jeœli nic nie trzeba zmieniaæ
	int i = p; //tym razem zaczynamy skrajnie z prawej
	int j = ( i - 1 ) / 2; //indeks ojca
	PQItem tmp = q->PQueue[i];

	//dopoki nie przekroczymy l, oraz sprawdzamy priorytety
	while ( i > l && q->PQueue[j].nPrior > tmp.nPrior )		//jeœli prior rodzica < prior ost elem - przesuñ z j do i (w dó³)
	{
		q->PQueue[i] = q->PQueue[j];
		i = j;
		j = ( i - 1 ) / 2; //ojciec j-tego
	}

	// no tak, na koniec wstawiæ zapamiêtany pod j-t¹ pozycjê   tmp!!	
	q->PQueue[i] = tmp;


}