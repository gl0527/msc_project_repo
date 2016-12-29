#pragma once
#include "Ogre.h"

namespace Engine
{
	typedef struct Vertex
	{
		std::string name;
		Ogre::Vector3 pos;
	} Vertex;

	bool operator<(const Vertex& v1, const Vertex& v2) { return v1.name < v2.name; }

	class Graph
	{
		std::map<Vertex, std::set<std::pair<Vertex, int>>> adjList;
		const bool directed;
	public:
		Graph(bool dir);
		~Graph();

		void addVertex(const Vertex& v);
		void addEdge(const Vertex& v, const Vertex& u, int w);
		
		bool isDirected() const { return directed; }
	};
}


