#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <time.h>

class Salesman
{
private:
	// Macierz sasiedztwa
	std::vector<std::vector<double>>* _mx;

	// Ilosc miast
	unsigned int _n;

	// Zwroc odleglosc miedzy puntkami
	double getDistance(double P1_X, double P1_Y, double P2_X, double P2_Y);

public:

	// Konstruktor
	Salesman();

	// Konstruktor parametryczny
	Salesman(unsigned int n);

	Salesman(std::vector<std::vector<double>>* vec);
	// Konstruktor (z pliku)
	Salesman(std::string filepath);

	// Destruktor
	~Salesman();

	// Zapisz do pliku
	void save(std::string filename);

	// Wyswielt
	void show();

	// Zwróæ Ilosc miast
	int getSize() const;

	// Zwróæ odleglosc miedzy miastami
	double getDistance(unsigned int, unsigned int) const;

	// Nadaj odleglosc miedzy miastami
	void setDistance(unsigned int, unsigned int, double);
};


