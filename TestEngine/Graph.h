#pragma once
#include "Ogre.h"

namespace Engine
{
	struct Node
	{
		std::string name;
		Ogre::Vector3 pos;
	};

	bool operator<(const Node& v1, const Node& v2) { return v1.name < v2.name; }
	
	class Graph
	{
		typedef std::pair<Node, int> Neighbor;
		typedef std::set<Neighbor> Neighbors;
		typedef std::map<Node, Neighbors> AdjacencyList;

		AdjacencyList adjList;
		const bool directed;
	public:
		Graph(bool dir);
		~Graph();

		void addNode(const Node& v);
		void addEdge(const Node& v, const Node& u, int w);
		
		bool isDirected() const { return directed; }
	};
}


