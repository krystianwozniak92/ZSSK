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

	// Iloœæ iteracji
	long iterations;

	// Temperatura pocz¹tkowa
	double initTemperature;

	// Parametr lambda
	double lambda;

	// Funkcja obliczaj¹ca temperaturê pocz¹tkow¹
	double calcInitTemperature();

	// Funkcja obliczaj¹ca prawdopodobieñstwo zmiany cyklu Hamiltona P(deltaL) = exp(- deltaL / T)
	double calcCycleChangeProbability(double, double);

	// Funkcja kopiuj¹ca cykl Hamiltona
	void hamiltonCopyCycle(std::vector<int>*, std::vector<int>*);

	// Funkcja zwracaj¹ca d³ugoœæ cyklu Hamiltona
	double hamiltonCycleLength(std::vector<int>*);

	// Funkcja losuj¹ca cykl Hamiltona
	std::vector<int>* hamiltonRandomCycle();

	// Funkcja sprawdzaj¹ca iloœæ s¹siadów
	int checkNeighboursCount();

	// Funkcja obni¿aj¹ca temperaturê
	double decTemperature(double);

	// Funkcja zamieniaj¹ca dwa wierzcho³ki ze sob¹ miejscami
	void swap(std::vector<int>*, unsigned int, unsigned int);

	// Funkcja zamieniaj¹ca dwa losowe wierzcho³ki ze sob¹ miejscami
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

	// Zwróæ d³ugoœæ znalezionego cyklu Hamiltona
	double getBestHamiltonCycleLength();

	// Zwróæ iloœæ iteracji
	long getIterations();

	// Zwróæ pocz¹tkow¹ temperaturê
	double getInitTemperature();

	// Zwróæ wartoœæ parametru lambda
	double getLambda();

	std::vector<int>* GetResult();
};
