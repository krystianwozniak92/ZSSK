#include "SalesmanAnnealing.h"

// Konstruktor
SalesmanAnnealing::SalesmanAnnealing()
{
	this->salesman = nullptr;
	this->bestGlobalCycle = nullptr;
	this->lambda = 0;
	this->iterations = 0;
	this->initTemperature = 0;
}

// Konstruktor
SalesmanAnnealing::SalesmanAnnealing(Salesman* salesman, double lambda)
{
	this->salesman = salesman;
	this->bestGlobalCycle = nullptr;
	this->lambda = lambda;
	this->iterations = 0;
	this->initTemperature = 0;
}

// Destruktor
SalesmanAnnealing::~SalesmanAnnealing()
{
	if (this->bestGlobalCycle != nullptr)
	{
		delete this->bestGlobalCycle;
	}
}

// Uruchamia algorytm
bool SalesmanAnnealing::start()
{
	// SRAND
	srand(static_cast<unsigned int>(time(nullptr)));

	// Numery wierzcho³ków
	int positionA = 0;
	int positionB = 0;

	// Aktualna temperatura
	double currentTemperature = 0;

	// Temperatura zatrzymania algorytmu
	double stopTemperature = 0.2f;

	// Cykle Hamiltona
	std::vector<int>* tempCycle;
	std::vector<int>* bestCycleLocal;
	std::vector<int>* bestCycleGlobal;

	// Jeœli TSP nie jest pusty
	if (salesman != nullptr)
	{
		if (salesman->getSize() > 0)
		{
			// Wygeneruj losowy cykl Hamiltona
			bestCycleLocal = this->hamiltonRandomCycle();

			// Zaalokuj cykle
			tempCycle = new std::vector<int>(bestCycleLocal->size());
			bestCycleGlobal = new std::vector<int>(bestCycleLocal->size());
			this->bestGlobalCycle = new std::vector<int>();

			// Kopia: Najlepszy lokalny cykl Hamiltona -> Tymczasowego cykl Hamiltona
			copy(bestCycleLocal->begin(), bestCycleLocal->end(), tempCycle->begin());

			// Kopia: Najlepszy lokalny cykl Hamiltona -> Najlepszego globalny cykl Hamiltona
			copy(bestCycleLocal->begin(), bestCycleLocal->end(), bestCycleGlobal->begin());

			// Ustaw iloœæ iteracji na zero
			this->iterations = 0;

			// Oblicz temperaturê pocz¹tkow¹
			this->initTemperature = this->calcInitTemperature();

			// Ustaw aktualn¹ temperaturê
			currentTemperature = this->initTemperature;

			// Wykonuj dopóki temperatura koñcowa nie osi¹gniêta
			do
			{
				// Zwiêksz licznik iteracji
				this->iterations++;

				// Wylosuj numery wierzcho³ków
				do
				{
					positionA = (rand() % salesman->getSize());
					positionB = (rand() % salesman->getSize());
				} while (positionA == positionB);

				// Swap wierzcho³ków w tymczasowym cyklu Hamiltona
				swap(tempCycle, positionA, positionB);

				// Jeœli nowy cykl jest lepszy lub równie dobry
				if (hamiltonCycleLength(tempCycle) <= hamiltonCycleLength(bestCycleLocal))
				{
					// WprowadŸ zmianê w najlepszym lokalnym cyklu Hamiltona
					swap(bestCycleLocal, positionA, positionB);

					// Jeœli nowy cykl jest lepszy lub równie dobry
					if (hamiltonCycleLength(bestCycleLocal) <= hamiltonCycleLength(bestCycleGlobal))
					{
						// Kopiuj cykl do najlepszego globalnego cyklu Hamiltona
						hamiltonCopyCycle(bestCycleLocal, bestCycleGlobal);
					}
				}

				// Jeœli nowy cykl jest gorszy
				else
				{
					// Wylosuj szansê
					double chance = ((double)rand() / (RAND_MAX));

					// Oblicz prawdopodobieñstwo zmiany cyklu
					double prob = calcCycleChangeProbability(hamiltonCycleLength(tempCycle) - hamiltonCycleLength(bestCycleLocal), currentTemperature);

					// WprowadŸ zmianê
					if (chance < prob)
					{
						swap(bestCycleLocal, positionA, positionB);
					}
					else
					{
						swap(tempCycle, positionB, positionA);
					}
				}

				// Obni¿ temperaturê
				currentTemperature = decTemperature(currentTemperature);
			} while (currentTemperature > stopTemperature);

			// Kopiuj cykl
			hamiltonCopyCycle(bestCycleGlobal, this->bestGlobalCycle);

			// Zwolnij pamiêæ
			if (tempCycle != nullptr)
			{
				delete tempCycle;
			}

			// Zwolnij pamiêæ
			if (bestCycleLocal != nullptr)
			{
				delete bestCycleLocal;
			}

			// Zwolnij pamiêæ
			if (bestCycleGlobal != nullptr)
			{
				delete bestCycleGlobal;
			}

			// Wróæ sukces
			return true;
		}
	}

	// Wróæ pora¿kê
	return false;
}

// Zwróæ d³ugoœæ znalezionego cyklu Hamiltona
double SalesmanAnnealing::getBestHamiltonCycleLength()
{
	if (this->bestGlobalCycle != nullptr)
	{
		if (this->bestGlobalCycle->size() > 0)
		{
			return this->hamiltonCycleLength(this->bestGlobalCycle);
		}
	}

	return 0;
}

// Zwróæ iloœæ iteracji
long SalesmanAnnealing::getIterations()
{
	return this->iterations;
}

// Zwróæ pocz¹tkow¹ temperaturê
double SalesmanAnnealing::getInitTemperature()
{
	return this->initTemperature;
}

// Zwróæ wartoœæ parametru lambda
double SalesmanAnnealing::getLambda()
{
	return this->lambda;
}

// Funkcja obliczaj¹ca temperaturê pocz¹tkow¹
double SalesmanAnnealing::calcInitTemperature()
{
	// Temperatura
	double temperature = 0;

	// Zmienna pomocnicza
	double tempDelta = 0;

	// Cykle Hamiltona
	std::vector<int>* hamiltonCycleOne;
	std::vector<int>* hamiltonCycleTwo;

	// Wylosuj pierwszy cykl Hamiltona
	hamiltonCycleOne = hamiltonRandomCycle();

	// Wykonaj (N * N) razy
	for (int i = 0; i < salesman->getSize() * salesman->getSize(); ++i)
	{
		// Wylosuj drugi cykl Hamiltona
		hamiltonCycleTwo = hamiltonRandomCycle();

		// Oblicz ró¿nicê d³ugoœci
		tempDelta = hamiltonCycleLength(hamiltonCycleTwo) - hamiltonCycleLength(hamiltonCycleOne);

		// Zwolnij pamiêæ
		if (hamiltonCycleTwo != nullptr)
		{
			delete hamiltonCycleTwo;
		}

		// SprawdŸ ró¿nicê
		if (tempDelta > temperature)
		{
			temperature = tempDelta;
		}
	}

	// Zwolnij pamiêæ
	if (hamiltonCycleOne != nullptr)
	{
		delete hamiltonCycleOne;
	}

	// Zwróc temperaturê
	return temperature;
}

// Funkcja obliczaj¹ca prawdopodobieñstwo zmiany cyklu Hamiltona P(deltaL) = exp(- deltaL / T)
double SalesmanAnnealing::calcCycleChangeProbability(double deltaL, double temperature)
{
	return exp(-deltaL / temperature);
}

// Funkcja kopiuj¹ca cykl
void SalesmanAnnealing::hamiltonCopyCycle(std::vector<int>* source, std::vector<int>* destination)
{
	destination->clear();
	destination->assign(source->begin(), source->end());
}

// Funkcja losuj¹ca cykl Hamiltona
double SalesmanAnnealing::hamiltonCycleLength(std::vector<int>* hamiltonCycle)
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

// Funkcja zwracaj¹ca d³ugoœæ cyklu Hamiltona
std::vector<int>* SalesmanAnnealing::hamiltonRandomCycle()
{
	// Jeœli macierz s¹siedztwa nie jest pusta
	if (salesman->getSize() > 0)
	{
		// Losowy cykl Hamiltona
		std::vector<int>* randomCycle = new std::vector<int>();

		// Wpisz wszystkie wierzcho³ki
		for (int i = 0; i < salesman->getSize(); ++i)
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

// Funkcja sprawdzaj¹ca iloœæ s¹siadów
int SalesmanAnnealing::checkNeighboursCount()
{
	// Podziel szerokoœæ macierzy przez 3
	int neighbours = salesman->getSize() / 3;

	// Jeœli iloœæ jest równa zero to pozosta³ jeden
	if (neighbours == 0)
	{
		return 1;
	}

	// Zwróæ iloœæ s¹siadów
	return neighbours;
}

// Funkcja obni¿aj¹ca temperaturê
double SalesmanAnnealing::decTemperature(double temperature)
{
	return (this->lambda * temperature);
}

// Funkcja zamieniaj¹ca dwa wierzcho³ki ze sob¹ miejscami
void SalesmanAnnealing::swap(std::vector<int>* hamiltonCycle, unsigned int positionA, unsigned int positionB)
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

// Funkcja zamieniaj¹ca dwa losowe wierzcho³ki ze sob¹ miejscami
void SalesmanAnnealing::swapRandomly(std::vector<int>* hamiltonCycle)
{
	// Jeœli cykl nie jest pusty i posiada dwa wierzcho³ki
	if (hamiltonCycle != nullptr)
	{
		if (hamiltonCycle->size() > 1)
		{
			// Indeksy wierzcho³ków
			int positionA = (rand() % hamiltonCycle->size());
			int positionB = (rand() % hamiltonCycle->size());

			// Wylosuj drugi wierzcho³ek
			while (positionA == positionB)
			{
				positionA = (rand() % hamiltonCycle->size());
				positionB = (rand() % hamiltonCycle->size());
			};

			// Swap
			int copy = hamiltonCycle->at(positionA);
			hamiltonCycle->at(positionA) = hamiltonCycle->at(positionB);
			hamiltonCycle->at(positionB) = copy;
		}
	}
}

std::vector<int>* SalesmanAnnealing::GetResult()
{
	return this->bestGlobalCycle;
}