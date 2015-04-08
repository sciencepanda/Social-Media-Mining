#include <iostream>
#include <cstdlib>
#include "../include/base/reader_graph.h"
//#include "./eigen.h"
#include "./degree.h"
#include "./betweeness.h"
#include "./closeness.h"
#include "./katz.h"

using namespace msd::base;
using namespace msd::centrality;

int main(int argv, char *argc[])
{
	GraphReader<int> graph_reader;

	graph_reader.open("./graph.data");

	Graph<int> graph = graph_reader.get_graph();

	graph.print_graph();

	std::map<int, double> res;

	degree_centrality<int>(graph, res);

	for (std::map<int, double>::iterator it = res.begin(); it != res.end(); ++it) {
		std::cout << "tag : " << it->first << std::endl;
		std::cout << "degree centrality : " << it->second << std::endl;
	}	

	res.clear();

//	eigen_centrality<int>(graph, res);
//
//	for (std::map<int, double>::iterator it = res.begin(); it != res.end(); ++it) {
//		std::cout << "tag : " << it->first << std::endl;
//		std::cout << "eigen centrality : " << it->second << std::endl;
//	}	
	
//	int from = 2;
//	std::set<int> nodes;
//	std::map<int, std::vector<int> > paths;
//   	std::map<int, double> dist;
//	std::map<int, double> sigma;
//
//	graph.single_source_dijkstra_full(from, nodes, paths, dist, sigma);
//
//	for (std::set<int>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
//		std::cout << "tag : " << *it << std::endl;
//	}
//
//	res.clear();
//
	betweeness_centrality<int>(graph, res);
	for (std::map<int, double>::iterator it = res.begin(); it != res.end(); ++it) {
		std::cout << "tag : " << it->first << std::endl;
		std::cout << "betweeness centrality : " << it->second << std::endl;
	}

	res.clear();
	closeness_centrality<int>(graph, res);
	for (std::map<int, double>::iterator it = res.begin(); it != res.end(); ++it) {
		std::cout << "tag : " << it->first << std::endl;
		std::cout << "closeness centrality : " << it->second << std::endl;
	}

	res.clear();
	katz_centrality<int>(graph, res, 0.25f, 0.2f, 0.01f);
	for (std::map<int, double>::iterator it = res.begin(); it != res.end(); ++it) {
		std::cout << "tag : " << it->first << std::endl;
		std::cout << "katz centrality : " << it->second << std::endl;
	}

	res.clear();
	pagerank_centrality<int>(graph, res, 0.95f, 0.1f, 0.001f);
	for (std::map<int, double>::iterator it = res.begin(); it != res.end(); ++it) {
		std::cout << "tag : " << it->first << std::endl;
		std::cout << "pagerank centrality : " << it->second << std::endl;
	}

	return 0;
}
