#pragma once
#include <string>
#include <iostream>
class Point2D
{
	int x;
	int y;
public:
	Point2D(int x, int y);

	void setPosX(int x);
	void setPosY(int y);

	int getPosX();
	int getPosY();

	std::string toString() const;
	~Point2D();

	int operator<(const Point2D &rhs) const;
	int operator==(const Point2D &rhs) const;
	Point2D& operator=(const Point2D &rhs);
};

