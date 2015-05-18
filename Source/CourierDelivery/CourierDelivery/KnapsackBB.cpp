#include "KnapsackBB.h"
#include "Knapsack.h"
KnapsackBB::KnapsackBB()
{
}
KnapsackBB::KnapsackBB(Knapsack* knapsack)
{
	poziom_ = 0;
	wartosc_ = 0;
	maxWartosc_ = 0;
	waga_ = 0;
	bound_ = 0;
	wynik_ = 0;

}
KnapsackBB::~KnapsackBB()
{
}

int KnapsackBB::bound(KnapsackBB u, int n, int W, std::vector<int> pVa, std::vector<int> wVa)
{
	int totweight = 0;
	int j = 0, k = 0; //w celu iterowania 

	if (u.waga_ >= W) //jesli waga wezla wieksza od wagi pelcaka
	{
		return 0; //zwroc zero jako wynik bo wtedy wezel jest nieobiecujacy
	}
	else
	{
		u.wynik_ = u.wartosc_; //
		j = u.poziom_ + 1;
		totweight = u.waga_; //waga danego wezla

		while ((j < n) && (totweight + wVa[j] <= W))
		{
			totweight += wVa[j]; //zwiekszam o wage wezla 
			u.wynik_ += pVa[j]; //zwiekszam o wartosc wezla 
			j++; //iteruje dalej
		}

		k = j;

		if (k < n) //jesli k jest mniejesze od liczby przedmotow 
		{
			u.wynik_ += (W - totweight) * (pVa[k] / wVa[k]); //podstaw za wynik (W - totweight) * (pVa[k] / wVa[k])
		}
		return u.wynik_; //zwraca górn¹ granice
	}
}

int KnapsackBB::plecak(int n, int waga[], int wartosc[], int W)
{
	std::queue<KnapsackBB> kolejka; //zdefiniowanie kolejki
	KnapsackBB u, v, max;
	//Knapsack help;
	//u - potomek nizej
	// v - korzen drzewa

	kolejka.empty();

	//wyczyszczenie kolejki by z kazda iteracja byla pusta aby nie nadpisywac wartosci
	wart.clear();
	wag.clear();

	for (int i = 0; i < n; i++)
	{
		wart.push_back(wartosc[i]); //wypelniam wektor tablica wartosci 
		wag.push_back(waga[i]); //wypelniam wektor tablica wag
	}

	v.poziom_ = -1;
	v.wartosc_ = 0;
	v.waga_ = 0;

	kolejka.push(v);
	while (!kolejka.empty()) //jesli kolejka nie jest pusta
	{
		v = kolejka.front(); //wczytaj najnowszy element do korzenia
		kolejka.pop();  //usun najstarszy element w kolejce

		if (v.poziom_ == -1) //czy aktualnie sprawdzany korzen jest glownym korzeniem
			u.poziom_ = 0; //prawda to 0
		else if (v.poziom_ != (n - 1)) //w przeciwnym wypadku jesli korzen nie rowna sie liczbie elementow
			u.poziom_ = v.poziom_ + 1; //zwieksz wartosc o 1

		u.waga_ += waga[u.poziom_]; //ustawiam wage jako sume aktualnej wagi
		u.wartosc_ += wartosc[u.poziom_]; //ustawiam wartosc jako wartosc aktualnej wartosci

		u.bound_ = bound(u, n, W, wart, wag); //zwracamy górna granice wartosci rozwiazania 

		if (u.waga_ <= W && u.wartosc_ > max.maxWartosc_)
			//jesli waga przedmiotu nie przekracza wagi plecaka i jesli zysk wezla jest lepszy niz rozwiazanie
			max.maxWartosc_ = u.wartosc_; //ustaw maxWartosc jako zysk aktualnego dziecka

		if (u.bound_ > max.maxWartosc_)// jesli granica górna wiêksza od rozwiazania tzn ze wezel jest obiecujacy
			kolejka.push(u); //wstawiamy o kolejki jako kolejny wezel obiecujacy

		u.waga_ = v.waga_; //waga korzenia jako waga wezla
		u.wartosc_ = v.wartosc_; //wartosc korzenia jako wartosc wezla

		u.bound_ = bound(u, n, W, wart, wag); //zwracamy górna granice wartosci rozwiazania 

		if (u.bound_ > max.maxWartosc_) // jesli granica górna wiêksza od rozwiazania tzn ze wezel jest obiecujacy
			kolejka.push(u); //wstawiamy o kolejki jako kolejny wezel obiecujacy

	}
	return max.maxWartosc_; //zwracamy najlepsze rozwiazanie
}

