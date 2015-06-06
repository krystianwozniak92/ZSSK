#pragma once
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <String>
#include "DeliveryMap.h"

class FileHelper
{
public:
	FileHelper();
	~FileHelper();

	int gen; //(1-100)
	int gen2; //(1-10)
	int x;
	int	y;
	int	w;
	std::fstream file;

	void RandomGenerator();

	DeliveryMap* FileReader();

};