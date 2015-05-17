#include "Timer.h"

// Konstruktor
Timer::Timer()
{
	timer.start.QuadPart = 0;
	timer.stop.QuadPart = 0;
	QueryPerformanceFrequency(&frequency);
}

// Rozpocznij odmierzanie
void Timer::startTimer()
{
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&timer.start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
}

// Zako�cz odmierzanie
void Timer::stopTimer()
{
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&timer.stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
}

// Zwr�� czas
double Timer::getElapsedTime()
{
	LARGE_INTEGER time;
	time.QuadPart = timer.stop.QuadPart - timer.start.QuadPart;

	return ((double)time.QuadPart / (double)frequency.QuadPart);
}