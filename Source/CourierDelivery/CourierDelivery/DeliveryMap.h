#pragma once
#include <vector>
#include "Point2D.h"
#include <string>
class DeliveryMap
{
	// Mapa punktow. Z kazdym punktem skojarzona jest paczka o okreslonej wadze.
	std::vector<Point2D> points;
	std::vector<Point2D> 
public:
	DeliveryMap();
	~DeliveryMap();

	void addPoint(Point2D, int weight);
	std::string getContent();
};

