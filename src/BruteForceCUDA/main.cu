#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>
#include <cassert>
#include <bits/stdc++.h> // std::reverse

#include <cuda.h>

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

/*
TODO:
1. Remove C++ STL dependency in all functions, migrate to normal arrays
  1.1 (you may choose to migrate to migrate to CUDA's Thrust library)
2. DONE Remove any use of C++ strings, convert to c strings
3. DONE Remove any memory operations (malloc, free) from all the functions but main()
4. Rewrite the for loop in the main() fn as a kernel function
  4.1 Split up the task across the kernels
  4.2 Refer to make BruteForcePThread's handleDataArg() for details
5. Allocate memory on the GPU in the main function
6. Call the CUDA kernels appropriately

Useful:
1. To Compile:
  make BruteForceCUDA
2. To run:
  ./test.sh
*/

#define LOG_DATA false

using ll = long long;


std::vector<std::vector <ll>> graph;
ll* cgraph = &graph[][0];

// helper functions
std::string decToBase(ll num, ll base) {
  if(num==0)
    return "0";

  std::string base_num = "";
  while (num>0) {
    ll dig = ll(num%base);
    if(dig<10) {
      base_num += std::to_string(dig);
    } else {
      base_num += std::string(1, char('A'+dig-10));  // Using uppercase letters
    }
    num = num/base;
  }
  std::reverse(base_num.begin(), base_num.end());// To reverse the string
  return base_num;
}

std::string padZeros(std::string s, ll n) {
  while (s.length() < n) {
    s = "0" + s;
  }
  return s;
}

ll getLength(ll v) {
  ll l = 0;
  for (ll i=1; i<=v; i++) {
    l += pow(i, v);
  }
  return l;
}

std::pair<ll,ll> getItem(ll v, ll key) {
  ll l = getLength(v);
  assert(key <= l);

  key+=1;
  ll t = 1;
  ll c = 1;
  while (key>t) {
    key-=t;
    c+=1;
    t = pow(c, v);
  }
        
  key -= 1;

  return std::make_pair(key, c);
}

// coloring
__global__ void isSafeToColor(ll* cgraph, ll* color, int size, bool* answer) {
  ll V = size; 
  int xindex = blockIdx.x * blockDim.x + threadIdx.x;
  int yindex = xindex+1; //blockIdx.y * blockDim.y + threadIdx.y;
  //for (ll i = 0; i < V; i++)
    //for (ll j = i + 1; j < V; j++)
  if(xindex<V && yindex<V)
  {
    if (cgraph[xindex][yindex] == 1 && color[yindex] == color[xindex])
          *answer= false;
    *answer= true;
  }
}

int main(int argc, char ** argv) {

  ll v;
  std::cin >> v;

  // set to 0
  for (ll i=0; i<v; i++) {
    for (ll j=0; j<v; j++) {
      cgraph[i][j] = 0;
    }
  }

  // read input graph
  for (ll i=0; i<v; i++) {
    for (ll j=0; j<v; j++) {
      std::cin >> cgraph[i][j];
    }
  }

  ll min_count = v;

  ll l = getLength(v);
  for (ll i=0; i<l; i++) {
    //ll id = i * MAXTHREADS + (thread_number%MAXTHREADS);
    ll id = i;
    std::pair<ll,ll> c_j = getItem(v, id);
    ll c = c_j.second;
    ll j = c_j.first;
    
    //if (LOG_DATA) printf("(%lld, %lld)\n", c, j);
    if (c < min_count) {
      std::string col = padZeros(decToBase(j, c), v);
      
      if (LOG_DATA) printf("(%lld, %lld)\t->\t%s\n", c, j, col.c_str());

      // set to 0
      ll* colors[v];
      for (ll i=0; i<v; i++) {
        colors[i] = 0;
      }
      
      // set colors
      for (ll t=0; t<v; t++) {
        colors[t] = col.at(t) - '0';
      }

      assert(col.length()==v);
      // call kernel function
      bool h_answer;
      bool* d_answer;
      
      ll* d_graph;
      ll* d_colors;
      
      cudaMalloc((void **)&d_graph, v*v*sizeof(ll));
      cudaMalloc((void **)&d_colors, v*sizeof(ll));
      cudaMalloc(&d_answer, sizeof(bool));

      cudaMemcpy(d_graph, &cgraph, v*v*sizeof(ll), cudaMemcpyHostToDevice);
      cudaMemcpy(d_colors, &colors, v*sizeof(ll), cudaMemcpyHostToDevice);
      isSafeToColor<<<v*v,1>>>(d_graph, d_colors, v, d_answer);
      cudaMemcpy(&h_answer, d_answer, sizeof(bool), cudaMemcpyDeviceToHost); 
      
      if (h_answer) {
        min_count = c;
      }
      cudaFree(d_answer);
      cudaFree(d_graph); 
      cudaFree(d_colors); 
    }
  }

  //if (LOG_DATA)
  printf("min=%lld\n", min_count);

}
