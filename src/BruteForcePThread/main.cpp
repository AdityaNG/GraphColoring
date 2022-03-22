/* 
 * Thread Pool
 */

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>

#include <utility>

#include <sys/types.h>
#include <sys/syscall.h>
#include <cstdlib>
#include <signal.h>

#include <math.h>
#include <cassert>

#include <bits/stdc++.h>

#define MAXTHREADS 8
#define THREAD_TERMINATE_SIG -10
#define LOG_DATA false

using ll = long long;

std::vector<std::vector <ll>> graph;

// List of thread IDs 
std::vector<pthread_t> THREADS(MAXTHREADS); // Actual Thread IDs
// TODO : Look llo replacing this with malloc
std::vector < std::pair<ll,ll> > t_thread_numbers(MAXTHREADS); // Virtual Thread IDs

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

/*
 * Counter to decide which thread to 
 * allocate the incoming request to 
 */
ll thread_count = 0;

/*
 * DataArg handler for thread_number
 */
void * handleDataArg(void * args) {

  std::pair<ll,ll> threadID_v = (std::pair<ll,ll>) * ((std::pair<ll,ll> * ) args);
  ll thread_number = threadID_v.first;
  ll v = threadID_v.second;

  pthread_t p_id = pthread_self();
  if (LOG_DATA) printf("[T%lld]\tStarted %ld, %lld\n", thread_number, p_id, v);

  ll min_count = v;

  ll l = getLength(v);
  for (ll i=0; i<l/MAXTHREADS; i++) {
    ll id = i * MAXTHREADS + (thread_number%MAXTHREADS);
    std::pair<ll,ll> c_j = getItem(v, id);
    ll c = c_j.second;
    ll j = c_j.first;
    if (LOG_DATA) printf("[T%lld]\t(%lld, %lld)\n", thread_number, c, j);
    if (c < min_count) {
      std::string col = padZeros(decToBase(j, c), v);
      
      //if (LOG_DATA) printf("[T%lld]\t(%lld, %lld)\t->\t%s\n", thread_number, c, j, col.c_str());

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
  printf("[T%lld]\t min=%lld\n", thread_number, min_count);

  return NULL;
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

  // Create all the threads
  for (ll i = 0; i < MAXTHREADS; i++)
  {
    pthread_t thread_number;
    printf("[TM]\tCreating thread %lld \n", i);
    t_thread_numbers[i] = std::make_pair(i, v);
    pthread_create( & thread_number, NULL, handleDataArg, (void * ) & t_thread_numbers[i]);
    THREADS[i] = thread_number;
  }

  for (ll i = 0; i < MAXTHREADS; i++)
  {
    pthread_t thread_id = THREADS[i];
    pthread_join(thread_id, NULL);
    printf("[ll] Stopped thread %lld \n", i);
  }

}