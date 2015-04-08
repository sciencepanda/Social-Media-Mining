#ifndef EIGEN_CENTRAL_H
#define EIGEN_CENTRAL_H

#include "../include/base/graph.h"
#include "../include/Eigen/Dense"

namespace msd {
	namespace centrality {
		using base::Graph;

		template <typename T>
			void graph_to_matrix(Graph<T>& graph, Eigen::MatrixXd& matrix)
			{
				for (typename Graph<T>::size_type i = 0; i < graph.size(); ++i) {
					std::vector<T>& vertex = graph.get_vertex_id(i);//TODO:struct vertex
					for (size_t j = 0; j < vertex.size(); ++j) {
						size_t v = vertex[j];
						matrix(i, v) = 1;
					}
				}
			}
		
		template <typename T>
			void eigen_centrality(Graph<T>& graph, std::map<T, double>& result)
			{
				Eigen::MatrixXd matrix(graph.size(), graph.size());
				graph_to_matrix<T>(graph, matrix);

				Eigen::EigenSolver<Eigen::MatrixXd> es(matrix);
				Eigen::VectorXcd v = es.eigenvectors().col(graph.size() - 1);
				
				for (size_t i = 0; i < v.rows(); ++i) {
					T name = graph.get_vertex_name(i);
					result[name] = v[i].real();
				}
				//copy back
			}
	}
}//msd

#endif 
