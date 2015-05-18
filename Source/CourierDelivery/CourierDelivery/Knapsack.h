#pragma once
#include <queue>
#include <vector>

class Knapsack
{
private:
	int rozmiar;
public:
	Knapsack();
	Knapsack(int rozmiar_);
	~Knapsack();
	int max_(int a, int b); //zwraca max z 2 liczb
	int knapSack(int wt[], int val[], int n); //
	int getSize();
};

