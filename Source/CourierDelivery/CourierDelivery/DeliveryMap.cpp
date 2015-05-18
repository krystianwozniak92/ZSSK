#include "DeliveryMap.h"


DeliveryMap::DeliveryMap()
{
	this->pointWeightMap = nullptr;
}


DeliveryMap::~DeliveryMap()
{
	if (this->pointWeightMap != nullptr)
		delete pointWeightMap;
}

void DeliveryMap::addPoint(Point2D point, int weight)
{
	if (this->pointWeightMap == nullptr)
		this->pointWeightMap = new std::map<Point2D, int>();
	else
	{
		(*pointWeightMap).insert(std::pair<Point2D, int>(point, weight));
	}
}

std::string DeliveryMap::getContent()
{
	std::string result = "{";

	if (this->pointWeightMap->size() > 0)
	{
		for (int i = 0; i < this->pointWeightMap->size(); i++)
		{
			(*pointWeightMap);
		}
	}

	result += "}";
	return result;
}