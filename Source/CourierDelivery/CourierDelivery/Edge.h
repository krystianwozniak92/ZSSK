#pragma once

class Edge
{
public:

	// Wierzcho³ki
	int vertexA;
	int vertexB;

	// Konstruktor
	Edge();

	// Konstruktor
	Edge(int, int);

	// Destruktor
	~Edge(void);

	// Operator porównania
	friend bool operator==(const Edge&, const Edge&);
};

