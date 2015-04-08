#ifndef KATZ_H
#define KATZ_H
#include <cmath>
#include "../include/base/graph.h"

namespace msd {
	namespace centrality {
		using base::Graph;

		template<typename T>
			void pagerank_centrality(Graph<T>& graph, std::map<T, double>& result, double alpha,
					double beta, double epsilion = 0.005f)
			{
				unsigned int n_steps = 0;
				std::vector<double> r(graph.size());
				std::vector<double> pr(graph.size(), 1.0f / graph.size());
				double diff = 0.0f;

				do {
					for (typename Graph<T>::size_type i = 0; i < graph.size(); ++i) {
						std::vector<T>& vertex = graph.get_vertex_id(i);

						for (size_t j = 0; j < vertex.size(); ++j) {
							size_t to_id = vertex[j];
							r[i] += alpha * pr[to_id] / graph.get_vertex_id(to_id).size();
						}
						r[i] += beta;
					}

					diff = 0.0f;
					for (size_t i = 0; i < graph.size(); ++i) {
						diff += fabs(r[i] - pr[i]);
						pr[i] = r[i];
						r[i] = 0.0f;
					}
					std::cout << diff << std::endl;

					++n_steps;
					std::cout << n_steps << std::endl;
				}while (diff > epsilion);

				for (size_t i = 0; i < pr.size(); ++i) {
					T name = graph.get_vertex_name(i);
					result[name] = pr[i];
				}
			}

		template<typename T>
			void katz_centrality(Graph<T>& graph, std::map<T, double>& result, double alpha,
					double beta, double epsilion = 0.005f)
			{
				unsigned int n_steps = 0;
				std::vector<double> r(graph.size());
				std::vector<double> pr(graph.size(), 1.0f / graph.size());
				double diff = 0.0f;

				do {
					for (typename Graph<T>::size_type i = 0; i < graph.size(); ++i) {
						std::vector<T>& vertex = graph.get_vertex_id(i);

						for (size_t j = 0; j < vertex.size(); ++j) {
							size_t to_id = vertex[j];
							r[i] += alpha * pr[to_id];
						}
						r[i] += beta;
					}

					diff = 0.0f;
					for (size_t i = 0; i < graph.size(); ++i) {
						diff += fabs(r[i] - pr[i]);
						pr[i] = r[i];
						r[i] = 0.0f;
					}

					++n_steps;
					std::cout << n_steps << std::endl;
					std::cout << diff << std::endl;
				}while (diff > epsilion);

				for (size_t i = 0; i < pr.size(); ++i) {
					T name = graph.get_vertex_name(i);
					result[name] = pr[i];
				}
			}
	}//centrality
}//msd

#endif
