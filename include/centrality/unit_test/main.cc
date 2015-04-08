#include <iostream>
#include <cstdlib>
#include "../../base/utils.h"
#include "../../base/reader_graph.h"
#include "../degree.h"
#include "../betweeness.h"
#include "../closeness.h"
#include "../katz.h"

using namespace smm;

int main(int argv, char *argc[])
{
	GraphReader<int> graph_reader;

	graph_reader.open("./graph.data");

	Graph<int> graph = graph_reader.get_instance();

	print_graph(graph);

	std::vector<double> res(graph.size());

	degree_centrality(graph, res);

	for (std::size_t i = 0; i < res.size(); ++i) {
		std::cout << "id : " << i << std::endl;
		std::cout << "tag : " << graph.get_vertex_name(i) << std::endl;
		std::cout << "degree centrality : " << res[i] << std::endl;
	}	
	std::cout<<std::endl;
	res.clear();

	res.resize(graph.size(), 0);
	betweeness_centrality(graph, res);
	for (std::size_t i = 0; i < res.size(); ++i) {
		std::cout << "id : " << i << std::endl;
		std::cout << "tag : " << graph.get_vertex_name(i) << std::endl;
		std::cout << "betweeness centrality : " << res[i] << std::endl;
	}	
	std::cout<<std::endl;

	closeness_centrality(graph, res);
	for (std::size_t i = 0; i < res.size(); ++i) {
		std::cout << "id : " << i << std::endl;
		std::cout << "tag : " << graph.get_vertex_name(i) << std::endl;
		std::cout << "closeness centrality : " << res[i] << std::endl;
	}	
	std::cout<<std::endl;

	katz_centrality(graph, res, 0.25f, 0.2f, 0.01f);
	for (std::size_t i = 0; i < res.size(); ++i) {
		std::cout << "id : " << i << std::endl;
		std::cout << "tag : " << graph.get_vertex_name(i) << std::endl;
		std::cout << "katz centrality : " << res[i] << std::endl;
	}	
	std::cout<<std::endl;

	pagerank_centrality(graph, res, 0.95f, 0.1f, 0.001f);
	for (std::size_t i = 0; i < res.size(); ++i) {
		std::cout << "id : " << i << std::endl;
		std::cout << "tag : " << graph.get_vertex_name(i) << std::endl;
		std::cout << "pagerank centrality : " << res[i] << std::endl;
	}	
	std::cout<<std::endl;

	return 0;
}
