#include "reader_graph.h"

using namespace msd::base;

int main()
{
	GraphReader<int> graph_reader;

	graph_reader.open("./graph.data");	

	Graph<int> g(graph_reader.get_instance());

	Graph<int> g1 = g;

	g.print_graph();

	return 0;
}
