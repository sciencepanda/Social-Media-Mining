#include "reader_graph.h"

using namespace msd::base;

int main()
{
	GraphReader<int> graph_reader;

	graph_reader.open("./graph.data");	

	Graph<int> g = graph_reader.get_graph();

	g.print_graph();

	return 0;
}
