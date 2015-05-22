#include "Salesman.h"

// Konstruktor
Salesman::Salesman()
{
	// Zerowa ilość miast
	this->_n = 0;

	// Pusta macierz sąsiedztwa
	this->_mx = nullptr;
}

// Konstruktor parametryczny
Salesman::Salesman(unsigned int n)
{
	// SRAND
	srand(static_cast<unsigned int>(time(NULL)));

	// ilość miast
	this->_n = n;

	// Jeœli ilość miast jest poprawna
	if (this->_n > 0)
	{
		// Utwórz macierz
		this->_mx = new std::vector<std::vector<double>>(this->_n, std::vector<double>(this->_n));

		// Wypełnij macierz sąsiedztwa
		for (unsigned int i = 0; i < this->_n; ++i)
		{
			for (unsigned int j = 0; j < this->_n; ++j)
			{
				// Losuj wartości
				if (i != j)
				{
					(*this->_mx)[i][j] = static_cast<double>(rand() % 100 + 1);
				}
				else
				{
					(*this->_mx)[i][j] = 0;
				}
			}
		}
	}
	else
	{
		// Zerowa ilość miast
		this->_n = 0;

		// Pusta macierz sąsiedztwa
		this->_mx = nullptr;
	}
}

// Destruktor
Salesman::~Salesman()
{
	if (this->_mx != nullptr)
	{
		delete this->_mx;
		this->_mx = nullptr;
	}
}


// wyświetl
void Salesman::show()
{
	std::cout << std::endl;
	std::cout.width(2);
	std::cout << std::right << "\\";

	for (unsigned int i = 0; i < this->_n; ++i)
	{
		std::cout.width(4);
		std::cout << std::right << i;
	}

	std::cout << std::endl;

	for (unsigned int i = 0; i < this->_n; ++i)
	{
		std::cout.width(2);
		std::cout << std::right << i;

		for (unsigned int j = 0; j < this->_n; ++j)
		{
			std::cout.width(4);
			std::cout << std::right << (*this->_mx)[i][j], 2;
		}

		std::cout << std::endl;
	}
}

// Zwróc ilość miast
int Salesman::getSize() const
{
	return this->_n;
}

// Zwróc odleglosci między miastami
double Salesman::getDistance(unsigned int row, unsigned int col) const
{
	if (row < this->_n && col < this->_n && this->_n > 0)
	{
		return (*this->_mx)[row][col];
	}
	else
	{
		return 0;
	}
}

// Nadaj odleglosci między miastami
void Salesman::setDistance(unsigned int row, unsigned int col, double distance)
{
	if (row < this->_n && col < this->_n && this->_n > 0)
	{
		(*this->_mx)[row][col] = distance;
	}
}

// Zwraca odleglosci między puntkami P1 oraz P2
double Salesman::getDistance(double P1_X, double P1_Y, double P2_X, double P2_Y)
{
	return sqrt(pow((P2_X - P1_X), 2) + pow((P2_Y - P1_Y), 2));
}

Salesman::Salesman(std::vector<std::vector<double>>* vec)
{
	this->_mx = vec;
	this->_n = (*vec)[0].size();
}