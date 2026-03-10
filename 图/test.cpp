#define _CRT_SECURE_NO_WARNINGS 1
#include"Graph.h"
int main()
{
	char arr[] = {'C','A','D','B','E'};
	Matrix::Graph<char, int> graph(arr, sizeof(arr)/sizeof(char));
	graph.AddEdge('A', 'D', 1);
	graph.AddEdge('D', 'B', 2);
	graph.AddEdge('D', 'E', 3);
	graph.AddEdge('B', 'E', 4);
	graph.AddEdge('B', 'C', 5);

	graph.BFS('A');
	graph.BFS('B');

	graph.DFS('A');
	graph.DFS('B');


	return 0;
}