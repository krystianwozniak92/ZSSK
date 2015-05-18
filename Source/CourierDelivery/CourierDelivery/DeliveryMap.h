#pragma once
#include <vector>
#include "WeightPoint.h"
#include <string>
class DeliveryMap
{
	// Mapa punktow. Z kazdym punktem skojarzona jest paczka o okreslonej wadze.
	std::vector<WeightPoint>* points;
public:
	DeliveryMap();
	~DeliveryMap();

	void addPoint(WeightPoint);
	std::string toString();
};

