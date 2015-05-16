#pragma once

#include <algorithm>
#include <vector>
#include <time.h>

#include "Salesman.h"

class SalesmanAnnealing
{
private:

	// Klasa TSP
	Salesman* salesman;

	// Najlepszy globalny cykl Hamiltona
	std::vector<int>* bestGlobalCycle;

	// Ilo�� iteracji
	long iterations;

	// Temperatura pocz�tkowa
	double initTemperature;

	// Parametr lambda
	double lambda;

	// Funkcja obliczaj�ca temperatur� pocz�tkow�
	double calcInitTemperature();

	// Funkcja obliczaj�ca prawdopodobie�stwo zmiany cyklu Hamiltona P(deltaL) = exp(- deltaL / T)
	double calcCycleChangeProbability(double, double);

	// Funkcja kopiuj�ca cykl Hamiltona
	void hamiltonCopyCycle(std::vector<int>*, std::vector<int>*);

	// Funkcja zwracaj�ca d�ugo�� cyklu Hamiltona
	double hamiltonCycleLength(std::vector<int>*);

	// Funkcja losuj�ca cykl Hamiltona
	std::vector<int>* hamiltonRandomCycle();

	// Funkcja sprawdzaj�ca ilo�� s�siad�w
	int checkNeighboursCount();

	// Funkcja obni�aj�ca temperatur�
	double decTemperature(double);

	// Funkcja zamieniaj�ca dwa wierzcho�ki ze sob� miejscami
	void swap(std::vector<int>*, unsigned int, unsigned int);

	// Funkcja zamieniaj�ca dwa losowe wierzcho�ki ze sob� miejscami
	void swapRandomly(std::vector<int>*);

public:

	// Konstruktor
	SalesmanAnnealing();

	// Konstruktor
	SalesmanAnnealing(Salesman*, double);

	// Destruktor
	~SalesmanAnnealing();

	// Uruchamia algorytm
	bool start();

	// Zwr�� d�ugo�� znalezionego cyklu Hamiltona
	double getBestHamiltonCycleLength();

	// Zwr�� ilo�� iteracji
	long getIterations();

	// Zwr�� pocz�tkow� temperatur�
	double getInitTemperature();

	// Zwr�� warto�� parametru lambda
	double getLambda();

	std::vector<int>* GetResult();
};
