#include <iostream>
#include "graph.h"

using namespace msd::base; 

void test_star()
{
	Graph<int> graph;

	graph.push_back(1, 2);
	graph.push_back(1, 3);
	graph.push_back(1, 4);
	graph.push_back(1, 5);
	graph.push_back(1, 6);
	graph.push_back(1, 7);

	graph.print_graph();
}

void test_random()
{
	Graph<int> graph;

	graph.push_back(1, 2);
	graph.push_back(5, 3);
	graph.push_back(8, 4);
	graph.push_back(10, 5);
	graph.push_back(1, 8);
	graph.push_back(7, 9);

	graph.print_graph();
}

void test_type()
{
	Graph<double> graph;

	graph.push_back(1.1f, 2.1f);
	graph.push_back(5.0f, 3.0f);
	graph.push_back(8.0f, 4.0f);
	graph.push_back(10.0f, 5.0f);
	graph.push_back(1.0f, 8.0f);
	graph.push_back(7.0f, 9.0f);

	graph.print_graph();
}

int main()
{
	test_star();

	test_random();

	test_type();

	return 0;
}
