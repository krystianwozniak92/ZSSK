#pragma once
#include "Knapsack.h"
#include <queue>
#include <vector>

class KnapsackBB
{

private: //deklaracje zmiennych i wektorow z ktorych korzystam
	int poziom_;
	int wartosc_;
	int maxWartosc_;
	int waga_;
	int bound_;
	int wynik_;
	std::vector<int> wart;
	std::vector<int> wag;

public:
	KnapsackBB();
	KnapsackBB(Knapsack*);
	~KnapsackBB();
	int bound(KnapsackBB u, int n, int W, std::vector<int> pVa, std::vector<int> wVa); //zwraca g�ra granice
	int plecak(int n, int waga[], int wartosc[], int W); //zwracamy najlepsze rozwiazanie


};

