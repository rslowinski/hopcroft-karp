#pragma warning(disable: 4996)
#pragma once
#include <iostream>
#define NIL 0
#define INF INT_MAX
#define QUEUE_SIZE 5000
#include <cstdio>


class Queue
{
	int *queue;
	int size;
	int first;
	int last;
public:
	Queue()
	{
		queue = new int[QUEUE_SIZE];
		first = 0;
		size = 0;
		last = 0;
	}
	void pushBack(int k)
	{
		queue[last] = k;
		last = (last + 1) % QUEUE_SIZE;
		size++;
	}
	void popFront()
	{
		if(size!=0)
		{
			first = (first + 1) % QUEUE_SIZE;
			size--;
		}
	}
	bool empty()
	{
		return size == 0;
	}
	int getFirst()
	{
		return queue[first];
	}
	void clear()
	{
		last = 0;
		first = 0;
		size = 0;
	}
	~Queue()
	{
		delete[] queue;
	}
};
inline bool dfs(int l, int** adj, int* dist, int* pairU, int* pairV);

int main()
{
	int left, right, i, q, value, j;
	scanf("%d %d", &left, &right);
	int **adj = new int*[left + 1];
	for (i = 1; i <= left; i++)
	{
		scanf("%d", &q);
		adj[i] = new int[q + 2];
		adj[i][0] = q;
		for (j = 1; j <= q; j++)
		{
			scanf("%d", &value);
			adj[i][j] = value;
		}adj[i][j] = -1;
	}
	int *pairL = new int[left + 1];
	int *pairR = new int[right + 1];
	int *pathSize = new int[left + 1];

	for (i = 0; i <= left; i++)
		pairL[i] = NIL;
	for (i = 0; i <= right; i++)
		pairR[i] = NIL;
	register unsigned int matchings = 0;
	Queue queue;
	while (true)
	{
		queue.clear();
		for (i = 1; i <= left; i++)
		{
			if (pairL[i] == NIL)
			{
				pathSize[i] = 0;
				queue.pushBack(i);
			}
			else
				pathSize[i] = INF;
		}
		pathSize[NIL] = INF;
		while (queue.empty() == false)
		{
			q = queue.getFirst();
			queue.popFront();

			if (pathSize[q] < pathSize[NIL])
			{
				for (i = 1; adj[q][i] != -1; i++)
				{
					if (pathSize[pairR[adj[q][i]]] == INF)
					{
						pathSize[pairR[adj[q][i]]] = pathSize[q] + 1;
						queue.pushBack(pairR[adj[q][i]]);
					}
				}

			}
		}
		if (pathSize[NIL] == INF)
			break;

		for (i = 1; i <= left; i++)
		{
			if (pairL[i] == NIL && dfs(i, adj, pathSize, pairL, pairR))
				matchings++;
		}
	}

	std::cout << matchings;
	//getchar();
	//getchar();

	delete [] pairL;
	delete [] pairR;
	delete[] pathSize;
	for (i = 1; i <= left; i++)
	{
		delete[]adj[i];
	}
	delete[]adj;
	return 0;
}

inline bool dfs(int l, int** adj, int* dist, int* pairU, int* pairV)
{
	if (l != NIL)
	{
		for (int q = 1; adj[l][q] != -1; q++)
		{
			if (dist[pairV[adj[l][q]]] == dist[l] + 1)
			{
				if (dfs(pairV[adj[l][q]], adj, dist, pairU, pairV) == true)
				{
					pairV[adj[l][q]] = l;
					pairU[l] = adj[l][q];
					return true;
				}
			}
		}

		dist[l] = INF;
		return false;
	}
	return true;
}
