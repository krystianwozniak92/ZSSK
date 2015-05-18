#pragma once
#include <vector>
#include "WeightPoint.h"
#include <string>
class DeliveryMap
{
	// Mapa punktow. Z kazdym punktem skojarzona jest paczka o okreslonej wadze.
	std::vector<WeightPoint>* points;
public:
	static enum SquareType
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	DeliveryMap();
	~DeliveryMap();

	void addPoint(WeightPoint);
	std::vector<WeightPoint>* getSquare(enum SquareType);
	std::string toString();

	
};

