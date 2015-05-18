#include <iostream>
#include "Salesman.h"
#include "SalesmanAnnealing.h"
#include "SalesmanTabuSearch.h"
#include "SalesmanGenetic.h"
#include <string>
#include "Point2D.h"
#include "DeliveryMap.h"
using namespace std;

// Function declarations----------------------
template < class T >
string GetVectorContent(vector<T>* vector);
//--------------------------------------------


int main()
{
	Salesman* salesman = new Salesman(5);
	Timer timer = Timer();

	// Salesman PARAMETERS---------------------
	// Annealing
	double lambda = 0.999;
	// Tabu Search
	int iterations = 1000;
	// Genetic
	int population = 100;
	int mutationCount = 2;
	int maxTime = 3;
	//-----------------------------------------

	SalesmanAnnealing* sAnnealing = new SalesmanAnnealing(salesman, lambda);
	SalesmanTabuSearch* sTabuSearch = new SalesmanTabuSearch(salesman, iterations);
	SalesmanGenetic* sGenetic = new SalesmanGenetic(salesman);

	// Start Salesman algorithms---------------
	// Measure the execution time of algorithms
	// Get best cycle (results)
	timer.startTimer();
	sAnnealing->start();
	timer.stopTimer();
	double timeSalesAnnealing = timer.getElapsedTime();
	vector<int>*  resultSalesAnnealing = sAnnealing->GetResult();

	timer.startTimer();
	sTabuSearch->start();
	timer.stopTimer();
	double timeSalesTabu = timer.getElapsedTime();
	vector<int>*  resultSalesTabu = sTabuSearch->GetResult();

	timer.startTimer();
	sGenetic->start(population, mutationCount, maxTime);
	timer.stopTimer();
	double timeSalesGenetic = timer.getElapsedTime();
	vector<unsigned>*  resultSalesGenetic = sGenetic->GetResult();
	//-----------------------------------------

	// Send result to the default output-------
	cout << "Salesman Annealing:\n";
	cout << "Best cycle: " << GetVectorContent<int>(resultSalesAnnealing) << endl;
	cout << "time: " << timeSalesAnnealing << endl;

	cout << "Salesman Tabu Search:\n";
	cout << "Best cycle: " << GetVectorContent<int>(resultSalesTabu) << endl;
	cout << "time: " << timeSalesAnnealing << endl;

	cout << "Salesman Genetic:\n";
	cout << "Best cycle: " << GetVectorContent<unsigned>(resultSalesGenetic) << endl;
	cout << "time: " << timeSalesAnnealing << endl;
	//-----------------------------------------

	//TESTS------------------------------------------------------------------------

	// Point2D
	Point2D p2d = Point2D(-3, 5);
	cout << "Point2D: " << p2d.toString() << endl;
	
	

	// DeliveryMap
	DeliveryMap deMap = DeliveryMap();
	deMap.addPoint(Point2D(-3, 5), 5);
	deMap.addPoint(Point2D(-2, 5), 9);
	deMap.getContent();
	system("pause");
	return 0;
}

// Function definitions------------------------
template < class T >
string GetVectorContent(vector<T>* vector)
{
	string result = "[";

	for (unsigned i = 0; i < vector->size(); i++)
	{
		result += to_string((*vector)[i]);
		if (i < vector->size() - 1)
			result += ", ";
	}

	result += "]";
	return result;
}

//----------------------------------------------