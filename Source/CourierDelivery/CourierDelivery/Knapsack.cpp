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

int Knapsack::knapSack(int wt[], int val[], int n)
{
	int i, w;

	int **K = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
		K[i] = new int[rozmiar + 1];


	// Build table K[][] in bottom up manner
	for (i = 0; i <= n; i++)
	{
		for (w = 0; w <= rozmiar; w++)
		{
			if (i == 0 || w == 0)
				K[i][w] = 0;
			else if (wt[i - 1] <= w)
				K[i][w] = max_(K[i - 1][w - wt[i - 1]] + val[i - 1], K[i - 1][w]);
			else
				K[i][w] = K[i - 1][w];
		}
	}

	return K[n][rozmiar];
}
