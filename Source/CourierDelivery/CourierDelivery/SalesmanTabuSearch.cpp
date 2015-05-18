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
	// Usuñ aktualny cykl
	if (this->currentCycle != nullptr)
	{
		delete this->currentCycle;
	}

	// Usuñ najlepszy cykl
	if (this->bestCycle != nullptr)
	{
		delete this->bestCycle;
	}

	// Usuñ macierz tabu
	if (this->tabuList != nullptr)
	{
		delete this->tabuList;
	}

	// Usuñ pierwsz¹ macierz tabu
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

	// D³ugoœæ aktualnie najlepszego cyklu
	this->bestCycleLength = this->hamiltonCycleLength(this->bestCycle);

	// Pêtla losuj¹ca kandydatów
	for (int candidate = 0; candidate < CANDIDATES; ++candidate)
	{
		// Wyzeruj licznik znalezionych nieefektywnych cykli
		int inefficientCycleCounter = 0;

		// Wygeneruj losowy cykl Hamiltona
		this->currentCycle = this->hamiltonRandomCycle();

		// D³ugoœæ aktualnego cyklu
		this->currentCycleLength = this->hamiltonCycleLength(this->currentCycle);

		// Zresetuj listê tabu
		this->resetTabuLists();

		// Pêtla iteracji algorytmu
		for (int i = 0; i < this->numberOfIterations; i++)
		{
			// Pobierz najlepszy s¹siedni cykl w zale¿noœci od iteracji
			std::vector<int>* bestCandidate = this->getBestCandidate(i);

			// D³ugoœæ aktualnego cyklu
			double bestCandidateLength = this->hamiltonCycleLength(bestCandidate);

			// Jeœli aktualny cykl jest lepszy od najlepszego kadydata
			if (bestCandidateLength < this->currentCycleLength)
			{
				// Wyzeruj licznik znalezionych nieefektywnych cykli
				inefficientCycleCounter = 0;

				// Kopia: Najlepszy kandydant -> Aktualny cykl
				copy(bestCandidate->begin(), bestCandidate->end(), this->currentCycle->begin());

				// Przypisz za d³ugoœæ aktulanego cyklu d³ugoœæ najlepszego kandydata
				this->currentCycleLength = bestCandidateLength;

				// Jeœli aktualny cykl jest lepszy od najlepszego cyklu
				if (this->currentCycleLength < this->bestCycleLength)
				{
					// Kopia: Aktualny cykl -> Najlepszy cykl
					copy(currentCycle->begin(), currentCycle->end(), this->bestCycle->begin());

					// Przypisz za d³ugoœæ najlepszego cyklu d³ugoœæ aktualnego cyklu
					this->bestCycleLength = this->currentCycleLength;
				}
			}
			else
			{
				// Zwiêksz licznik znalezionych nieefektywnych cykli
				inefficientCycleCounter++;

				// SprawdŸ licznik znalezionych nieefektywnych cykli
				if (inefficientCycleCounter > numberOfIterations / 4)
				{
					break;
				}
			}
		}
	}
}

// Zwraca d³ugoœæ najlepszego cyklu
double SalesmanTabuSearch::getBestCycleLength()
{
	// Jeœli cykl nie jest pusty
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
	// Jeœli macierz s¹siedztwa nie jest pusta
	if (this->salesman->getSize() > 0)
	{
		// Losowy cykl Hamiltona
		std::vector<int>* randomCycle = new std::vector<int>();

		// Wpisz wszystkie wierzcho³ki
		for (int i = 0; i < this->salesman->getSize(); ++i)
		{
			randomCycle->push_back(i);
		}

		// Wymieszaj
		random_shuffle(randomCycle->begin(), randomCycle->end());

		// Zwróæ cykl
		return randomCycle;
	}

	// Zwróc pusty cykl
	return nullptr;
}

// Zwraca d³ugoœæ cyklu Hamiltona
double SalesmanTabuSearch::hamiltonCycleLength(std::vector<int>* hamiltonCycle)
{
	// D³ugoœæ cyklu Hamiltona
	double length = 0.0f;

	// Zmienne pomocnicze
	int v1 = 0;
	int v2 = 0;

	// Jeœli cykl nie jest pusty
	if (hamiltonCycle != nullptr)
	{
		if (hamiltonCycle->size() > 0)
		{
			// Numer pierwszego wierzcho³ka
			v1 = *(hamiltonCycle->begin());

			// Dodaj wagi wszystkich krawêdzi
			for (std::vector<int>::iterator it = hamiltonCycle->begin() + 1; it < hamiltonCycle->end(); ++it)
			{
				// Numer kolejnego wierzcho³ka
				v2 = *it;

				// Dodaj wagê krawêdzi do d³ugoœci
				length += salesman->getDistance(v1, v2);

				// Przepisz numer dalej
				v1 = v2;
			}

			// Dodaj wagê krawêdzi ³¹cz¹cej pierwszy i ostatni wierzcho³ek
			v1 = *(hamiltonCycle->begin());
			length += salesman->getDistance(v1, v2);

			// Zwróc d³ugoœæ
			return length;
		}
	}

	// Zwróæ zero
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
	// D³ugoœæ cyklu najlepszego kandydata przyjmuj¹ca aktualnie najgorsz¹ wartoœæ
	double bestCandidateCycleLength = std::numeric_limits<double>::max();

	// Indeksy najlepszej zamiany do uzyskania najlepszego kandydata
	int bestIndexA = 0;
	int bestIndexB = 1;

	// SprawdŸ wszystkie mo¿liwe zamiany permutacji
	for (int i = 0; i < salesman->getSize(); ++i)
	{
		for (int j = (i + 1); j < salesman->getSize(); ++j)
		{
			// Zamieñ permutacje w aktualnym cyklu w poszukiwaniu lepszego cyklu
			this->swap(this->currentCycle, i, j);

			// D³ugoœæ cyklu aktualnego kandydata
			double candidateCycleLength = this->hamiltonCycleLength(this->currentCycle);

			// Wylicz d³ugoœæ cyklu aktualnego kandydata uwzglêdniaj¹c d³ugoterminow¹ listê tabu
			double candidateCyclePenalLength = candidateCycleLength + PENAL_LONG_TERM * (*this->tabuListLongTerm)[i][j];

			// SprawdŸ czy zamiana jest lepsza ni¿ w najlepszym kandydacie oraz nie jest na liœcie tabu lub czy zmiana spe³nia kryterium aspiracji
			if ((candidateCyclePenalLength < bestCandidateCycleLength && (*this->tabuList)[i][j] < iteration + 1) || candidateCycleLength < this->currentCycleLength)
			{
				// Zapisz najlepsze indeksy zmiany cyklu
				bestIndexA = i;
				bestIndexB = j;

				// Przypisz d³ugoœci najlepszego kandydata d³ugoœæ aktualnego cyklu kandydata ³¹cznie z progiem aspiracji
				bestCandidateCycleLength = candidateCyclePenalLength;

				// Dodaj zamianê do listy tabu uwzglêdniaj¹c przez jego czas ¿ycia w liœcie tabu
				(*this->tabuList)[i][j] = iteration + TABU_TIME;
				(*this->tabuList)[j][i] = iteration + TABU_TIME;
			}

			// Przywróæ aktualny cykl do poprzedniego stanu
			this->swap(this->currentCycle, j, i);

			// SprawdŸ czy zamiana istnieje w d³ugoterminowej liœcie tabu i przekroczy³a 10% iteracji algorytmu
			if ((*this->tabuListLongTerm)[i][j] > 0 && iteration > this->numberOfIterations / 10)
			{
				(*this->tabuListLongTerm)[i][j] -= 1;
			}
		}
	}

	// Dodaj zamianê do d³ugoterminowej listy tabu
	(*this->tabuListLongTerm)[bestIndexA][bestIndexB] += 2;

	// Utwórz najlepszego kandydata
	std::vector<int>* bestCandidate = new std::vector<int>(this->currentCycle->size());

	// Kopia: Aktualny cykl -> Najlepszy kandydat
	copy(this->currentCycle->begin(), this->currentCycle->end(), bestCandidate->begin());

	// Zastosuj nalepsz¹ zmianê przekszta³caj¹c aktualny cykl w najlepszego kandydata
	this->swap(bestCandidate, bestIndexA, bestIndexB);

	// Zwróæ nowy aktualny cykl
	return bestCandidate;
}

// Zamienia dwa wierzcho³ki ze sob¹ miejscami
void SalesmanTabuSearch::swap(std::vector<int>* hamiltonCycle, unsigned int positionA, unsigned int positionB)
{
	// Jeœli nie jest pusty i nie wykracza poza zakres
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