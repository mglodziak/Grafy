#ifndef _INCLUDE_QUEUE_PRIOR_
#define _INCLUDE_QUEUE_PRIOR_


typedef struct
{
	int nKey;
	double nPrior;
} PQItem;

typedef struct
{
	PQItem* PQueue;		// kolejka realizowana dynamicznie w postaci stogu //PQueue jest tablic� element�w struktur PQItem
	int PQSize;			// rozmiar kolejki priorytetowej
	int PQCurrSize;		// aktualna ilo�� element�w w kolejce, indeks do elementu tablicy, gdzie nale�y wsyawi� element
} PQueue;


PQueue* PQInit( int nSize );	//inicjuje kolejk� o rozmiarze przekazanym w parametrze
int PQisEmpty( PQueue* );	//sprawdzenie, czy kolejka priorytetowa jest pusta (zwraca 1 albo 0)
void PQEnQueue( PQueue*, int nKey, double nPrior );	// funkcja wk�adaj�ca do kolejki
int  PQDeQueue( PQueue* );	//zwracany jest element o najwy�szym priorytecie
void pQClearQueue ( PQueue* ); // czy�ci elementy kolejki. Kolejka zostaje
void PQRelease( PQueue** );	//Usuwa ca�kowicie kolejk�, zwalnia pami��, nie zostawia po niej �ladu
void PQPrint( PQueue* );	//Drukuje w inorder01, traktujemy jak drzewo binarne


void DecreaseKey( PQueue*, int nKey, int nowyPrior ); //(nPrior < Item.nPrior)	//dla pewnego elementu maj�cy klucz key, kt�ry w tej kolejce jest, ustawiam priorytet
void IncreaseKey( PQueue*, int nKey, int nowyPrior ); // (nPrior > Item.nPrior)	//decrease zmniejszenie, increase zwi�kszenie priorytetu // w skr�cie zmiana priorytetu.

#endif