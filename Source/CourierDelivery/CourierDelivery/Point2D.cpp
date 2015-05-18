#include "Point2D.h"


Point2D::Point2D(int x, int y)
{
	this->x = x;
	this->y = y;
}


Point2D::~Point2D()
{
}

void Point2D::setPosX(int x)
{
	this->x = x;
}
void Point2D::setPosY(int y)
{
	this->y = y;
}

int Point2D::getPosX()
{
	return this->x;
}
int Point2D::getPosY()
{
	return this->y;
}

std::string Point2D::toString()
{
	std::string result = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	return result;
}