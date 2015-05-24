#include "KnapsackDynamic.h"
#include "Knapsack.h"
KnapsackDynamic::KnapsackDynamic()
{
	//maxWartosc_ = 0;
}
KnapsackDynamic::KnapsackDynamic(Knapsack* knapsack)
{
	poziom_ = 0;
	wartosc_ = 0;
	maxWartosc_ = 0;
	waga_ = 0;
	bound_ = 0;
	wynik_ = 0;

}
KnapsackDynamic::~KnapsackDynamic()
{
}

int KnapsackDynamic::knapSack(int wt[], int val[], int n, Knapsack* k)
{
	int i, w;

	int **K = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
		K[i] = new int[k->getSize() + 1];


	// Build table K[][] in bottom up manner
	for (i = 0; i <= n; i++)
	{
		for (w = 0; w <= k->getSize(); w++)
		{
			if (i == 0 || w == 0)
				K[i][w] = 0;
			else if (wt[i - 1] <= w)
				K[i][w] = k->max_(K[i - 1][w - wt[i - 1]] + val[i - 1], K[i - 1][w]);
			else
				K[i][w] = K[i - 1][w];
		}
	}

	return K[n][k->getSize()];
}