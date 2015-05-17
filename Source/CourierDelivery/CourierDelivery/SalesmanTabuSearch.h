#pragma once

#include <algorithm>
#include <vector>
#include <queue>

#include "Salesman.h"
#include "Edge.h"

class SalesmanTabuSearch
{
private:

	int numberOfIterations;								// Ilo�� iteracji

	double currentCycleLength;							// D�ugo�� aktualnego cyklu
	double bestCycleLength;								// D�ugo�� najlepszego cyklu

	Salesman* salesman;									// Obiekt klasy TSP

	std::vector<int>* currentCycle;						// Aktualny cykl Hamiltona
	std::vector<int>* bestCycle;						// Najlepszy cykl Hamiltona

	std::vector<std::vector<int>>* tabuList;			// Macierz tabu
	std::vector<std::vector<int>>* tabuListLongTerm;	// Macierz tabu

public:

	// Konstruktor
	SalesmanTabuSearch();

	// Konstruktor
	SalesmanTabuSearch(Salesman*, int);

	// Destruktor
	~SalesmanTabuSearch();

	// Uruchamia algorytm
	void start();

	// Zwraca d�ugo�� najlepszego cyklu
	double getBestCycleLength();

	std::vector<int>* GetResult();
private:

	// Losuje cykl Hamiltona
	std::vector<int>* hamiltonRandomCycle();

	// Zwraca d�ugo�� cyklu Hamiltona
	double hamiltonCycleLength(std::vector<int>*);

	// Resetuje macierze tabu
	void resetTabuLists();

	// Znajduje najlepszego kandydata
	std::vector<int>* getBestCandidate(int);

	// Zamienia dwa wierzcho�ki ze sob� miejscami
	void swap(std::vector<int>*, unsigned int, unsigned int);

	
};

