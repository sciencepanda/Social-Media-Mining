#include "../tarjan.h"
#include "../../base/utils.h"

using namespace smm;

int main()
{
	Graph<char> graph;

	graph.add_edge('a', 'b');	
	graph.add_edge('a', 'c');	
	graph.add_edge('b', 'd');	
	graph.add_edge('b', 'e');	
	graph.add_edge('c', 'e');	
	graph.add_edge('c', 'f');	
	//XXX
//	print_graph(graph);

	std::vector<std::size_t> pre(graph.size());
	std::vector<std::size_t> low(graph.size());
	std::vector<std::size_t> cut(graph.size());

	std::size_t from_id = 0;
	tarjan(graph, from_id, pre, low, cut);

	std::size_t sum_bridge = 0;
	std::size_t sum_cut = 0;

	for (std::size_t i = 0; i < pre.size(); ++i) {
		if (pre[i] == low[i] && i != from_id)
			sum_bridge++;
		sum_cut += cut[i];
	}

	std::cout << "number of bridges : " << sum_bridge << std::endl;
	std::cout << "number of cut : " << sum_cut << std::endl;

	return 0;
}
