#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
//using namespace std;
void topologicalSort(std::vector<std::vector<std::string> >& adjListCopy, std::queue<std::string>& topo, std::vector<std::string>& zero_Indegrees);

int main(int argc, char** argv) {
	//first input argument is always the program name...
	char* fileName = argv[1];
	
	//open the file
	std::ifstream fin(fileName);
	
	if(!fin) {
		std::cout<< "File not found" << std::endl;
		return EXIT_FAILURE;
	}
 
  std::vector<std::vector<std::string> > adjList; 
  
  int v = -1;
  
	std::string line;
  std::string re;
  while(std::getline(fin,line)) {
    if (line[0] != '#') {
 
      re = line;
      
      //check if Duplicate
      bool Not_duplicate = true;
      for (int i = 0; i < adjList.size(); i++) {
        if (adjList[i][0] == line){
          Not_duplicate = false;
        }
      }
      // It is Not a Duplicate
      if (Not_duplicate == true){
        v++;
        adjList.push_back(std::vector<std::string>());
        adjList[v].push_back(line);
      }
    }
    else if (line[0] == '#') {
      //take out #include < >
      line.erase (0,10);
      line.erase (line.end()-1);
      
      //check if Duplicate
      bool Not_duplicate = true;
      
      for (int i = 0; i < adjList.size(); i++) {
        if (adjList[i][0] == line){
          Not_duplicate = false;
        }
      }
      
      // It is Not a Duplicate
      if (Not_duplicate == true){
        v++;
        
        int vertix_value1 = 0;
        for (int i = 0; i < adjList.size(); i++) {
          vertix_value1++;
          if (adjList[i][0] == re){
            break;
          }
        }
        vertix_value1--;
        
        adjList.push_back(std::vector<std::string>());
        adjList[v].push_back(line);
        adjList[vertix_value1].push_back(line);
      }
      // It is a Duplicate
      else if (Not_duplicate == false) {
        
        int vertix_value = 0;
        for (int i = 0; i < adjList.size(); i++) {
          vertix_value++;
          if (adjList[i][0] == re){
            break;
          }
        }
        vertix_value--;
        /*
        int y_value = 1;
        for (int i = 1; i < adjList.size(); i++) {
          y_value++;
          if (adjList[vertix_value][i] == re){
            break;
          }
        }
        y_value--;
        */
        adjList[vertix_value].push_back(line);
      }
    }
	}

  // print graph
  for (int i = 0; i < adjList.size(); i++) {
    for (int j = 0; j < adjList[i].size(); j++) {
      std::cout << adjList[i][j] << "--->";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  
  //create copied vector
  std::vector<std::vector<std::string> > adjListCopy; 
  
  //adjListCopy = adjList;
  /*
  for (int i = 0; i < adjListCopy.size(); i++) {
    for (int j = 0; j < adjListCopy[i].size(); j++) {
      std::cout << adjListCopy[i][j] << "--->";
    }
    std::cout << std::endl;
  }
  */
  std::cout << std::endl;
  
  std::queue<std::string> topo;
  std::vector<std::string> zero_Indegrees;
  
  /*
  //check if not dag
  for (int i = 0; i < adjList.size(); i++) {
    if (adjList[i].size() == 1) {
      zero_Indegrees.push(adjList[i][0]);
    }
  }
  if (zero_Indegrees.empty()) {
    return EXIT_SUCCESS;
  }
  else {
    topologicalSort(adjListCopy, topo, zero_Indegrees);
  }
  */
  topologicalSort(adjList, topo, zero_Indegrees);

  while(!topo.empty()){
		std::cout << topo.front();
		topo.pop();
    std::cout << std::endl;
	}
 
  
	return EXIT_SUCCESS;
}


void topologicalSort(std::vector<std::vector<std::string> >& adjListCopy, std::queue<std::string>& topo, std::vector<std::string>& zero_Indegrees) {
  
  for (int i = 0; i < adjListCopy.size(); i++) {
    if (adjListCopy[i].size() == 1) { //try 0?
      zero_Indegrees.push_back(adjListCopy[i][0]);
      topo.push(adjListCopy[i][0]);
    }
  }
  
  int s = 0;
  while (s < zero_Indegrees.size()) {
    for (int r = 0; r < adjListCopy.size(); ++r) {
      for (int j = 0; j < adjListCopy.size(); ++j) {
        if (adjListCopy[r][j] == zero_Indegrees[s]) {
          adjListCopy[r][j].erase();
          if (adjListCopy[r].size() == 0) {
            adjListCopy.erase(adjListCopy.begin()+r);
          }
        }
      }
    }
    ++s;
  }
//   if (!adjListCopy.empty()) {
//     zero_Indegrees.clear();
//     topologicalSort(adjListCopy, topo, zero_Indegrees);
//   }
}












