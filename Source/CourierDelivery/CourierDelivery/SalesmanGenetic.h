/*
Klasa reprezentuje algorytm genetyczny dla problemu komiwojazera.
Zaimplementowane sa funkcje zwiazane z funkcja kosztu, mutacji, krzyzowania itp.
*/

#pragma once
#include "Salesman.h"
#include "Timer.h"
#include <algorithm>    // std::random_shuffle
#include <random>

class SalesmanGenetic
{
	// TSP
	Salesman* _salesman;

	// Wynik dzia³ania algorytmu. 
	std::vector<unsigned>* _hamCycle;

	/* -- Parametry dla algorytmu -- */
	unsigned _mutCount; // Liczba mutacji dla pojedynczego osobnika w jednej iteracji algorytmu
	unsigned _popCount; // Calkowita liczba populacji

	/* Statystyki wykonanego algorytmu */
	unsigned _iterations; // Calkowita liczba iteracji petli glownej algorytmu

	/* Funkcja zwraca populacje osobnikow o losowych cyklach hamiltona.
	pop - liczba osobnikow
	*/
	std::vector< std::vector<unsigned> >* getRandomPop(unsigned pop);

	/* Funkcja zwraca dlugosc cyklu hamiltona zachowanego w wektorze cities.
	cities - wektor reprezentujacy cykl hamiltona
	*/
	unsigned getLength(std::vector<unsigned>* cities);

	/* Funkcja zwraca dwoch najkorzystniejszych rodzicow (selekcja turniejowa)
	population - populacja osobnikow
	tourSize - rozmiar grupy turniejowej
	*/
	unsigned* SalesmanGenetic::getBestParents(std::vector< std::vector<unsigned> >* population, unsigned tourSize);

	/* Funkcja krzyzuje dwoje rodzicow i tworzy nowe potomstwo w postaci dwojki dzieci
	(Krzy¿owanie z czêœciowym odwzorowaniem (PMX) )
	parents - rodzice
	return - dwojka dzieci
	*/
	std::vector<std::vector<unsigned>>* SalesmanGenetic::crossOver(std::vector<unsigned>* p1, std::vector<unsigned>* p2);

	/* Funkcja mutuje dziecko poprzez zmiane kolejnosci poszczegolnych miast.
	children - wektor zawierajacy miasta
	count - liczba genow (miast), ktore zostana losowo pozamieniane
	*/
	void SalesmanGenetic::mutate(std::vector<unsigned>* children, unsigned count);
public:
	/*  Funkcja wykonuje algorytm i zwraca wynik w postaci wektora reprezentujacego cykl hamiltona.
	pop - liczebnosc populacji osobnikow
	mutCount - Liczba wierzcholkow zmieniajacych pozycje w procesie mutacji osobnika
	maxTime - maksymalny czas, w ktorym funkcja nie znajduje lepszego rozwiazania
	*/
	std::vector<unsigned>* SalesmanGenetic::start(unsigned pop, unsigned mutCosunt, double maxTime);

	/* Funkcja zwraca dlugosc najlepszego znalezionego cyklu hamiltona
	*/
	unsigned getBestHamCycLen();

	/* Funkcja zwraca wielkosc populacji na ktorej opieral sie algorytm
	*/
	unsigned getPopSize();

	/* Funkcja zwraca liczbe mutacji dla pojedynczego osobnika w procesie mutacji
	*/
	unsigned getMutCount();

	/* Funkcja zwraca liczbe iteracji algorytmu
	*/
	unsigned getIterCount();

	std::vector<unsigned>* GetResult();

	// Konstruktory
	SalesmanGenetic(Salesman*);
	SalesmanGenetic();

	// Destruktor
	~SalesmanGenetic();
};

