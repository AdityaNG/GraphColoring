#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#include <limits>

using namespace std;
const int V = 4;   //vertex no.


const int colors[V] = { 0,1,2, 4 };
int counter = 0;
bool problem = false;

/* 

	 Example graph

		 2      7---------8
		/ \      \        |
       /   \      \       |
      /     \      \      |
     1------3-------5-----9
     \     /       /      |
      \   /       /       |
       \ /       /        |
        4-------6---------10

*/

int rate_list[V]; //{ 0,0,0,0,0,0,0,0,0,0};

int min_colors = std::numeric_limits<int>::max();

struct Graph_t {
	int verteV_rates[V];
	bool adj[V][V];
	int colors[V];
	bool colored[V];
};

bool isSafeToColor(vector < vector < int >> & graph, vector < int > color) {
  for (int i = 0; i < V; i++)
    for (int j = i + 1; j < V; j++)
      if (graph[i][j] == 1 && color[j] == color[i])
        return false;
  return true;
}
 
void printColorArray(vector < int > color) {
  cout << ("Solution colors are: ") << endl;

  set<int> s;
  //min_colors

  for (int i = 0; i < color.size(); i++) {
    cout << (color[i]);
	s.insert(color[i]);
  }
  
  if (s.size() < min_colors) {
	min_colors = s.size();
  }

  cout << endl;
}
bool graphColoring(vector < vector < int >> & graph, int m, int i, vector < int > color) {
	//cout << m << '\t' << i << endl;
  if (i == V) {
    if (isSafeToColor(graph, color)) {
      printColorArray(color);
      //return true;
    }
    return false;
  }
  for (int j = 1; j <= m; j++) {
    color[i] = j;
    if (graphColoring(graph, m, i + 1, color))
      return true;
 
    color[i] = 0;
  }
 
  return false;
}

void colorIt(Graph_t g) {
	vector < vector < int >> graph(V, vector<int>(V,0));
	for (int i=0; i<V; i++) {
		for (int j = 0; j<V; j++)
		{
			graph[i][j] = g.adj[i][j];
		}
		
	}

	vector <int> color(V,0);
	for (int i=0; i<V; i++) {
		color[i] = 0;
	}

	graphColoring(graph, V, 0, color);
}

int main()
{
	Graph_t graph_ele1;

	//init color

	for (int y = 0; y < V; y++) {
		graph_ele1.colors[y] = 99;
		graph_ele1.colored[y] = false;
	}

	int N;
	N = V;
    bool graph_ele_in[N][N];

    int u;
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
        	cin >> u;
			graph_ele_in[i][j] = u;
		}
    }

	//init graph
	memcpy(&graph_ele1.adj, &graph_ele_in, sizeof(graph_ele1.adj));

	colorIt(graph_ele1);

	cout<<"min_colors: "<<min_colors<<endl;

	return 0;
}
