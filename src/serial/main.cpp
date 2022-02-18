#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int x = 10;   //vertex no.


const int colors[x] = { 0,1,2,3,4,5,6,7,8,9 };
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

int rate_list[x]; //{ 0,0,0,0,0,0,0,0,0,0};

struct Graph_t {
	int vertex_rates[x];
	bool adj[x][x];
	int colors[x];
	bool colored[x];
};

//welsh powell

void colorIt(Graph_t g) {
	counter++;
	int biggest=0;
	int temp_rate = 0;

	//rate listing from adj matrix (counting edges)

	if (counter == 1)
		for (int i = 0; i < x; i++)
			for (int j = 0; j < x; j++)
				if (g.adj[i][j])
					rate_list[i]++;


	for (int w = 0; w < x; w++)
		if (!g.colored[w]) {
			g.vertex_rates[w] = rate_list[w];
			if (temp_rate < g.vertex_rates[w]) {
				temp_rate = g.vertex_rates[w];
				biggest = w;
			}
		}

	//coloring biggest one first

	g.colors[biggest] = colors[counter];
	std::cout << "vert(" << biggest << ")" <<":color("<< g.colors[biggest]<<")"<<std::endl;

	//coloring which doesn't have path with biggest one

	for (int e=0;e < x;e++)
		if (!g.adj[biggest][e] && biggest!=e && !g.colored[e]) {
			for (int t = 0; t < x;t++) {

				if(g.adj[e][t] &&g.colors[t]==g.colors[biggest]) problem = true;

					if (t == x - 1 && !problem) {
						g.colors[e] = colors[counter];
						std::cout << "vert(" << e << ")" <<":color("<< g.colors[e] << ")" << std::endl;
						g.colored[e] = true;
						problem = false;
					}
					else if (t == x - 1) problem = false;
			}
		}

		g.colored[biggest] = true;

	//somehow it gives sometimes "access violation" error

	if (std::all_of(std::begin(g.colored), std::end(g.colored), [](bool i) { return i; })) {
		std::cout << "Graph full colored" << std::endl;
		//system("pause");
		exit(EXIT_SUCCESS);

	}

	else colorIt(g); // recusive

}

int main()
{
	Graph_t graph_ele1;

	//init color

	for (int y = 0; y < x; y++) {
		graph_ele1.colors[y] = 99;
		graph_ele1.colored[y] = false;
	}

	int N;
	N = x;
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

	return 0;
}
