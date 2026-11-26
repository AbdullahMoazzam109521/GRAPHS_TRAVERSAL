
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
    bool* visited;

public:
    Graph(int v)
    {
        vertices = v;

        adjList = new Node * [vertices];
        visited = new bool[vertices];

        for (int i = 0; i < vertices; i++)
        {
            adjList[i] = NULL;
            visited[i] = false;
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

    void resetVisited()
    {
        for (int i = 0; i < vertices; i++)
        {
            visited[i] = false;
        }
    }

    void DFS(int vertex)
    {
        visited[vertex] = true;

        cout << vertex << " ";

        Node* temp = adjList[vertex];

        while (temp != NULL)
        {
            int neighbor = temp->vertex;

            if (visited[neighbor] == false)
            {
                DFS(neighbor);
            }

            temp = temp->next;
        }
    }

    void findConnectedComponents()
    {
        resetVisited();

        int count = 0;

        cout << "Connected Components:" << endl;

        for (int i = 0; i < vertices; i++)
        {
            if (visited[i] == false)
            {
                count++;

                cout << "Component " << count << ": ";

                DFS(i);

                cout << endl;
            }
        }

        cout << "Total Connected Components: " << count << endl;
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
        delete[] visited;
    }
};

int main()
{
    Graph g(7);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(4, 5);

    g.displayGraph();

    cout << endl;

    cout << "DFS Starting from Computer 0: ";
    g.resetVisited();
    g.DFS(0);

    cout << endl << endl;

    g.findConnectedComponents();

    return 0;
}
