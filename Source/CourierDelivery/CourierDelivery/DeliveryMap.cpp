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