#include <iostream>
#include "Salesman.h"
#include "SalesmanAnnealing.h"
using namespace std;

int main()
{
	Salesman* salesman = new Salesman(5);
	SalesmanAnnealing* sAnnealing = new SalesmanAnnealing(salesman, 0.999);

	sAnnealing->start();
	vector<int>*  result = sAnnealing->GetResult();
	
	system("pause");
	return 0;
}