#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

#define pb push_back

int main(int argc, char* argv[]){

	ifstream file;
	ofstream outFile;
	int node1, node2; 
	string graphType;
	int startNode;
	char *  filename;
	int weight, k;
	int findMin(vector<int>, vector<bool>, vector<bool>);
	void relax(int, int, int, vector<int>&, vector<bool>&, vector<bool>&, int*);
	int dist(int, int, vector< vector<int> >&, vector< vector<int> >, vector< vector<int> >, int, int&, vector<int>);
	
	
	if(argc != 4){
		cout << "Error: Invalid number of arguments\nUsage is 'shortestpaths <filename> <start node> <k>' \n";
		return 1;
	}
	vector<char> node;
	vector<int> fakeNodes;

	filename = argv[1];
	string start(argv[2]);
	k = atoi(argv[3]);

	file.open(filename);
	if(!file.is_open()){
		cout << "Error: File does not exist\n";
		return 1;
	}

	outFile.open("out.txt");
	char next;
	while(file.peek() == '#'){
		while(file.get(next)){
			 if (next == '\n'){    
			 	break;        
			 }                  
		}
	}

	vector<vector<int> > alist;
	vector<vector<int> > w;
	deque<int> vertices;
	vector<int> keyValue;
	vector<bool> is_infinity;
	vector<bool> visited;
	
	int distance[10] = {0,0,0,0,0,0,0,0,0,0};
	int counter = 1;
	keyValue.resize(10);
	is_infinity.resize(10);
	alist.resize(10);
	w.resize(10);
	visited.resize(10);
	file >> graphType;

	
	string N1, N2;
	file >> N1 >> N2 >> weight;
	int nodeVal1 = 0, nodeVal2 = 0;
	while(!file.eof()){
	bool found1 = false, found2 = false;
		for(int i = 0; i < node.size(); i++){
			if(N1[0] == node[i]){
				nodeVal1 = i;
				found1 = true;
				break;
			}
		}
		if(found1 != true){
			node.pb(N1[0]);
			nodeVal1 = node.size() -1;	
		}
		for(int i = 0; i < node.size(); i++){
			if(N2[0] == node[i]){
				nodeVal2 = i;
				found2 = true;
				break;
			}
		}
		if(found2 != true){
			node.pb(N2[0]);
			nodeVal2 = node.size() -1;	
		}
		if(nodeVal1 != nodeVal2)
			alist[nodeVal1].pb(nodeVal2);
		w[nodeVal1].pb(weight);
		file >> N1 >> N2 >> weight;
	}
	
	bool found = false;	
	for(int i = 0; i < node.size(); i++){
		
			if(start[0] == node[i]){
				found = true;
				startNode = i;
				break;
			}
	}
	
	if(found == true){
		is_infinity.assign(10, true);
		visited.assign(10, false);
		keyValue[startNode] = 0;
		is_infinity[startNode] = false;
		distance[startNode] = 0;
	}
	
	for(int i = 0; i < 10; i++){
		if(!alist[i].empty())
		vertices.pb(i);
	}

	bool udAdj[10][10];
	if(graphType == "UD"){
		int index = 0;
		int W = 0;
		for(int i = 0; i < 10; i++){
			for(int j =0; j < 10; j ++){
					udAdj[i][j] = false;
			}
		}
		for(int i = 0; i < alist.size(); i++){
			for(int j =0; j < alist[i].size(); j ++){
				index = alist[i][j];
				W = w[i][j];
				udAdj[i][index] = true;			
				if(udAdj[index][i] == false){
					alist[index].pb(i);
					w[index].pb(W);
					udAdj[index][i] = true;
				}
			}
		}
		
		int u, v;
		outFile << "Dijkstra\nSource: " << node[startNode] << "\n";
		while(!vertices.empty()){
			u = findMin(keyValue, is_infinity, visited);
				for(int i = 0; i < alist[u].size(); i++){	
						v = alist[u][i];
						if(udAdj[v][u] == true){
						if(!visited[v]){ 
							relax(u, v, w[u][i], keyValue, is_infinity, visited, distance);
						
						}
						udAdj[u][v] = false;
					}
					else{
						visited[u] = true;
					}
				}
				vertices.pop_front();
		}
		
		for(int i = 0; i < keyValue.size(); i++){
			if((keyValue[i] != 0) || (i == startNode))
				outFile << "NODE " << node[i] << ": " << keyValue[i] << "\n";
		}
		outFile << "End Dijkstra\n\n";
		outFile << "Shortest Reliable Paths Algorithm\n";
		outFile << "Integer k: " << k << " Source: " << node[startNode] << "\n";
		for(int i = 0; i < 10; i++){
			if((distance[i] <= k) && ((keyValue[i] != 0) || (i == startNode)))
				outFile << "NODE " << node[i] << ": " << keyValue[i] << "\n";
		}
		outFile << "End Shortest Reliable Paths Algorithm\n";
	}

	if(graphType == "D"){
		int u, v;
		outFile << "Dijkstra\nSource: " << node[startNode] << "\n";
		while(!vertices.empty()){
			u = findMin(keyValue, is_infinity, visited);
			if(alist[u].size() == 0){
				visited[u] = true;
				vertices.pop_front();
			}
			else{
				visited[u] = true;
				for(int i = 0; i < alist[u].size(); i++){
					v = alist[u][i];
					if(!visited[v]){
						relax(u, v, w[u][i], keyValue, is_infinity, visited, distance);
					}
				}
				vertices.pop_front();
			}
		}
		
		for(int i = 0; i < keyValue.size(); i++){
			if((keyValue[i] != 0) || (i == startNode))
				outFile << "NODE " << node[i] << ": " << keyValue[i] << "\n";
		}
		outFile << "End Dijkstra\n\n";
		outFile << "Shortest Reliable Paths Algorithm\n";
		outFile << "Integer k: " << k << " Source: " << node[startNode] << "\n";
		for(int i = 0; i < 10; i++){
			if((distance[i] <= k) && ((keyValue[i] != 0) || (i == startNode)))
				outFile << "NODE " << node[i] << ": " << keyValue[i] << "\n";
		}
		outFile << "End Shortest Reliable Paths Algorithm\n";
	}
	
	vector< vector <int> > paths;
	paths.resize(keyValue.size());
	
	for (int j = 0; j < paths.size(); j++)	
			paths[j].resize(k+1);
			
	paths[startNode].assign(k+1, 0);
	for (int j = 0; j < paths.size(); j++){
		if(j != startNode){	
			paths[j].assign(k+1, -2);
			paths[j][0] = -1;
			}
		}

	
	int total =0;
	for(int i = 0; i < 10; i++){
		if(!alist[i].empty())
		total++;
	}
	int max = (total - 1) * k;
	int newcount = 0;
	
	int min = 0;
	vector<int> mins;
	for(int i = 0; i < total; i++){
		if(i == startNode)
			continue;
		else{
			for(int j = 1; j <= k; j++){
				paths[i][j] = dist(i, j, paths, alist, w, startNode, min, mins);
			}
		}
	}
	
return 0;
}

int dist(int node, int i, vector< vector<int> >& paths, vector< vector<int> > alist, vector< vector<int> > w, int startNode, int& min, vector<int> mins){
	int value = 0;
	//cout << "node: " << node << "\n";
	//cout << "i: " << i << "\n";
	if(node == startNode){
		return 0;
	}
	else if(i == 0)
		return -1;
	else if(paths[node][i] != -2)
		return paths[node][i];
	else{
		for(int m = 0; m < alist[node].size(); m++){
			//cout << "node: " << node << "\n";
			int adjNode = alist[node][m];
			
			value = dist(adjNode, i-1, paths, alist, w, startNode, min, mins);
			if((value >= 0)){
				value += w[node][m];
				mins.pb(value);
				if(value < paths[adjNode][i-1])
				paths[adjNode][i-1] = value;
			}
		}
		if(mins.size() > 0){
			min = mins[0];
			for(int n = 1; n < mins.size(); n++){
				if(mins[n] < min)
					min = mins[n];
			}
			paths[node][i] = min;
		}
	}
	mins.clear();
	
	return min;
}

void relax(int u, int v, int w, vector<int>& values, vector<bool>& infinity, vector<bool>& visited, int *distance){

	if(infinity[v] == true){
		values[v] = values[u] + w;
		if(distance[v] == 0) 
			distance[v] = distance[u]+1;
		}
	else if(values[v] >= (values[u] + w)){
		values[v] = values[u] + w;
		if(distance[v] == 0) 
			distance[v] = distance[u]+1;
	}
	infinity[v] = false;
	visited[u] = true;
}

int findMin(vector<int> values, vector<bool> infinity, vector<bool> visited){
	int min;
	bool setMin = false;
	int index = 0;
	for(int i = 0; i < values.size(); i++){
		if((infinity[i] != true) && (visited[i] == false)){
			if(setMin == false){
				min = values[i];
				setMin = true;
				index = i;
			}
			else{
				if(values[i] <= min){
					min = values[i];
					index = i;
				}
			}
		}
	}
	return index;
}


