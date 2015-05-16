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

	// Numery wierzcho�k�w
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

	// Je�li TSP nie jest pusty
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

			// Ustaw ilo�� iteracji na zero
			this->iterations = 0;

			// Oblicz temperatur� pocz�tkow�
			this->initTemperature = this->calcInitTemperature();

			// Ustaw aktualn� temperatur�
			currentTemperature = this->initTemperature;

			// Wykonuj dop�ki temperatura ko�cowa nie osi�gni�ta
			do
			{
				// Zwi�ksz licznik iteracji
				this->iterations++;

				// Wylosuj numery wierzcho�k�w
				do
				{
					positionA = (rand() % salesman->getSize());
					positionB = (rand() % salesman->getSize());
				} while (positionA == positionB);

				// Swap wierzcho�k�w w tymczasowym cyklu Hamiltona
				swap(tempCycle, positionA, positionB);

				// Je�li nowy cykl jest lepszy lub r�wnie dobry
				if (hamiltonCycleLength(tempCycle) <= hamiltonCycleLength(bestCycleLocal))
				{
					// Wprowad� zmian� w najlepszym lokalnym cyklu Hamiltona
					swap(bestCycleLocal, positionA, positionB);

					// Je�li nowy cykl jest lepszy lub r�wnie dobry
					if (hamiltonCycleLength(bestCycleLocal) <= hamiltonCycleLength(bestCycleGlobal))
					{
						// Kopiuj cykl do najlepszego globalnego cyklu Hamiltona
						hamiltonCopyCycle(bestCycleLocal, bestCycleGlobal);
					}
				}

				// Je�li nowy cykl jest gorszy
				else
				{
					// Wylosuj szans�
					double chance = ((double)rand() / (RAND_MAX));

					// Oblicz prawdopodobie�stwo zmiany cyklu
					double prob = calcCycleChangeProbability(hamiltonCycleLength(tempCycle) - hamiltonCycleLength(bestCycleLocal), currentTemperature);

					// Wprowad� zmian�
					if (chance < prob)
					{
						swap(bestCycleLocal, positionA, positionB);
					}
					else
					{
						swap(tempCycle, positionB, positionA);
					}
				}

				// Obni� temperatur�
				currentTemperature = decTemperature(currentTemperature);
			} while (currentTemperature > stopTemperature);

			// Kopiuj cykl
			hamiltonCopyCycle(bestCycleGlobal, this->bestGlobalCycle);

			// Zwolnij pami��
			if (tempCycle != nullptr)
			{
				delete tempCycle;
			}

			// Zwolnij pami��
			if (bestCycleLocal != nullptr)
			{
				delete bestCycleLocal;
			}

			// Zwolnij pami��
			if (bestCycleGlobal != nullptr)
			{
				delete bestCycleGlobal;
			}

			// Wr�� sukces
			return true;
		}
	}

	// Wr�� pora�k�
	return false;
}

// Zwr�� d�ugo�� znalezionego cyklu Hamiltona
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

// Zwr�� ilo�� iteracji
long SalesmanAnnealing::getIterations()
{
	return this->iterations;
}

// Zwr�� pocz�tkow� temperatur�
double SalesmanAnnealing::getInitTemperature()
{
	return this->initTemperature;
}

// Zwr�� warto�� parametru lambda
double SalesmanAnnealing::getLambda()
{
	return this->lambda;
}

// Funkcja obliczaj�ca temperatur� pocz�tkow�
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

		// Oblicz r�nic� d�ugo�ci
		tempDelta = hamiltonCycleLength(hamiltonCycleTwo) - hamiltonCycleLength(hamiltonCycleOne);

		// Zwolnij pami��
		if (hamiltonCycleTwo != nullptr)
		{
			delete hamiltonCycleTwo;
		}

		// Sprawd� r�nic�
		if (tempDelta > temperature)
		{
			temperature = tempDelta;
		}
	}

	// Zwolnij pami��
	if (hamiltonCycleOne != nullptr)
	{
		delete hamiltonCycleOne;
	}

	// Zwr�c temperatur�
	return temperature;
}

// Funkcja obliczaj�ca prawdopodobie�stwo zmiany cyklu Hamiltona P(deltaL) = exp(- deltaL / T)
double SalesmanAnnealing::calcCycleChangeProbability(double deltaL, double temperature)
{
	return exp(-deltaL / temperature);
}

// Funkcja kopiuj�ca cykl
void SalesmanAnnealing::hamiltonCopyCycle(std::vector<int>* source, std::vector<int>* destination)
{
	destination->clear();
	destination->assign(source->begin(), source->end());
}

// Funkcja losuj�ca cykl Hamiltona
double SalesmanAnnealing::hamiltonCycleLength(std::vector<int>* hamiltonCycle)
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

// Funkcja zwracaj�ca d�ugo�� cyklu Hamiltona
std::vector<int>* SalesmanAnnealing::hamiltonRandomCycle()
{
	// Je�li macierz s�siedztwa nie jest pusta
	if (salesman->getSize() > 0)
	{
		// Losowy cykl Hamiltona
		std::vector<int>* randomCycle = new std::vector<int>();

		// Wpisz wszystkie wierzcho�ki
		for (int i = 0; i < salesman->getSize(); ++i)
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

// Funkcja sprawdzaj�ca ilo�� s�siad�w
int SalesmanAnnealing::checkNeighboursCount()
{
	// Podziel szeroko�� macierzy przez 3
	int neighbours = salesman->getSize() / 3;

	// Je�li ilo�� jest r�wna zero to pozosta� jeden
	if (neighbours == 0)
	{
		return 1;
	}

	// Zwr�� ilo�� s�siad�w
	return neighbours;
}

// Funkcja obni�aj�ca temperatur�
double SalesmanAnnealing::decTemperature(double temperature)
{
	return (this->lambda * temperature);
}

// Funkcja zamieniaj�ca dwa wierzcho�ki ze sob� miejscami
void SalesmanAnnealing::swap(std::vector<int>* hamiltonCycle, unsigned int positionA, unsigned int positionB)
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

// Funkcja zamieniaj�ca dwa losowe wierzcho�ki ze sob� miejscami
void SalesmanAnnealing::swapRandomly(std::vector<int>* hamiltonCycle)
{
	// Je�li cykl nie jest pusty i posiada dwa wierzcho�ki
	if (hamiltonCycle != nullptr)
	{
		if (hamiltonCycle->size() > 1)
		{
			// Indeksy wierzcho�k�w
			int positionA = (rand() % hamiltonCycle->size());
			int positionB = (rand() % hamiltonCycle->size());

			// Wylosuj drugi wierzcho�ek
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