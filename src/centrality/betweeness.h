#ifndef BETWEENESS_H
#define BETWEENESS_H
#include "../include/base/graph.h"

namespace msd {
	namespace centrality {
		using base::Graph;

		template <typename T>
			void betweeness_centrality(Graph<T>& graph, std::map<T, double>& result)
			{
				for (typename Graph<T>::size_type i = 0; i < graph.size(); ++i) {
					T from = graph.get_vertex_name(i);	

					std::stack<T> nodes;
					std::map<T, std::vector<T> > paths;
					std::map<T, double> dist;
					std::map<T, double> sigma;

					graph.single_source_dijkstra_full(from, nodes, paths, dist, sigma);

//					std::cout<< "from " << from <<std::endl;
//					for (typename std::map<T, double>::iterator it = dist.begin(); it != dist.end(); ++it) {
//						std::cout<< "to : " << it->first << " dist : " << it->second << std::endl;
//					}

					//accumulate
					std::map<T, double> delta;
					while (!nodes.empty()) {
						T u = nodes.top();
						nodes.pop();

						double coeff = (1.0f + delta[u]) / sigma[u];
//						std::cout << "from " << from << std::endl;
//						std::cout << "sigma " << sigma[u] << std::endl;
//						std::cout << "delta " << delta[u] << std::endl;
//
						for (size_t i = 0; i < paths[u].size(); ++i) {
							T v = paths[u][i];
//							std::cout << "prev " << v << std::endl;
							delta[v] += sigma[v] * coeff;
						}
						
//						std::cout<<std::endl;
						if (u != from) {
							result[u] += delta[u];
						}
					}
				}

				if (result.size() <= 2)
					return;

				double scale = 1.0f / ((graph.size() - 1) * (graph.size() - 2));
//				std::cout << "scale " << scale << std::endl;
				std::map<T, double> new_res;
				for (typename std::map<T, double>::iterator it = result.begin(); it != result.end(); ++it) {
//					std::cout << "central " << it->second << std::endl;
					new_res[it->first] = scale * it->second;		
				}

				result = new_res;
			}

	}//centrality
}//msd

#endif
