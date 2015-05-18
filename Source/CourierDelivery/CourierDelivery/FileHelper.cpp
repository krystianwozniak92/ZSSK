#include "FileHelper.h"

FileHelper::FileHelper(){}

FileHelper::~FileHelper(){}

void FileHelper::RandomGenerator()
{
	gen = 100;
	gen2 = 10;
	std::string path = "map1";
	this->file.open( "Maps/" + path + ".txt");

	srand(time(NULL));
	for(int i = 0; i < 100; ++i) //courier num1
	{
		this->x = rand()%gen - gen;
		this->y = rand()%gen + 1;
		this->w = rand()%gen2 + 1;
		this->file << x << " " << y << " " << w << std::endl;
	}
	for(int j = 0; j < 100; ++j) //courier num2
	{
		this->x = rand()%gen + 1;
		this->y = rand()%gen + 1;
		this->w = rand()%gen2 + 1;
		this->file << x << " " << y << " " << w << std::endl;
	}
	for(int k = 0; k < 100; ++k) //courier num3
	{
		this->x = rand()%gen + 1;
		this->y = rand()%gen - gen;
		this->w = rand()%gen2 + 1;
		this->file << x << " " << y << " " << w << std::endl;
	}
	for(int l = 0; l < 100; ++l) //courier num4
	{
		this->x = rand()%gen - gen;
		this->y = rand()%gen - gen;
		this->w = rand()%gen2 + 1;
		this->file << x << " " << y << " " << w << std::endl;
	}
	this->file.close();
}

void FileHelper::FileReader()
{
	std::string path = "map1";
	this->file.open( "Mapy/" + path + ".txt");

	this->file.close();
}