#ifndef EIGEN_CENTRAL_H
#define EIGEN_CENTRAL_H

#include "../include/base/graph.h"
//#include "../include/Eigen/Dense"
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <iostream>

namespace msd {
	namespace centrality {
		using base::Graph;

/*		template <typename T>
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
*/
		/*
		 * test
		 */
		template <typename T>
			void eigen_centrality(Graph<T>& graph, std::map<T,double>& result)
			{
				size_t vertex_num = graph.size();
				double *matrix = new double[vertex_num * vertex_num];
				for (typename Graph<T>::size_type i = 0; i<vertex_num; ++i) {
					std::vector<T>& vertex = graph.get_vertex_id(i);
					for (size_t j=0; j < vertex.size(); ++j) {
						size_t v = vertex[j];
						matrix[ i*vertex_num +v]=1;
					}
				}

				double *eigen = new double[vertex_num];
				double *vec = new double[vertex_num];
				double *new_vec = new double[vertex_num];
				double norm = 0;
				double eps = 0.000001;
				double lamda = 0;
			
				for (int pos = 0; pos<vertex_num; ++pos) {
					for (int i = 0; i<vertex_num; ++i) {
						vec[i] = 0;
					}
					vec[pos] = 1;	
					double delta = 1;	
					int iter = 0;
					while (delta > eps) {
						//calculate new vec
						for(int i = 0; i<vertex_num; ++i) {
							new_vec[i]=0;
							for(int j = 0; j<vertex_num; ++j) {
								new_vec[i] += matrix[j*vertex_num +i]*vec[j];
							}
						}
						//normalize new vec
						norm=0;
						for (int i = 0; i<vertex_num; ++i) {
							norm += new_vec[i]*new_vec[i];
						}
						norm = pow(norm,0.5);
						for (int i = 0; i<vertex_num; ++i) {
							new_vec[i] /= norm;
						}
						//calculate delta and update vec
						delta = 0;
						for (int i = 0; i<vertex_num; ++i) {
							delta += fabs(new_vec[i]-vec[i]);
							vec[i] = new_vec[i];
						}
					}
					if (norm > lamda) {
						lamda = norm;
						for(int i = 0; i<vertex_num; ++i) {
							eigen[i] = vec[i];
						}
					}
				}
				for (int i = 0; i<vertex_num; ++i) {
					T name = graph.get_vertex_name(i);
					result[name] = eigen[i];
				}
				delete []eigen;
				delete []vec;
				delete []new_vec;
				delete []matrix;
			}

	}//centrality
}//msd

#endif 
//another update test