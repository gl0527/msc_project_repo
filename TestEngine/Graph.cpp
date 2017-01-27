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


	void Graph::addNode(const Node& v)
	{
		if (adjList.find(v) == adjList.end())
		{
			Neighbors s;
			adjList[v] = s;
		}
	}


	void Graph::addEdge(const Node& v, const Node& u, int w)
	{
		if (adjList.find(v) == adjList.end())
		{
			Neighbors s;
			s.insert(std::pair<Node, int>(u, w));
			adjList[v] = s;
			if (!directed)
				addEdge(u, v, w);
		}
		else
		{
			Neighbor pair(u, w);
			if (adjList[v].find(pair) == adjList[v].end())
			{
				adjList[v].insert(pair);
				if (!directed)
					addEdge(u, v, w);
			}
		}
	}


}
