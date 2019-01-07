#ifndef _INCLUDE_QUEUE_PRIOR_
#define _INCLUDE_QUEUE_PRIOR_


typedef struct
{
	int nKey;
	double nPrior;
} PQItem;

typedef struct
{
	PQItem* PQueue;		// kolejka realizowana dynamicznie w postaci stogu //PQueue jest tablic¹ elementów struktur PQItem
	int PQSize;			// rozmiar kolejki priorytetowej
	int PQCurrSize;		// aktualna iloœæ elementów w kolejce, indeks do elementu tablicy, gdzie nale¿y wsyawiæ element
} PQueue;


PQueue* PQInit( int nSize );	//inicjuje kolejkê o rozmiarze przekazanym w parametrze
int PQisEmpty( PQueue* );	//sprawdzenie, czy kolejka priorytetowa jest pusta (zwraca 1 albo 0)
void PQEnQueue( PQueue*, int nKey, double nPrior );	// funkcja wk³adaj¹ca do kolejki
int  PQDeQueue( PQueue* );	//zwracany jest element o najwy¿szym priorytecie
void pQClearQueue ( PQueue* ); // czyœci elementy kolejki. Kolejka zostaje
void PQRelease( PQueue** );	//Usuwa ca³kowicie kolejkê, zwalnia pamiêæ, nie zostawia po niej œladu
void PQPrint( PQueue* );	//Drukuje w inorder01, traktujemy jak drzewo binarne


void DecreaseKey( PQueue*, int nKey, int nowyPrior ); //(nPrior < Item.nPrior)	//dla pewnego elementu maj¹cy klucz key, który w tej kolejce jest, ustawiam priorytet
void IncreaseKey( PQueue*, int nKey, int nowyPrior ); // (nPrior > Item.nPrior)	//decrease zmniejszenie, increase zwiêkszenie priorytetu // w skrócie zmiana priorytetu.

#endif