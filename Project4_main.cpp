#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <string>

//Initializing the graph (adj list)
// This function return
std::string graph_init(std::string const x){
	// extracts the file names
	std::string extracted_word;
	if(x[0] == '#'){
		int first_bracket = x.find("<");
		int end_bracket = x.find(">");
		int a = 0;

		extracted_word = x.substr(first_bracket+1, end_bracket-first_bracket-1);
		return extracted_word;
	}
	return "you mis-used a line that does not have #include";
}

std::vector<std::vector<std::string> > find_neibrs(std::vector<std::vector<std::string> > const x){
	std::vector<std::string> new_adj_list;
	std::vector<std::vector<std::string> > new_adj_graph;
	new_adj_list.push_back(x[0][0]);
	for(int i{0}; i<x.size(); ++i){
		for(int j{0}; j<x[i].size(); ++j){
			bool check_rep = true;
			for(int k{0}; k<new_adj_list.size(); ++k){
				if(x[i][j] == new_adj_list[k]){
					check_rep = false;
					break;
				}else{
					check_rep = true;
				}
			}
			if(check_rep){
				new_adj_list.push_back(x[i][j]);
			}
		
		}
	}
	

	for(int i{0}; i<new_adj_list.size(); ++i){
		new_adj_graph.push_back(std::vector<std::string>());
	}

	for(int i{0}; i<new_adj_list.size(); ++i){
		new_adj_graph[i].push_back(new_adj_list[i]);
	}

	for(int i{0}; i<x.size(); ++i){
		for(int j{1}; j<x[i].size(); ++j){
			for(int k{0}; k<new_adj_graph.size(); ++k){
				if(x[i][j] == new_adj_graph[k][0]){
					new_adj_graph[k].push_back(x[i][0]);
				}
			}
		}
	}

	for(int k{0}; k<new_adj_graph.size(); ++k){
		for(int i{0}; i<new_adj_graph[k].size(); ++i){
			std::cout << new_adj_graph[k][i] << " -> ";
		}
		std::cout << std::endl;
	}



	return new_adj_graph;
}


int main(int argc, char** argv)
{
	//first input argument is always the program name...
	char* fileName = argv[1];
	
	//open the file
	std::ifstream fin(fileName);
	
	if(!fin)
	{
		std::cout<< "File not found" << std::endl;
		return EXIT_FAILURE;
	}
	//initialize variables 
	int vertices_count = -1;
	std::vector<std::vector<std::string> > adj_graph;
	std::vector<std::vector<std::string> > degree_graph;
	std::string line;
	int i{-1};
	int j{-1};

	vertices_count = -1;
	while(std::getline(fin,line))
	{
		// Incrementing number of vertices when seeing 'F'
		if(line[0] != '#'){
			std::cout<<std::endl;
			++vertices_count;
			++i;
			j = 0;
			adj_graph.push_back(std::vector<std::string>());
			adj_graph[vertices_count].push_back(line);
			std::cout << adj_graph[vertices_count][j] << " -> ";
			std::cout << std::endl;
		}
		// updating sub-vectors for each vertex
		else if(line[0] == '#'){
			adj_graph[vertices_count].push_back(graph_init(line));
			++j;
			std::cout << adj_graph[vertices_count][j] << " -> ";
		}

		//this is just to get you going.  You'll need to do much more here...
		//std::cout << line << std::endl;
	}


	// if(adj_graph[0][0] == "FILE_A"){
	// 	std::cout << adj_graph.size();
	// }

	// std::cout << std::endl;
	// for(int i{0}; i<adj_graph.size(); ++i){
	// 	for(int j{0}; j<adj_graph[i].size(); ++j){
	// 		std::cout << adj_graph[i][j] << " -> ";
	// 	}
	// 	std::cout << std::endl;
	// }
	std::cout << "***********************************" << std::endl;
	//Initialize topology variables
	std::deque<std::string> deg_zero_q;
	std::deque<std::string> temp_zero_q;
	std::vector<std::string> new_adj_list;
	std::vector<std::string> temp_adj_list;
	new_adj_list.push_back(adj_graph[0][0]);
	for(int i{0}; i<adj_graph.size(); ++i){
		for(int j{0}; j<adj_graph[i].size(); ++j){
			bool check_rep = true;
			for(int k{0}; k<new_adj_list.size(); ++k){
				if(adj_graph[i][j] == new_adj_list[k]){
					check_rep = false;
					break;
				}else{
					check_rep = true;
				}
			}
			if(check_rep){
				new_adj_list.push_back(adj_graph[i][j]);
			}
		
		}
	}
	degree_graph = find_neibrs(adj_graph);
	temp_adj_list = new_adj_list;
	// Initializing the vertex queue for degree zero verticies
	std::string temp_holder;
	for(int l{0}; l<temp_adj_list.size(); ++l){
		for(int i{0}; i<new_adj_list.size(); ++i){
			bool cheq_repeat = false;

			for(int z{0}; z<temp_zero_q.size(); ++z){			
				if(temp_zero_q[z] == new_adj_list[i]){
					cheq_repeat = true;
					break;
				}
			}

			if(cheq_repeat == false){
				int vertex_deg = 0;
				for(int j{0}; j<degree_graph.size(); ++j){
					for(int k{1}; k<degree_graph[j].size();++k){
						if(degree_graph[j][k] == new_adj_list[i]){
							vertex_deg +=1;
						}
					}
				}
				if(vertex_deg == 0){
					deg_zero_q.push_back(new_adj_list[i]);
					temp_zero_q.push_back(new_adj_list[i]);
				}
			}
		}
		std::cout << deg_zero_q.front() << std::endl;
		
		// Remove the printed vertex out of degree_graph
		for(int j{0}; j<degree_graph.size(); ++j){
			for(int k{1}; k<degree_graph[j].size();++k){
				if(degree_graph[j][k] == deg_zero_q.front()){
					degree_graph[j].erase(degree_graph[j].begin()+k);
				}
			}
			if(degree_graph[j][0] == deg_zero_q.front()){
				degree_graph.erase(degree_graph.begin()+j);
			}
		}
		temp_holder = deg_zero_q.front();
		deg_zero_q.pop_front();
	}



	return EXIT_SUCCESS;
}