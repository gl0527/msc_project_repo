#include "Graph.h"

namespace Engine
{
	Graph::Graph(bool dir)
		: directed(dir)
	{
		
	}

	
	Graph::~Graph()
	{
	}


	void Graph::addVertex(const Vertex& v)
	{
		if (adjList.find(v) == adjList.end())
		{
			std::set<std::pair<Vertex, int>> s;
			adjList[v] = s;
		}
	}


	void Graph::addEdge(const Vertex& v, const Vertex& u, int w)
	{
		if (adjList.find(v) == adjList.end())
		{
			std::set<std::pair<Vertex, int>> s;
			s.insert(std::pair<Vertex, int>(u, w));
			adjList[v] = s;
			if (!directed)
				addEdge(u, v, w);
		}
		else
		{
			std::pair<Vertex, int> pair(u, w);
			if (adjList[v].find(pair) == adjList[v].end())
			{
				adjList[v].insert(pair);
				if (!directed)
					addEdge(u, v, w);
			}
		}
	}


}
