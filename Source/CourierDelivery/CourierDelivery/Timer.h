#pragma once

#include <windows.h>

typedef struct
{
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
}
stopWatch;

class Timer
{

private:
	stopWatch timer;
	LARGE_INTEGER frequency;

public:
	// Konstruktor
	Timer();

	// Rozpocznij odmierzanie
	void startTimer();

	// Zako�cz odmierzanie
	void stopTimer();

	// Zwr�� czas
	double getElapsedTime();
};

