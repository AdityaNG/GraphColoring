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

#define MAXTHREADS 4
#define THREAD_TERMINATE_SIG -10
#define LOG_DATA true

std::vector<std::vector <int>> graph;

// List of thread IDs 
std::vector<pthread_t> THREADS(MAXTHREADS); // Actual Thread IDs
// TODO : Look into replacing this with malloc
std::vector < std::pair<int,int> > t_thread_numbers(MAXTHREADS); // Virtual Thread IDs

std::string decToBase(int num, int base) {
  if(num==0)
    return "0";

  std::string base_num = "";
  while (num>0) {
    int dig = int(num%base);
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

std::string padZeros(std::string s, int n) {
  while (s.length() < n) {
    s = "0" + s;
  }
  return s;
}

int getLength(int v) {
  int l = 0;
  for (int i=1; i<=v; i++) {
    l += pow(i, v);
  }
  return l;
}

std::pair<int,int> getItem(int v, int key) {
  int l = getLength(v);
  assert(key <= l);

  key+=1;
  int t = 1;
  int c = 1;
  while (key>t) {
    key-=t;
    c+=1;
    t = pow(c, v);
  }
        
  key -= 1;

  return std::make_pair(key, c);
}

bool isSafeToColor(std::vector<std::vector<int>> graph, std::vector <int> color) {
  int V = color.size();
  for (int i = 0; i < V; i++)
    for (int j = i + 1; j < V; j++)
      if (graph[i][j] == 1 && color[j] == color[i])
        return false;
  return true;
}

/*
 * Counter to decide which thread to 
 * allocate the incoming request to 
 */
int thread_count = 0;

/*
 * DataArg handler for thread_number
 */
void * handleDataArg(void * args) {

  std::pair<int,int> threadID_v = (std::pair<int,int>) * ((std::pair<int,int> * ) args);
  int thread_number = threadID_v.first;
  int v = threadID_v.second;

  pthread_t p_id = pthread_self();
  if (LOG_DATA) printf("[T%d]\tWating %ld, %d\n", thread_number, p_id, v);

  int min_count = v;

  int l = getLength(v);
  for (int i=0; i<l/MAXTHREADS; i++) {
    int id = i * MAXTHREADS + (thread_number%MAXTHREADS);
    std::pair<int,int> c_j = getItem(v, id);
    int c = c_j.second;
    int j = c_j.first;
    if (c < min_count) {
      std::string col = padZeros(decToBase(j, c), v);
      
      if (LOG_DATA) printf("[T%d]\t(%d, %d)\t->\t%s\n", thread_number, c, j, col.c_str());
      std::vector<int> colors(v, 0);
      for (int t=0; t<v; t++) {
        colors[t] = col.at(t) - '0';
      }

      assert(col.length()==v);
      if (isSafeToColor(graph, colors)) {
        min_count = c;
      }
    }
  }

  if (LOG_DATA) printf("[T%d]\t min=%d\n", thread_number, min_count);

  return NULL;
}

int main(int argc, char ** argv) {

  int v;
  std::cin >> v;

  graph = std::vector<std::vector <int>>(v, std::vector<int>(v, 0));

  for (int i=0; i<v; i++) {
    for (int j=0; j<v; j++) {
      std::cin >> graph[i][j];
    }
  }

  // Create all the threads
  for (int i = 0; i < MAXTHREADS; i++)
  {
    pthread_t thread_number;
    printf("[TM]\tCreating thread %d \n", i);
    t_thread_numbers[i] = std::make_pair(i, v);
    pthread_create( & thread_number, NULL, handleDataArg, (void * ) & t_thread_numbers[i]);
    THREADS[i] = thread_number;
  }

  for (int i = 0; i < MAXTHREADS; i++)
  {
    pthread_t thread_id = THREADS[i];
    pthread_join(thread_id, NULL);
    printf("[INT] Stopped thread %d \n", i);
  }

}