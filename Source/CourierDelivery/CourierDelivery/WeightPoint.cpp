#include "WeightPoint.h"

WeightPoint::WeightPoint(Point2D p2d, int weight)
{
	this->p2d = p2d;
	this->weight = weight;
}

void WeightPoint::set(Point2D p2d, int weight)
{
	this->p2d = p2d;
	this->weight = weight;
}
int WeightPoint::getWeight()
{
	return this->weight;
}
Point2D WeightPoint::getPoint2D()
{
	return this->p2d;
}

WeightPoint::~WeightPoint()
{
}