#pragma warning(disable: 4996)
#pragma once
#include <iostream>
#define NIL 0
#define INF INT_MAX
#include <cstdio>
 
 
struct Node
{
        int key;
        Node *next, *previous;
};
 
class List
{
public:
        Node *first, *last;
        int amount;
 
        List()
        {
                first = last = nullptr;
                amount = 0;
        }
 
        ~List()
        {
                while (amount) popFront();
        }
 
        bool empty()
        {
                return amount == 0;
        }
 
        void pushFront(int k)
        {
                Node* tmp = new Node;
                tmp->key = k;
                tmp->previous = nullptr;
                tmp->next = first;
                first = tmp;
                amount++;
                if (tmp->next) tmp->next->previous = tmp;
                else last = tmp;
        }
 
        void pushBack(int k)
        {
                Node* tmp = new Node;
                tmp->key = k;
                tmp->next = nullptr;
                tmp->previous = last;
                last = tmp;
                amount++;
                if (tmp->previous) tmp->previous->next = tmp;
                else first = tmp;
        }
 
        void remove(Node* node)
        {
 
                        amount--;
                        if (node->previous)
                                node->previous->next = node->next;
                        else
                                first = node->next;
                        if (node->next)
                                node->next->previous = node->previous;
                        else
                                last = node->previous;
                        delete node;
                
        }
 
        void popFront()
        {
                if (amount)
                        remove(first);
        }
 
        void popBack()
        {
                if (amount)
                        remove(last);
        }
 
        int getFirst()
        {
                return first->key;
        }
 
        int getLast()
        {
                return last->key;
        }
 
        int* getAll()
        {
                int* keys = new int[amount];
                Node* tmp = first;
                for (int i = 0; i < amount; i++)
                {
                        keys[i] = tmp->key;
                        tmp = tmp->next;
                }
                return keys;
        }
};
 
inline bool dfs(int l, List* adj, int* dist, int* pairU, int* pairV);
 
int main()
{
        int m, n, i, q, value;
        scanf("%d %d", &m, &n);
        List* adj = new List[m + 1];
        for (i = 1; i <= m; i++)
        {
                scanf("%d", &q);
                for (int j = 1; j <= q; j++)
                {
                        scanf("%d", &value);
                        adj[i].pushBack(value);
                }
        }
        int *pairL = new int[m + 1];
        int *pairR = new int[n + 1];
        int *pathSize = new int[m + 1];
 
        for (i = 0; i <= m; i++)
                pairL[i] = NIL;
        for (i = 0; i <= n; i++)
                pairR[i] = NIL;
        int matchings = 0;
        while (true)
        {
                List* queue = new List;
                for (i = 1; i <= m; i++)
                {
                        if (pairL[i] == NIL)
                        {
                                pathSize[i] = 0;
                                queue->pushBack(i);
                        }
                        else
                                pathSize[i] = INF;
                }
                pathSize[NIL] = INF;
                while (queue->empty() == false)
                {
                        q = queue->getFirst();
                        queue->popFront();
 
                        if (pathSize[q] < pathSize[NIL])
                        {
                                int size = adj[q].amount;
                                int* nodes = adj[q].getAll();
                                for (i = 0; i < size; i++)
                                {
                                        int val = nodes[i];
                                        if (pathSize[pairR[val]] == INF)
                                        {
                                                pathSize[pairR[val]] = pathSize[q] + 1;
                                                queue->pushBack(pairR[val]);
                                        }
                                }
                        }
                }
                if (pathSize[NIL] == INF)
                        break;
 
                for (i = 1; i <= m; i++)
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
        delete [] pathSize;
        delete[]adj;
        return 0;
}
 
inline bool dfs(int l, List* adj, int* dist, int* pairU, int* pairV)
{
        if (l != NIL)
        {
                int size = adj[l].amount;
                int* nodes = adj[l].getAll();
                for (int q = 0; q < size; q++)
                {
                        int val = nodes[q];
                        if (dist[pairV[val]] == dist[l] + 1)
                        {
                                if (dfs(pairV[val], adj, dist, pairU, pairV) == true)
                                {
                                        pairV[val] = l;
                                        pairU[l] = val;
                                        return true;
                                }
                        }
                }
                dist[l] = INF;
                return false;
        }
        return true;
}
 
