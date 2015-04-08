#include "../graph.h"
#include "../utils.h"

using namespace smm;

void test_star()
{
	Graph<int> graph;

	graph.add_edge(1, 2);
	graph.add_edge(1, 3);
	graph.add_edge(1, 4);
	graph.add_edge(1, 5);
	graph.add_edge(1, 6);
	graph.add_edge(1, 7);

	print_graph(graph);
}

void test_random()
{
	Graph<int> graph;

	graph.add_edge(1, 2);
	graph.add_edge(5, 3);
	graph.add_edge(8, 4);
	graph.add_edge(10, 5);
	graph.add_edge(1, 8);
	graph.add_edge(7, 9);

	print_graph(graph);
}

void test_type()
{
	Graph<double> graph;

	graph.add_edge(1.1f, 2.1f);
	graph.add_edge(5.0f, 3.0f);
	graph.add_edge(8.0f, 4.0f);
	graph.add_edge(10.0f, 5.0f);
	graph.add_edge(1.0f, 8.0f);
	graph.add_edge(7.0f, 9.0f);

	print_graph(graph);
}

int main()
{
	//test graph structure
	test_star();

	test_random();

	test_type();

	//TODO: test every function

	return 0;
}
