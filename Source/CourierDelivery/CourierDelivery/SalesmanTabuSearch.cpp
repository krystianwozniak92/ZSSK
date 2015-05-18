#include "SalesmanTabuSearch.h"


#define TABU_TIME 25
#define CANDIDATES 25
#define PENAL_LONG_TERM 50

// Konstruktor
SalesmanTabuSearch::SalesmanTabuSearch()
{
	this->numberOfIterations = 0;

	this->bestCycleLength = std::numeric_limits<double>::max();

	this->salesman = salesman;

	this->currentCycle = nullptr;
	this->bestCycle = nullptr;

	this->tabuList = nullptr;
	this->tabuListLongTerm = nullptr;
}

// Konstruktor
SalesmanTabuSearch::SalesmanTabuSearch(Salesman* salesman, int numberOfIterations)
{
	this->numberOfIterations = numberOfIterations;

	this->bestCycleLength = std::numeric_limits<double>::max();

	this->salesman = salesman;

	this->currentCycle = nullptr;
	this->bestCycle = nullptr;

	this->tabuList = new std::vector<std::vector<int>>(salesman->getSize(), std::vector<int>(salesman->getSize()));
	this->tabuListLongTerm = new std::vector<std::vector<int>>(salesman->getSize(), std::vector<int>(salesman->getSize()));
}

// Destruktor
SalesmanTabuSearch::~SalesmanTabuSearch()
{
	// Usu� aktualny cykl
	if (this->currentCycle != nullptr)
	{
		delete this->currentCycle;
	}

	// Usu� najlepszy cykl
	if (this->bestCycle != nullptr)
	{
		delete this->bestCycle;
	}

	// Usu� macierz tabu
	if (this->tabuList != nullptr)
	{
		delete this->tabuList;
	}

	// Usu� pierwsz� macierz tabu
	if (this->tabuListLongTerm != nullptr)
	{
		delete this->tabuListLongTerm;
	}
}

// Uruchamia algorytm
void SalesmanTabuSearch::start()
{
	// Wygeneruj losowy cykl i przyjmij go za najlepszy znany do tej pory cykl
	this->bestCycle = this->hamiltonRandomCycle();

	// D�ugo�� aktualnie najlepszego cyklu
	this->bestCycleLength = this->hamiltonCycleLength(this->bestCycle);

	// P�tla losuj�ca kandydat�w
	for (int candidate = 0; candidate < CANDIDATES; ++candidate)
	{
		// Wyzeruj licznik znalezionych nieefektywnych cykli
		int inefficientCycleCounter = 0;

		// Wygeneruj losowy cykl Hamiltona
		this->currentCycle = this->hamiltonRandomCycle();

		// D�ugo�� aktualnego cyklu
		this->currentCycleLength = this->hamiltonCycleLength(this->currentCycle);

		// Zresetuj list� tabu
		this->resetTabuLists();

		// P�tla iteracji algorytmu
		for (int i = 0; i < this->numberOfIterations; i++)
		{
			// Pobierz najlepszy s�siedni cykl w zale�no�ci od iteracji
			std::vector<int>* bestCandidate = this->getBestCandidate(i);

			// D�ugo�� aktualnego cyklu
			double bestCandidateLength = this->hamiltonCycleLength(bestCandidate);

			// Je�li aktualny cykl jest lepszy od najlepszego kadydata
			if (bestCandidateLength < this->currentCycleLength)
			{
				// Wyzeruj licznik znalezionych nieefektywnych cykli
				inefficientCycleCounter = 0;

				// Kopia: Najlepszy kandydant -> Aktualny cykl
				copy(bestCandidate->begin(), bestCandidate->end(), this->currentCycle->begin());

				// Przypisz za d�ugo�� aktulanego cyklu d�ugo�� najlepszego kandydata
				this->currentCycleLength = bestCandidateLength;

				// Je�li aktualny cykl jest lepszy od najlepszego cyklu
				if (this->currentCycleLength < this->bestCycleLength)
				{
					// Kopia: Aktualny cykl -> Najlepszy cykl
					copy(currentCycle->begin(), currentCycle->end(), this->bestCycle->begin());

					// Przypisz za d�ugo�� najlepszego cyklu d�ugo�� aktualnego cyklu
					this->bestCycleLength = this->currentCycleLength;
				}
			}
			else
			{
				// Zwi�ksz licznik znalezionych nieefektywnych cykli
				inefficientCycleCounter++;

				// Sprawd� licznik znalezionych nieefektywnych cykli
				if (inefficientCycleCounter > numberOfIterations / 4)
				{
					break;
				}
			}
		}
	}
}

// Zwraca d�ugo�� najlepszego cyklu
double SalesmanTabuSearch::getBestCycleLength()
{
	// Je�li cykl nie jest pusty
	if (this->bestCycle != nullptr)
	{
		if (this->bestCycle->size() > 0)
		{
			return this->hamiltonCycleLength(this->bestCycle);
		}
	}

	return 0;
}



// Losuje cykl Hamiltona
std::vector<int>* SalesmanTabuSearch::hamiltonRandomCycle()
{
	// Je�li macierz s�siedztwa nie jest pusta
	if (this->salesman->getSize() > 0)
	{
		// Losowy cykl Hamiltona
		std::vector<int>* randomCycle = new std::vector<int>();

		// Wpisz wszystkie wierzcho�ki
		for (int i = 0; i < this->salesman->getSize(); ++i)
		{
			randomCycle->push_back(i);
		}

		// Wymieszaj
		random_shuffle(randomCycle->begin(), randomCycle->end());

		// Zwr�� cykl
		return randomCycle;
	}

	// Zwr�c pusty cykl
	return nullptr;
}

// Zwraca d�ugo�� cyklu Hamiltona
double SalesmanTabuSearch::hamiltonCycleLength(std::vector<int>* hamiltonCycle)
{
	// D�ugo�� cyklu Hamiltona
	double length = 0.0f;

	// Zmienne pomocnicze
	int v1 = 0;
	int v2 = 0;

	// Je�li cykl nie jest pusty
	if (hamiltonCycle != nullptr)
	{
		if (hamiltonCycle->size() > 0)
		{
			// Numer pierwszego wierzcho�ka
			v1 = *(hamiltonCycle->begin());

			// Dodaj wagi wszystkich kraw�dzi
			for (std::vector<int>::iterator it = hamiltonCycle->begin() + 1; it < hamiltonCycle->end(); ++it)
			{
				// Numer kolejnego wierzcho�ka
				v2 = *it;

				// Dodaj wag� kraw�dzi do d�ugo�ci
				length += salesman->getDistance(v1, v2);

				// Przepisz numer dalej
				v1 = v2;
			}

			// Dodaj wag� kraw�dzi ��cz�cej pierwszy i ostatni wierzcho�ek
			v1 = *(hamiltonCycle->begin());
			length += salesman->getDistance(v1, v2);

			// Zwr�c d�ugo��
			return length;
		}
	}

	// Zwr�� zero
	return 0.0f;
}

// Resetuje macierze tabu
void SalesmanTabuSearch::resetTabuLists()
{
	for (int i = 0; i < this->salesman->getSize(); ++i)
	{
		for (int j = 0; j < this->salesman->getSize(); ++j)
		{
			(*this->tabuList)[i][j] = 0;
			(*this->tabuListLongTerm)[i][j] = 0;
		}
	}
}

// Znajduje najlepszego kandydata
std::vector<int>* SalesmanTabuSearch::getBestCandidate(int iteration)
{
	// D�ugo�� cyklu najlepszego kandydata przyjmuj�ca aktualnie najgorsz� warto��
	double bestCandidateCycleLength = std::numeric_limits<double>::max();

	// Indeksy najlepszej zamiany do uzyskania najlepszego kandydata
	int bestIndexA = 0;
	int bestIndexB = 1;

	// Sprawd� wszystkie mo�liwe zamiany permutacji
	for (int i = 0; i < salesman->getSize(); ++i)
	{
		for (int j = (i + 1); j < salesman->getSize(); ++j)
		{
			// Zamie� permutacje w aktualnym cyklu w poszukiwaniu lepszego cyklu
			this->swap(this->currentCycle, i, j);

			// D�ugo�� cyklu aktualnego kandydata
			double candidateCycleLength = this->hamiltonCycleLength(this->currentCycle);

			// Wylicz d�ugo�� cyklu aktualnego kandydata uwzgl�dniaj�c d�ugoterminow� list� tabu
			double candidateCyclePenalLength = candidateCycleLength + PENAL_LONG_TERM * (*this->tabuListLongTerm)[i][j];

			// Sprawd� czy zamiana jest lepsza ni� w najlepszym kandydacie oraz nie jest na li�cie tabu lub czy zmiana spe�nia kryterium aspiracji
			if ((candidateCyclePenalLength < bestCandidateCycleLength && (*this->tabuList)[i][j] < iteration + 1) || candidateCycleLength < this->currentCycleLength)
			{
				// Zapisz najlepsze indeksy zmiany cyklu
				bestIndexA = i;
				bestIndexB = j;

				// Przypisz d�ugo�ci najlepszego kandydata d�ugo�� aktualnego cyklu kandydata ��cznie z progiem aspiracji
				bestCandidateCycleLength = candidateCyclePenalLength;

				// Dodaj zamian� do listy tabu uwzgl�dniaj�c przez jego czas �ycia w li�cie tabu
				(*this->tabuList)[i][j] = iteration + TABU_TIME;
				(*this->tabuList)[j][i] = iteration + TABU_TIME;
			}

			// Przywr�� aktualny cykl do poprzedniego stanu
			this->swap(this->currentCycle, j, i);

			// Sprawd� czy zamiana istnieje w d�ugoterminowej li�cie tabu i przekroczy�a 10% iteracji algorytmu
			if ((*this->tabuListLongTerm)[i][j] > 0 && iteration > this->numberOfIterations / 10)
			{
				(*this->tabuListLongTerm)[i][j] -= 1;
			}
		}
	}

	// Dodaj zamian� do d�ugoterminowej listy tabu
	(*this->tabuListLongTerm)[bestIndexA][bestIndexB] += 2;

	// Utw�rz najlepszego kandydata
	std::vector<int>* bestCandidate = new std::vector<int>(this->currentCycle->size());

	// Kopia: Aktualny cykl -> Najlepszy kandydat
	copy(this->currentCycle->begin(), this->currentCycle->end(), bestCandidate->begin());

	// Zastosuj nalepsz� zmian� przekszta�caj�c aktualny cykl w najlepszego kandydata
	this->swap(bestCandidate, bestIndexA, bestIndexB);

	// Zwr�� nowy aktualny cykl
	return bestCandidate;
}

// Zamienia dwa wierzcho�ki ze sob� miejscami
void SalesmanTabuSearch::swap(std::vector<int>* hamiltonCycle, unsigned int positionA, unsigned int positionB)
{
	// Je�li nie jest pusty i nie wykracza poza zakres
	if (hamiltonCycle != nullptr)
	{
		if (positionA < hamiltonCycle->size() && positionB < hamiltonCycle->size())
		{
			// Swap
			int copy = hamiltonCycle->at(positionA);
			hamiltonCycle->at(positionA) = hamiltonCycle->at(positionB);
			hamiltonCycle->at(positionB) = copy;
		}
	}
}

std::vector<int>* SalesmanTabuSearch::GetResult()
{
	return this->bestCycle;
}