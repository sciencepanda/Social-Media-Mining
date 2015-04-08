#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <iostream>

namespace msd {
	namespace base {
		/*
		 * to implement a iterator, 
		 * a vertex struct
		 */
		template <typename T> 
			class Graph {
				public:
					typedef std::size_t size_type;

					Graph<T>() : _m_is_directed(false), _m_is_weighted(false) {};

					Graph<T>(bool is_directed, bool is_weighted) : 
						_m_is_directed(is_directed), _m_is_weighted(is_weighted) {};

					Graph<T>(size_type size, bool is_directed, bool is_weighted) : 
						_m_graph(size), _m_is_directed(is_directed), _m_is_weighted(is_weighted) {};

					size_type size() const
					{
						return _m_graph.size();
					}

					T get_vertex_name(size_type index) 
					{
						return _m_id_to_T[index];
					}

					//clear values, not for memory
					void clear();

					//reallocating memory
					void reallocate();

					//default case: undirect graph
					inline void push_back(const T& from, const T& to);

					inline std::vector<T>& get_vertex(const T& index);

					//FIXME: adjust method name
					inline std::vector<T>& get_vertex_id(size_type index);

					void print_graph() const;

					void print_graph();

					//algorithms
					//FIXME: judge whether to use a T or size_type?
					void single_source_dijkstra_full(T from, std::stack<T>& nodes, 
							std::map<T, std::vector<T> >& paths, std::map<T, double>& dist,
							std::map<T, double>& sigma);

				private:
					struct heap_node_t {
						size_type node_id;
						size_type prev_id;
						double dist;

						heap_node_t() {};

						heap_node_t(size_type _node_id, size_type _prev_id, double _dist) : 
							node_id(_node_id), prev_id(_prev_id), dist(_dist) {};

						bool operator < (const struct heap_node_t& node) const 
						{
							return this->dist > node.dist;
						}	
					};

				private:
					//internal function
					void copy_T_set(std::set<size_type>& input, std::set<T>& output);

					void copy_T_map(std::map<size_type, double>& input, 
							std::map<T, double>& output);

					void copy_T_path(std::map<size_type, std::vector<size_type> >& input, 
							std::map<T, std::vector<T> >& output);

				private:
					//the map functions can be implemented by hash_map in c++11. 
					//id start from 0
					bool _m_is_directed;
					bool _m_is_weighted;
					//TODO: hashmap implement
					//for weighted graph, not implemented yet
					std::map<std::pair<size_type, size_type>, double> _m_weight;
					std::map<T, size_type> _m_T_to_id;
					std::map<size_type, T> _m_id_to_T;
					std::vector<std::vector<T> > _m_graph;
			};

		template <typename T>
			void Graph<T>::clear()
			{
				for (size_type i = 0; i < _m_graph.size(); ++i) {
					_m_graph[i].clear();
				}

				_m_weight.clear();
				_m_T_to_id.clear();
				_m_id_to_T.clear();
			}

		template <typename T>
			void Graph<T>::reallocate()
			{
				std::map<std::pair<size_type, size_type>, double>().swap(_m_weight);
				std::map<T, size_type>().swap(_m_T_to_id);
				std::map<size_type, T>().swap(_m_id_to_T);
				std::vector<std::vector<T> >().swap(_m_graph);
			}

		template <typename T>
			inline void Graph<T>::push_back(const T& from, const T& to)
			{
				size_type from_id, to_id;

				if (_m_T_to_id.find(from) == _m_T_to_id.end()) {
					_m_graph.resize(_m_graph.size() + 1);
					_m_T_to_id[from] = _m_graph.size() - 1;
					_m_id_to_T[_m_graph.size() - 1] = from;
				}
				from_id = _m_T_to_id[from];

				if (_m_T_to_id.find(to) == _m_T_to_id.end()) {
					_m_graph.resize(_m_graph.size() + 1);
					_m_T_to_id[to] = _m_graph.size() - 1;
					_m_id_to_T[_m_graph.size() - 1] = to;
				}
				to_id = _m_T_to_id[to];

				_m_graph[from_id].push_back(to_id);

				if (!_m_is_directed)
					_m_graph[to_id].push_back(from_id);
			}

		template <typename T>
			inline std::vector<T>& Graph<T>::get_vertex(const T& index)
			{
				size_type id = _m_T_to_id[index];

				if (id < _m_graph.size()) {
					return _m_graph[index];
				}
			}

		template <typename T>
			inline std::vector<T>& Graph<T>::get_vertex_id(size_type index)
			{
				if (index < _m_graph.size()) {
					return _m_graph[index];
				}
			}

		template <typename T>
			void Graph<T>::copy_T_set(std::set<size_type>& input, std::set<T>& output)
			{
				for (std::set<size_type>::iterator it = input.begin(); it != input.end(); 
						++it) {
					output.insert(_m_id_to_T[*it]);
				}
			}

		template <typename T>
			void Graph<T>::copy_T_map(std::map<size_type, double>& input, 
					std::map<T, double>& output)
			{
				for (std::map<size_type, double>::iterator it = input.begin(); 
						it != input.end(); ++it) {
					output[_m_id_to_T[it->first]] = it->second;
				}	
			}

		template <typename T>
			void Graph<T>::copy_T_path(std::map<size_type, std::vector<size_type> >& input, 
					std::map<T, std::vector<T> >& output)
			{
				for (std::map<size_type, std::vector<size_type> >::iterator it = input.begin();
						it != input.end(); ++it) {
					for (size_type i = 0; i < (it->second).size(); ++i) {
						output[_m_id_to_T[it->first]].push_back(_m_id_to_T[(it->second)[i]]);
					}
				}	
			}


		/*
		 * @param nodes, all the nodes in the from->to
		 * @param paths, the previous nodes for certain node
		 * @param result, length
		 * @ret bool, if there exists any path
		 */
		template <typename T>
			void Graph<T>::single_source_dijkstra_full(T from, std::stack<T>& nodes, 
					std::map<T, std::vector<T> >& paths, std::map<T, double>& dist,
					std::map<T, double>& sigma)
			{
				//initialize
				std::priority_queue<heap_node_t> pq;
				std::set<size_type> seen;
				std::map<size_type, std::vector<size_type> > paths_id;
				std::map<size_type, double> dist_id;
				std::map<size_type, double> sigma_id;

				size_type node_id = _m_T_to_id[from];
				sigma_id[node_id] = 1.0f;

				pq.push(*(new heap_node_t(node_id, node_id, 0.0f)));

				while (!pq.empty()) {
					struct heap_node_t node = pq.top(); 

					pq.pop();

					size_type u = node.node_id;

					if (seen.find(u) != seen.end())//already in
						continue;

					//std::cout << "u " << u << std::endl;
					nodes.push(get_vertex_name(u));
					//update set
					//std::cout<<" u " << get_vertex_name[u] << " prev " << get_vertex_name[u] << std::endl;
					//std::cout<<" sigma " << sigma_id[u] << " sigma " << sigma_id[u] << std::endl;
					sigma_id[u] += sigma_id[node.prev_id];
					seen.insert(u);
					dist_id[u] = node.dist;

					for (size_type i = 0; i < _m_graph[u].size(); ++i) {
						size_type v = _m_graph[u][i];
						double uv_dist = node.dist + (_m_is_weighted ? 
								_m_weight[std::make_pair(u, v)] : 1.0f);

						if (seen.find(v) == seen.end() && 
								(dist_id.find(v) == dist_id.end() || uv_dist < dist_id[v])) {
							dist_id[v] = uv_dist;

							pq.push(*(new heap_node_t(v, u, uv_dist)));	

							sigma_id[v] = 0.0f;

							paths_id[v].clear();
							paths_id[v].push_back(u);
						} else if (uv_dist == dist_id[v]) {//equal path
							//std::cout<<" v " << get_vertex_name[v] << " u " << get_vertex_name[u] << std::endl;
							//std::cout<<" sigma " << sigma_id[v] << " sigma " << sigma_id[u] << std::endl;
							sigma_id[v] += sigma_id[u];
							paths_id[v].push_back(u);
						}
					}
				}

				//map back, define copy_if lambda?
				copy_T_path(paths_id, paths);

				copy_T_map(dist_id, dist);

				copy_T_map(sigma_id, sigma);
			}

		template <typename T>
			void Graph<T>::print_graph() const
			{
				for (size_type i = 0; i < _m_graph.size(); ++i) {
					std::cout << "tag : " << _m_id_to_T[i] << " links: " << std::endl;
					for (size_type j = 0; j < _m_graph[i].size(); ++j) {
						std::cout << "tag : " << _m_id_to_T[_m_graph[i][j]] << std::endl;
					}
				}

				std::cout<<std::endl;
			}

		template <typename T>
			void Graph<T>::print_graph() 
			{
				for (size_type i = 0; i < _m_graph.size(); ++i) {
					std::cout << "tag : " << _m_id_to_T[i] << " links: " << std::endl;
					for (size_type j = 0; j < _m_graph[i].size(); ++j) {
						std::cout << "tag : " << _m_id_to_T[_m_graph[i][j]] << std::endl;
					}
				}

				std::cout<<std::endl;
			}
	}//namespace base
}//namespace msd

#endif
