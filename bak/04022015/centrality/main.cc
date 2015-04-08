#include <iostream>
#include <cstdlib>
#include "../include/base/reader_graph.h"
#include "./degree.h"

using namespace msd::base;
using namespace msd::centrality;

int main(int argv, char *argc[])
{
	GraphReader<int> graph_reader;

	graph_reader.open("../../data/graph.data");

	Graph<int> graph = graph_reader.get_graph();

	graph.print_graph();

	std::map<int, double> res;

	degree_centrality<int>(graph, res);

	for (std::map<int, double>::iterator it = res.begin(); it != res.end(); ++it) {
		std::cout << "tag : " << it->first << std::endl;
		std::cout << "degree centrality : " << it->second << std::endl;
	}	

	return 0;
}
