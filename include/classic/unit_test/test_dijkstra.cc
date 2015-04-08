#include "../../base/reader_graph.h"
#include "../dijkstra.h"

using namespace smm;

int main()
{
	GraphReader<int> graph_reader;

	graph_reader.open("./graph.data");

	Graph<int> graph = graph_reader.get_instance();

	std::size_t from = 2;
	std::stack<size_t> nodes;
	std::map<size_t, std::vector<size_t> > paths;
   	std::map<size_t, double> dist;
	std::map<size_t, double> sigma;

	single_source_dijkstra_full(graph, from, nodes, paths, dist, sigma);

	for (std::map<size_t, double>::iterator it = dist.begin(); it != dist.end(); ++it) {
		std::cout << "id : " << it->first << std::endl;
		std::cout << "dist : " << it->second << std::endl;
	}

	return 0;
}
