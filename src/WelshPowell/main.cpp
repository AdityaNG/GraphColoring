#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>
#include <cassert>
#include <bits/stdc++.h> // std::reverse

#define LOG_DATA false

using ll = long long;

void colorIt(std::vector<std::vector <ll>> graph, std::vector<ll> rate_list, ll v, ll counter) {
	counter++;
	int biggest=0;
	int temp_rate = 0;

	//rate listing from adj matrix (counting edges)

	if (counter == 1)
		for (int i = 0; i < v; i++)
			for (int j = 0; j < v; j++)
				if (g.adj[i][j])
					rate_list[i]++;


	for (int w = 0; w < v; w++)
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

	for (int e=0;e < v;e++)
		if (!g.adj[biggest][e] && biggest!=e && !g.colored[e]) {
			for (int t = 0; t < v;t++) {

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

	else colorIt(graph, counter); // recusive

}

int main(int argc, char ** argv) {
	ll v;
	std::cin >> v;

	std::vector<std::vector <ll>> graph;
	graph = std::vector<std::vector <ll>>(v, std::vector<ll>(v, 0));

	for (ll i=0; i<v; i++) {
		for (ll j=0; j<v; j++) {
		std::cin >> graph[i][j];
		}
	}

	std::vector<ll> rate_list(v,0);
	
	colorIt(graph, rate_list, v, 0);

}