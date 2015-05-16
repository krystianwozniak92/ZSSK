#include <iostream>
#include "Salesman.h"
#include "SalesmanAnnealing.h"
#include "SalesmanTabuSearch.h"
using namespace std;

int main()
{
	Salesman* salesman = new Salesman(5);
	double lambda = 0.999;
	int iterations = 1000;
	SalesmanAnnealing* sAnnealing = new SalesmanAnnealing(salesman, lambda);
	SalesmanTabuSearch* sTabuSearch = new SalesmanTabuSearch(salesman, iterations);

	sAnnealing->start();
	sTabuSearch->start();

	vector<int>*  resultSalesAnnealing = sAnnealing->GetResult();
	vector<int>*  resultSalesTabu = sTabuSearch->GetResult();

	system("pause");
	return 0;
}