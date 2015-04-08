#include "../reader_graph.h"
#include "../utils.h"

using namespace smm;

int main()
{
	GraphReader<int> graph_reader;

	graph_reader.open("./graph.data");	

	//test copy
	Graph<int> g(graph_reader.get_instance());

	//test assignment
	Graph<int> g1 = g;

	print_graph(g);
	print_graph(g1);

	return 0;
}
