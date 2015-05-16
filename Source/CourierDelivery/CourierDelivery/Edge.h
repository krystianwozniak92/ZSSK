#pragma once

class Edge
{
public:

	// Wierzcho�ki
	int vertexA;
	int vertexB;

	// Konstruktor
	Edge();

	// Konstruktor
	Edge(int, int);

	// Destruktor
	~Edge(void);

	// Operator por�wnania
	friend bool operator==(const Edge&, const Edge&);
};

