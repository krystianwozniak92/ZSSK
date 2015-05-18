#pragma once
#include <map>
#include "Point2D.h"
#include <string>
class DeliveryMap
{
	// Mapa punktow. Z kazdym punktem skojarzona jest paczka o okreslonej wadze.
	std::map<Point2D, int>* pointWeightMap;
public:
	DeliveryMap();
	~DeliveryMap();

	void addPoint(Point2D, int weight);
	std::string getContent();
};

