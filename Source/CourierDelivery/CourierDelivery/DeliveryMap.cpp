#include "DeliveryMap.h"


DeliveryMap::DeliveryMap()
{
	this->points = nullptr;
}


DeliveryMap::~DeliveryMap()
{
	if (this->points != nullptr)
		delete points;
}

void DeliveryMap::addPoint(WeightPoint point)
{
	if (this->points == nullptr)
		this->points = new std::vector<WeightPoint>();

	this->points->push_back(point);
}

std::string DeliveryMap::toString()
{
	std::string result = "{";

	if (this->points->size() > 0)
	{
		for (int i = 0; i < this->points->size(); i++)
		{
			result += (*points)[i].toString();
			if (i < this->points->size() - 1)
				result += " ; ";
		}
	}

	result += "}";
	return result;
}

std::vector<WeightPoint>* DeliveryMap::getSquare(enum SquareType squareType)
{
	std::vector<WeightPoint>* map = new std::vector<WeightPoint>();
	switch (squareType)
	{
		case SquareType::TopLeft:

			for (int i = 0; i < points->size(); i++)
			{
				Point2D p2d = (*points)[i].getPoint2D();
				if (p2d.getPosX() < 0 && p2d.getPosY() >= 0)
					map->push_back((*points)[i]);
			}

			break;

		case SquareType::TopRight:
			for (int i = 0; i < points->size(); i++)
			{
				Point2D p2d = (*points)[i].getPoint2D();
				if (p2d.getPosX() >= 0 && p2d.getPosY() >= 0)
					map->push_back((*points)[i]);
			}
			break;

		case SquareType::BottomLeft:

			for (int i = 0; i < points->size(); i++)
			{
				Point2D p2d = (*points)[i].getPoint2D();
				if (p2d.getPosX() < 0 && p2d.getPosY() < 0)
					map->push_back((*points)[i]);
			}

			break;

		case SquareType::BottomRight:

			for (int i = 0; i < points->size(); i++)
			{
				Point2D p2d = (*points)[i].getPoint2D();
				if (p2d.getPosX() >= 0 && p2d.getPosY() < 0)
					map->push_back((*points)[i]);
			}

			break;
	}
	return map;
}
