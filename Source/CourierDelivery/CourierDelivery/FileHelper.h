#pragma once
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <String>

class FileHelper
{
public:
	FileHelper();
	~FileHelper();

	int gen;//(1-100)
	int gen2;//(1-10)
	int x;
	int	y; 
	int	w;
	std::ofstream file;

void RandomGenerator();

void FileReader();

};