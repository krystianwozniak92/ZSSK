#pragma once
#include "Point2D.h"
#include <string>
class WeightPoint
{
	Point2D p2d;
	int weight;
public:
	WeightPoint();
	WeightPoint(Point2D, int);
	~WeightPoint();

	void set(Point2D, int);
	int getWeight();
	Point2D getPoint2D();

	std::string toString();
};

