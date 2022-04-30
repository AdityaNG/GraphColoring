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
2. Remove any use of C++ strings, convert to c strings
3. Remove any memory operations (malloc, free) from all the functions but main()
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

bool isSafeToColor(std::vector<std::vector<ll>> graph, std::vector <ll> color) {
  ll V = color.size();
  for (ll i = 0; i < V; i++)
    for (ll j = i + 1; j < V; j++)
      if (graph[i][j] == 1 && color[j] == color[i])
        return false;
  return true;
}

int main(int argc, char ** argv) {

  ll v;
  std::cin >> v;

  graph = std::vector<std::vector <ll>>(v, std::vector<ll>(v, 0));

  for (ll i=0; i<v; i++) {
    for (ll j=0; j<v; j++) {
      std::cin >> graph[i][j];
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

      std::vector<ll> colors(v, 0);
      for (ll t=0; t<v; t++) {
        colors[t] = col.at(t) - '0';
      }

      assert(col.length()==v);
      if (isSafeToColor(graph, colors)) {
        min_count = c;
      }
    }
  }

  //if (LOG_DATA)
  printf("min=%lld\n", min_count);

}