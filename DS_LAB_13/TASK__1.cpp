
#include <iostream>
using namespace std;

class Node
{
public:
    int vertex;
    Node* next;

    Node(int v)
    {
        vertex = v;
        next = NULL;
    }
};

class Graph
{
private:
    int vertices;
    Node** adjList;

public:
    Graph(int v)
    {
        vertices = v;
        adjList = new Node * [vertices];

        for (int i = 0; i < vertices; i++)
        {
            adjList[i] = NULL;
        }
    }

    void addOneDirection(int src, int dest)
    {
        Node* newNode = new Node(dest);

        if (adjList[src] == NULL)
        {
            adjList[src] = newNode;
        }
        else
        {
            Node* temp = adjList[src];

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = newNode;
        }
    }

    void addEdge(int u, int v)
    {
        addOneDirection(u, v);
        addOneDirection(v, u);
    }

    void displayGraph()
    {
        cout << "Adjacency List:" << endl;

        for (int i = 0; i < vertices; i++)
        {
            cout << i << " -> ";

            Node* temp = adjList[i];

            while (temp != NULL)
            {
                cout << temp->vertex << " -> ";
                temp = temp->next;
            }

            cout << "NULL" << endl;
        }
    }

    void BFS(int start)
    {
        bool* visited = new bool[vertices];

        for (int i = 0; i < vertices; i++)
        {
            visited[i] = false;
        }

        int* queue = new int[vertices];

        int front = 0;
        int rear = 0;

        queue[rear] = start;
        rear++;

        visited[start] = true;

        cout << "BFS Starting from User " << start << ": ";

        while (front < rear)
        {
            int current = queue[front];
            front++;

            cout << current << " ";

            Node* temp = adjList[current];

            while (temp != NULL)
            {
                int neighbor = temp->vertex;

                if (visited[neighbor] == false)
                {
                    visited[neighbor] = true;
                    queue[rear] = neighbor;
                    rear++;
                }

                temp = temp->next;
            }
        }

        cout << endl;

        delete[] visited;
        delete[] queue;
    }

    ~Graph()
    {
        for (int i = 0; i < vertices; i++)
        {
            Node* temp = adjList[i];

            while (temp != NULL)
            {
                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }

        delete[] adjList;
    }
};

int main()
{
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    g.displayGraph();

    cout << endl;

    g.BFS(0);
    g.BFS(1);

    return 0;
}
