#ifndef DEGREE_H
#define DEGREE_H
#include <map>
#include "../include/base/graph.h"

namespace msd {
	namespace centrality {
		using base::Graph;

		template <typename T>
			void degree_centrality(Graph<T>& graph, std::map<T, double>& result)
			{
				for (typename Graph<T>::size_type i = 0; i < graph.size(); ++i) {
					T name = graph.get_vertex_name(i);	
					size_t degree = graph.get_vertex(name).size();	
					result[name] = (double) degree / graph.size();
				}
			}
	}//centrality
}//msd

#endif
