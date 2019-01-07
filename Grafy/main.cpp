#define _CRT_SECURE_NO_WARNINGS
#include "Prior.h"
#include "stdafx.h"
#include "Graf.h"
#include <stdlib.h>


void ReadGraph( FILE*, Vertex*, int ); //jedna czy dwie gwiazdki? //jedna
void PrintGraph( FILE*, Vertex*, int );
void RemoveGraph( Vertex*, int );

int main( int argc, char* argv[] )
{
	if ( argc != 3 ) //Gdy nie zgadza siê liczba parametrów
	{
		printf( "Error numbers of arguments!!" );
		return 1;
	}

	FILE* fin = NULL;
	if (! ( fin = ( fopen( argv[1], "r" ) ) ) ) //otwieranie pliku // wykrzyknik
	{
		printf( "Error opening file" );
		return 2;
	}

	int liczba_wierzcholkow;
	fscanf( fin, "%d\n", &liczba_wierzcholkow ); //wczytanie liczby wierzcho³ków
	printf( "Liczba wierzcholkow: %d\n", liczba_wierzcholkow );

	Vertex* City = ( Vertex* )calloc( liczba_wierzcholkow, sizeof( Vertex ) ); // alokujê pamiêæ dla struktury przechowuj¹cej dane grafu
	if ( !City )
	{
		perror( "Error creating City, no enough memory!!" );
		return 3;
	}
	ReadGraph ( fin, City, liczba_wierzcholkow );
	fclose ( fin );

	///-----------DFS-----------
	int* visited = ( int* )calloc( liczba_wierzcholkow, sizeof( int ) );
	if ( !visited )
	{
		perror( "Error creating TabVisited!" );
		return 1;
	}
	for ( int i = 0; i < liczba_wierzcholkow; i++ )
		visited[i] = 0;
	
	DFS( City, 0, visited );
	free( visited );
	///-----------DFS-----------



	for ( int i = 0; i < liczba_wierzcholkow; i++ ) //dijkstra, szukam drogi
	{
		if ( !City[i].ShopOrNot ) //szukam drogi jeœli nie jest sklepem
		{
			City[i].SumDistance = Dijkstra( City, liczba_wierzcholkow, i ); // uzywam dijkstry do znalezienia drogi
			City[i].SumTime = City[i].SumDistance / SPEED; //wyliczam czas dojscia

			int* Path = ( int* )calloc( liczba_wierzcholkow, sizeof( int ) ); // tablica aby zapisac droge do sklepu
			if ( !Path )
			{
				perror( "Error creating, no memory!" );
				return 1;
			}

			int tmp = City[i].NearestShop;
			int p = 0;
			while ( Path[p - 1] != i ) // zapis œcie¿ki do tablicy i jej odwrócenie
			{
				Path[p++] = tmp;
				tmp = City[i].NoNodToNearestShop[tmp];
			}

			for ( int w = 0; w < p / 2; w++ )
			{
				int temp = Path[p - w - 1];
				Path[p - w - 1] = Path[w];
				Path[w] = temp;
			}
			City[i].NoNodToNearestShop = Path;
		}
	}



	FILE* fout = NULL;
	if ( ( fout = ( fopen( argv[2], "w+" ) ) ) == NULL ) //otwieranie pliku
	{
		perror( "* File open error!\n\n" );
		return 0;
	}
	PrintGraph( fout, City, liczba_wierzcholkow ); //zapis danych do pliku
	fclose( fout );
	
	RemoveGraph( City, liczba_wierzcholkow ); //usuwam graf

	return 0;
}




void ReadGraph( FILE* fin, Vertex* City, int nSize)

{
	for ( int licznik = 0; licznik < nSize; licznik++ ) // bêdê g³ówn¹ pêtlê wykonywa³ tyle razy ile jest wierzcho³ków
														// potem druga pêtla która dopisze do listy s¹siaduj¹ce wierzcho³ki
	{
		fgetc ( fin ); // fgetc odczytuje gwiazdkê

		int i = 0; // numer wierzcho³ka
		int is_shop = 0; // tu zapiszê, czy sklep czy nie

		fscanf( fin, "%d %d\n", &i, &is_shop ); //wczytujê tutaj dane z linijek zaczynaj¹cych siê od gwiazdek
		City[i].ShopOrNot = is_shop; // zapisujê do tablicy czy jest sklepem czy nie


//		NItem* pointer = City[i].nList;
		char c;
		while ( ( c = fgetc( fin ) ) != '*' && c != EOF )// teraz wczytujemy dane s¹siaduj¹cych wierzcho³ków
		{
			ungetc( c, fin );
			NItem* NewData = ( NItem* )calloc( 1, sizeof( NItem ) );
			if ( !NewData )
			{
				printf ( "Error NewData: Not enough memory" );
				return;
			}
			if ( !City[i].nList ) //jesli lista jest pusta to niewiele trzeba robic
				City[i].nList = NewData;
			else //jesli juz w niej cos jest
			{
				NItem* tmp = City[i].nList;
				if ( !tmp )
				{
					perror( "Error tmp: Not enough memory" );
					return;
				}

				while ( tmp->pNext )
					tmp = tmp->pNext;

				tmp->pNext = NewData;
			}



			fscanf( fin, "%d %lf\n", &NewData->nKey, &NewData->length ); 	
	//		printf( "%d %lf\n", NewData->nKey, NewData->length );
		}
		ungetc( c, fin );
	}

}

void PrintGraph( FILE* fout, Vertex* City, int nSize) //zapis do pliku
{
	for ( int i = 0; i < nSize; i++ )
	{
		fprintf ( fout, "Nr wierzcholka: %d\n", i );
		if (City[i].ShopOrNot )
			fprintf ( fout, "Sklep monopolowy!\n");
		else
		{
			fprintf( fout, "Dom\n" );
			fprintf( fout, "Indeks najbli¿szego sklepu: %d\n", City[i].NearestShop );
			fprintf( fout, "Odl. do sklepu: %.2lfkm\n", City[i].SumDistance );

			fprintf( fout, "Droga do sklepu: " );
			int k = 0;
			while ( City[i].NoNodToNearestShop[k] != City[i].NearestShop )
				fprintf( fout, "%d ", City[i].NoNodToNearestShop[k++] );
			fprintf( fout, "%d ", City[i].NoNodToNearestShop[k] );


			fprintf( fout, "\nCzas przejscia: %.2lfh = %.2lfmin\n", City[i].SumTime, City[i].SumTime * 60 );

		}
		fprintf( fout, "--------------------------------------------\n" );

	}
}

void RemoveGraph(  Vertex* City, int nSize )
{
	for ( int j = 0; j < nSize; j++ )
	{
		while ( NItem* tmp = City[j].nList )
		{
			City[j].nList = tmp->pNext;
			free( tmp );
		}
		free( City[j].NoNodToNearestShop );
	}
	free( City );
	City = NULL;
}
