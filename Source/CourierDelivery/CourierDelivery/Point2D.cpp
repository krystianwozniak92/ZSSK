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

std::string Point2D::toString() const
{
	std::string result = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	return result;
}

int Point2D::operator<(const Point2D &rhs) const
{
	if (this->x == rhs.x && this->y < rhs.y) return 1;
	if (this->x < rhs.x) return 1;
	return 0;
}
int Point2D::operator==(const Point2D &rhs) const
{
	if (this->x != rhs.x) return 0;
	if (this->y != rhs.y) return 0;
	return 1;
}
Point2D& Point2D::operator=(const Point2D &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;

	return *this;
}

std::ostream &operator<<(std::ostream &output, const Point2D &p2d)
{
	output << p2d.toString();
	return output;
}