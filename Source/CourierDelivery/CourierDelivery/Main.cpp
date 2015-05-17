#include <iostream>
#include "Salesman.h"
#include "SalesmanAnnealing.h"
#include "SalesmanTabuSearch.h"
#include "SalesmanGenetic.h"

using namespace std;

int main()
{
	Salesman* salesman = new Salesman(5);
	Timer timer = Timer();

	// Salesman PARAMETERS----------
	// Annealing
	double lambda = 0.999;
	// Tabu Search
	int iterations = 1000;
	// Genetic
	int population = 100;
	int mutationCount = 2;
	int maxTime = 3;
	// -----------------------------

	SalesmanAnnealing* sAnnealing = new SalesmanAnnealing(salesman, lambda);
	SalesmanTabuSearch* sTabuSearch = new SalesmanTabuSearch(salesman, iterations);
	SalesmanGenetic* sGenetic = new SalesmanGenetic(salesman);

	sAnnealing->start();
	sTabuSearch->start();
	sGenetic->start(population, mutationCount, maxTime);

	timer.startTimer();
	vector<int>*  resultSalesAnnealing = sAnnealing->GetResult();
	timer.stopTimer();
	cout << "Salesman Annealing time: " << timer.getElapsedTime() << endl;
	
	timer.startTimer();
	vector<int>*  resultSalesTabu = sTabuSearch->GetResult();
	timer.stopTimer();
	cout << "Salesman Tabu Search time: " << timer.getElapsedTime() << endl;

	timer.startTimer();
	vector<unsigned>*  resultSalesGenetic = sGenetic->GetResult();
	timer.stopTimer();
	cout << "Salesman Genetic time: " << timer.getElapsedTime() << endl;


	system("pause");
	return 0;
}