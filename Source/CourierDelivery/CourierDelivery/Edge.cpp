#include "Edge.h"

// Konstruktor
Edge::Edge()
{
	this->vertexA = 0;
	this->vertexB = 0;
}

// Konstruktor
Edge::Edge(int vertexA, int vertexB)
{
	this->vertexA = vertexA;
	this->vertexB = vertexB;
}

// Destruktor
Edge::~Edge(void)
{
	vertexA = 0;
	vertexB = 0;
}

// Operator porównania
bool operator==(const Edge& rhs, const Edge& lhs)
{
	return ((lhs.vertexA == rhs.vertexA) && (lhs.vertexB == rhs.vertexB));
}
