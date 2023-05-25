#include <iostream>
#include <vector>
#include <omp.h>
#include <queue>
using namespace std;
void parallelDFS(vector<vector<int>>& graph, int current, vector<bool>& visited) {
 visited[current] = true;
 int numThreads = omp_get_num_threads();
    int threadID = omp_get_thread_num();
    cout << "Thread " << threadID << " of " << numThreads << " threads - Visited vertex: " << current << endl;
 cout << "Visited vertex: " << current << endl;
 #pragma omp parallel for
 for (int i = 0; i < graph[current].size(); ++i) {
 int neighbor = graph[current][i];
 if (!visited[neighbor]) {
 #pragma omp task
 parallelDFS(graph, neighbor, visited);
 }
 }
}
void parallelBFS(vector<vector<int>>& graph, int source) {
 int numVertices = graph.size();
 vector<bool> visited(numVertices, false);
 vector<int> level(numVertices, -1);
 queue<int> q;
 level[source] = 0;
 visited[source] = true;
 q.push(source);
 while (!q.empty()) {
 int current = q.front();
 q.pop();
 #pragma omp parallel for

 for (int i = 0; i < graph[current].size(); ++i) {
 int neighbor = graph[current][i];
 if (!visited[neighbor]) {
 #pragma omp critical
 {
 visited[neighbor] = true;
 level[neighbor] = level[current] + 1;
 q.push(neighbor);
 }
 }
 }
 }
 // Print the level of each vertex
 cout << "Vertex\tLevel" << endl;
 for (int i = 0; i < numVertices; ++i) {
 cout << i << "\t" << level[i] << endl;
 }
}
void parallelDFSWrapper(vector<vector<int>>& graph) {
 int numVertices = graph.size();
 vector<bool> visited(numVertices, false);
 #pragma omp parallel
 {
 #pragma omp single nowait

 parallelDFS(graph, 0, visited);
 }
}
int main() {
 int numVertices = 7;
 vector<vector<int>> graph(numVertices);
 // Add edges to the graph
 graph[0] = {1, 2};
 graph[1] = {0, 3, 4};
 graph[2] = {0, 5, 6};
 graph[3] = {1};
 graph[4] = {1};
 graph[5] = {2};
 graph[6] = {2};
parallelDFSWrapper(graph);
 int source = 0;
 parallelBFS(graph, source);
 return 0;
}