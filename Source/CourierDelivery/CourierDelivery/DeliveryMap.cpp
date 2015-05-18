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

std::string DeliveryMap::getContent()
{
	std::string result = "{";

	if (this->points->size() > 0)
	{
		for (int i = 0; i < this->points->size(); i++)
		{
			this->points[i];
		}
	}

	result += "}";
	return result;
}