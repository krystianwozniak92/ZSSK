#pragma once
#include "Knapsack.h"
#include <queue>
#include <vector>

class KnapsackDynamic
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
	Knapsack* knap;

public:
	KnapsackDynamic();
	KnapsackDynamic(Knapsack*);
	~KnapsackDynamic();
	int knapSack(int wt[], int val[], int n, Knapsack*); //Zwraca wynik 


};

