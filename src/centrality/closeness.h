#ifndef CLOSENESS_H
#define CLOSENESS_H
#include "../include/base/graph.h"

namespace msd {
	namespace centrality {
		using base::Graph;

		template <typename T>
			void closeness_centrality(Graph<T>& graph, std::map<T, double>& result)
			{
				for (typename Graph<T>::size_type i = 0; i < graph.size(); ++i) {
					T from = graph.get_vertex_name(i);	

					std::stack<T> nodes;
					std::map<T, std::vector<T> > paths;
					std::map<T, double> dist;
					std::map<T, double> sigma;

					graph.single_source_dijkstra_full(from, nodes, paths, dist, sigma);
					
					double sum = 0.0f;
					for (typename std::map<T, double>::iterator it = dist.begin(); it != dist.end(); ++it) {
						sum += it->second;
					}		

					double scale = 1.0f / (graph.size() - 1);
					result[from] = 1 / (sum * scale);
				}
				
			}
	}//centrality
}//msd

#endif
