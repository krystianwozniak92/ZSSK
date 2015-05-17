#include "SalesmanGenetic.h"


// Funkcja wykonuje algorytm i zwraca wynik w postaci wektora reprezentujacego cykl hamiltona.
std::vector<unsigned>* SalesmanGenetic::start(unsigned pop, unsigned mutCosunt, double maxTime)
{
	Timer t;
	unsigned bestLen = 0; // Dlugosc najkrotszej drogi
	unsigned trnmSize = 10; // Wielkosc grupy turniejowej
	unsigned averagePop = 0; // Srednia dlugosc drogi w populacji
	unsigned tempLength = 0;
	long double time = 0;
	std::vector<unsigned> bestHamCycle;
	unsigned* temp = nullptr;
	bool end = false;

	// Uruchomienie licznika
	t.startTimer();
	if (pop > 0)
	{
		// Inicjalizacja populacji osobnikow
		std::vector< std::vector<unsigned> >* population = getRandomPop(pop);
		std::vector< std::vector<unsigned> >* populationTemp = nullptr;
		std::vector< std::vector<unsigned> >* childrensTemp = nullptr;

		// Zresetowanie liczby iteracji
		_iterations = 0;

		// Petla glowna algorytmu. Wywolywana dopoki nie zostanie osiagniete ograniczenie czasowe
		while (time < maxTime)
		{
			populationTemp = new std::vector< std::vector<unsigned> >(pop);

			// Wyszukanie najlepszego cyklu w populacji osobnikow
			for (int i = 0; i < pop; i++)
			{
				tempLength = getLength(&population->at(i));
				if (bestLen == 0 || tempLength < bestLen)
				{
					bestLen = tempLength;
					bestHamCycle = population->at(i);
					time = 0;
				}
				averagePop += tempLength;
			}
			averagePop /= pop;

			// Proces selekcji 
			for (int i = 0; i < pop / 2; i++)
			{
				// Wyselekcjonowanie dwoch najkorzystniejszych rodzicow (metoda selekcji turniejowej)
				temp = getBestParents(population, trnmSize);

				// Krzyzowanie dwoch wyselekcjonowanych rodzicow w celu utworzenia dwojki dzieci
				childrensTemp = crossOver(&population->at(temp[0]), &population->at(temp[1]));

				// Mutacja
				mutate(&childrensTemp->at(0), mutCosunt);
				mutate(&childrensTemp->at(1), mutCosunt);

				// Zapisanie dzieci do tymczasowej struktury
				populationTemp->at(i) = childrensTemp->at(0);
				populationTemp->at(pop - i - 1) = childrensTemp->at(1);

				// Zwolnienie pamieci
				delete[] temp;
				delete childrensTemp;
			}

			if (pop % 2 == 1)
				populationTemp->at(pop / 2) = getRandomPop(1)->at(0);

			t.stopTimer();
			time += t.getElapsedTime();
			t.startTimer();

			delete population;
			population = populationTemp;

			// Inkrementacja liczby iteracji algorytmu
			_iterations++;
		}

		_hamCycle = new std::vector<unsigned>(bestHamCycle);
		_mutCount = mutCosunt;
		_popCount = pop;
	}
	return nullptr;
}

// Konstruktory
SalesmanGenetic::SalesmanGenetic(Salesman* s)
{
	this->_salesman = s;
	_hamCycle = nullptr;
}
SalesmanGenetic::SalesmanGenetic()
{
	this->_salesman = nullptr;
	_hamCycle = nullptr;
}

// Destruktor
SalesmanGenetic::~SalesmanGenetic()
{
	if (this->_hamCycle != nullptr)
	{
		delete _hamCycle;
		_hamCycle = nullptr;
	}
}

// Funkcja zwraca populacje osobnikow o losowych cyklach hamiltona
std::vector< std::vector<unsigned> >* SalesmanGenetic::getRandomPop(unsigned pop)
{
	std::vector< std::vector<unsigned> >* population = nullptr;

	if (_salesman != nullptr)
	{
		population = new std::vector<std::vector<unsigned>>();
		for (int i = 0; i < pop; i++)
		{
			population->push_back(std::vector<unsigned>());
			for (int j = 0; j < _salesman->getSize(); j++)
				population->at(i).push_back(j);

			std::vector< unsigned > temp = population->at(i);
			std::random_shuffle(temp.begin(), temp.end());
			temp.push_back(temp[0]);
			population->at(i) = temp;
		}
	}
	return population;
}

/* Funkcja zwraca dlugosc cyklu hamiltona zachowanego w wektorze cities.
cities - wektor reprezentujacy cykl hamiltona
*/
unsigned SalesmanGenetic::getLength(std::vector<unsigned>* cities)
{
	unsigned length = 0;

	for (int i = 0; i < cities->size() - 1; i++)
		length += _salesman->getDistance(cities->at(i), cities->at(i + 1));

	return length;
}

/* Funkcja zwraca dwoch najkorzystniejszych rodzicow (metoda turniejowa)
population - populacja osobnikow
tourSize - rozmiar grupy turniejowej
*/
unsigned* SalesmanGenetic::getBestParents(std::vector< std::vector<unsigned> >* population, unsigned tourSize)
{
	unsigned* parents = nullptr;
	unsigned* tournament = nullptr;
	unsigned bestTemp;
	unsigned temp;

	if (population->size() > 1)
	{
		parents = new unsigned[2];
		parents[0] = parents[1] = 0;
		tournament = new unsigned[tourSize];

		for (int i = 0; i < 2; i++) // Wyselekcjonowanie dwoch najlepszych osobnikow z grup turniejowych
		{
			for (int j = 0; j < tourSize; j++) // Wypelnienie grupy turniejowej
				tournament[j] = rand() % population->size();

			for (int j = 0; j < tourSize; j++) // Wybranie najlepszego osobnika w grupie turniejowej
			{
				temp = getLength(&population->at(tournament[j]));
				if (parents[i] == 0 || temp < bestTemp)
				{
					parents[i] = tournament[j];
					bestTemp = temp;
				}
			}
		}

		// Zwolnienie pamieci
		delete tournament;
	}
	return parents;
}

/* Funkcja krzyzuje dwoje rodzicow i tworzy nowe potomstwo w postaci dwojki dzieci
(Krzy¿owanie z czêœciowym odwzorowaniem (PMX) )
p1, p2 - wskazniki na rodzicow
return - wskazniki na dwojke dzieci
*/
std::vector< std::vector<unsigned> >* SalesmanGenetic::crossOver(std::vector<unsigned>* p1, std::vector<unsigned>* p2)
{
	std::vector< std::vector<unsigned> >* childrens = nullptr;
	unsigned v0, v1;
	int temp;
	if (p1 != nullptr && p2 != nullptr)
	{
		// Inicjalizacja dwoch nowych dzieci
		childrens = new std::vector< std::vector<unsigned> >;

		// Dodanie nowych instancji dzieci
		childrens->push_back(std::vector<unsigned>(p1->size()));
		childrens->push_back(std::vector<unsigned>(p1->size()));

		// Wypelnienie dzieci miastami, ktore nie istnieja w celu kontrolnym
		for (int i = 0; i < p1->size(); i++)
		{
			childrens->at(0).at(i) = p1->size();
			childrens->at(1).at(i) = p1->size();
		}

		// Wybranie losowej podtrasy
		if (_salesman->getSize() > 7)
		{
			v0 = rand() % (_salesman->getSize() / 4 - 1);
			v1 = (_salesman->getSize() / 0.75 - 1);
		}
		else
		{
			v0 = rand() % (_salesman->getSize() - 1);
			v1 = rand() % (_salesman->getSize() - 1);

			if (v0 > v1)
			{
				temp = v0;
				v0 = v1;
				v1 = temp;
			}
		}

		// Przyporzadkowanie podtrasy (v0 - v1) rodzica 2 do dziecka 1 i na odwrot
		for (int i = 0; i < p1->size() - 1; i++)
		{
			// Jezeli indeks znajduje sie na wylosowanej podtrasie to kopiuj elementy z tej pozycji
			if (i >= v0 && i <= v1)
			{
				childrens->at(0).at(i) = p2->at(i); // Pierwsze dziecko przejmuje geny od drugiego rodzica
				childrens->at(1).at(i) = p1->at(i); // Drugie dziecko przejmuje geny od pierwszego rodzica
			}
		}

		// Uzupelnienie miast poprzez dodanie niepowtarzajacych sie miast z rodzica i do dziecka i na konkretnych pozycjach
		for (int j = 0; j < p1->size() - 1; j++)
		{
			if (j < v0 || j > v1) // Jezeli j-ty element dziecka jest pusty (poza podtrasa) to wstaw element
			{
				// Jezeli j-ty element rodzica nie znajduje sie u dziecka to wstaw na j-tej pozycji
				if (std::find(
					childrens->at(0).begin(), childrens->at(0).end(), p1->at(j)) == childrens->at(0).end())
				{
					childrens->at(0).at(j) = p1->at(j);
				}
				else // W przeciwnym przypadku  (jezeli juz sie znajduje to znajdz element niepowtarzajacy sie od rodzica)
				{
					unsigned temp = 0;
					temp = p1->at(j);
					bool found = false;
					do{ // Wstaw element, ktorego brakuje

						for (int z = 0; z < p1->size() - 1; z++)
						{
							if (childrens->at(0).at(z) == temp)
							{
								temp = p1->at(z);
								break;
							}

							// Element temp nie powtarza sie juz u dziecka, zatem wstawiamy
							if (z == p1->size() - 1 - 1)
							{
								childrens->at(0).at(j) = temp;
								found = true;
							}
						}

					} while (!found);
				}
			}
		}

		// Uzupelnienie miast poprzez dodanie niepowtarzajacych sie miast z rodzica i do dziecka i na konkretnych pozycjach
		for (int j = 0; j < p2->size() - 1; j++)
		{
			if (j < v0 || j > v1) // Jezeli j-ty element dziecka jest pusty (poza podtrasa) to wstaw element
			{
				// Jezeli j-ty element rodzica nie znajduje sie u dziecka to wstaw na j-tej pozycji
				if (std::find(
					childrens->at(1).begin(), childrens->at(1).end(), p2->at(j)) == childrens->at(1).end())
				{
					childrens->at(1).at(j) = p2->at(j);
				}
				else // W przeciwnym przypadku  (jezeli juz sie znajduje to znajdz element niepowtarzajacy sie od rodzica)
				{
					unsigned temp = 0;
					temp = p2->at(j);
					bool found = false;
					do{ // Wstaw element, ktorego brakuje

						for (int z = 0; z < p2->size() - 1; z++)
						{
							if (childrens->at(1).at(z) == temp)
							{
								temp = p2->at(z);
								break;
							}

							// Element temp nie powtarza sie juz u dziecka, zatem wstawiamy
							if (z == p2->size() - 1 - 1)
							{
								childrens->at(1).at(j) = temp;
								found = true;
							}
						}

					} while (!found);
				}
			}
		}


		// Droga powrotna do pierwszego miasta
		childrens->at(0).at(p1->size() - 1) = childrens->at(0).at(0);
		childrens->at(1).at(p1->size() - 1) = childrens->at(1).at(0);
	}

	return childrens;
}

void SalesmanGenetic::mutate(std::vector<unsigned>* children, unsigned count)
{
	unsigned v0, v1;
	unsigned temp;
	for (int i = 0; i < count; i++)
	{
		// Losowe wybieranie genow (miast)
		v0 = rand() % (children->size() - 1);
		do{
			v1 = rand() % (children->size() - 1);
		} while (v1 == v0);

		// Mutacja
		temp = children->at(v0);
		children->at(v0) = children->at(v1);
		children->at(v1) = temp;
	}

	// Korekta 
	children->at(children->size() - 1) = children->at(0);
}

unsigned SalesmanGenetic::getBestHamCycLen()
{
	unsigned result = 0;
	if (_salesman != nullptr)
	{
		for (int i = 0; i < _hamCycle->size() - 1; i++)
			result += _salesman->getDistance(_hamCycle->at(i), _hamCycle->at(i + 1));
	}
	return result;
}

/* Funkcja zwraca wielkosc populacji na ktorej opieral sie algorytm
*/
unsigned SalesmanGenetic::getPopSize()
{
	return _popCount;
}

/* Funkcja zwraca liczbe mutacji dla pojedynczego osobnika w procesie mutacji
*/
unsigned SalesmanGenetic::getMutCount()
{
	return _mutCount;
}

/* Funkcja zwraca liczbe iteracji algorytmu
*/
unsigned SalesmanGenetic::getIterCount()
{
	return _iterations;
}

std::vector<unsigned>* SalesmanGenetic::GetResult()
{
	return this->_hamCycle;
}