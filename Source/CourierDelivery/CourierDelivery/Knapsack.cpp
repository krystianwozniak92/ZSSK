#include "Knapsack.h"

Knapsack::Knapsack()
{
}

Knapsack::Knapsack(int rozmiar_)
{
	rozmiar = rozmiar_;
}
Knapsack::~Knapsack()
{
}

int Knapsack::max_(int a, int b)
{
	return (a > b) ? a : b;
}



int Knapsack::getSize()
{
	return rozmiar;
}