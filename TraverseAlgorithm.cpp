#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class GraphNode {
private:
    int id;

public:
    char color;
    int dist;
    int d_time;
    int f_time;
    GraphNode *pi;
    vector<GraphNode*> adjacency;
    GraphNode(int id) {
        this -> id = id;
        this -> color = 'W';
        this -> dist = INFINITY;
        this -> pi = nullptr;
    }
    int getId() {
        return this -> id;
    }
};

//Stack版 DFS
void DFS(GraphNode* s, int n) { // n：number of vertex in Graph
    vector<bool> visited(n, false);
    stack<GraphNode*> stack;
    stack.push(s);

    while (!stack.empty()) {
        s = stack.top();
        stack.pop();

        if (!visited[s -> getId()]) {
            cout << s -> getId() << " ";
            visited[s -> getId()] = true;
        }

        for (int i = 0; i < s -> adjacency.size(); i++) {
            if (!visited[s -> adjacency[i] -> getId()]) {
                stack.push(s -> adjacency[i]);
            }
        }
    }
}

//DS版 DFS (Recursion Stack)
vector<bool> visited(8, false);
void DFS(GraphNode* s) {
    visited[s -> getId()] = true;
    cout << s -> getId() << " ";
    for (int i = 0; i < s -> adjacency.size(); i++) {
        if (!visited[s -> adjacency[i] -> getId()]) {
            DFS(s -> adjacency[i]);
        }
    }
}

//ALGO版 DFS
void DFS_Visit(GraphNode* s, int* timer) {
    *timer = *timer + 1;
    s -> d_time = *timer;
    s -> color = 'G';
    cout << s -> getId() << " ";
    for (int i = 0; i < s -> adjacency.size(); i++) {
        if (s -> adjacency[i] -> color == 'W') {
            s -> adjacency[i] -> pi = s;
            DFS_Visit(s -> adjacency[i], timer);
        }
    }
    s -> color = 'B';
    *timer = *timer + 1;
    s -> f_time = *timer;
}
void DFS(vector<GraphNode*> G) {
    int timer = 0;
    for (int i = 0; i < G.size(); i++) {
        if (G[i] -> color == 'W') {
            DFS_Visit(G[i], &timer);
        }
    }
    cout << endl;
    for (int i = 0; i < G.size(); i++) {
        cout << G[i] -> getId() << ":" << G[i] -> d_time << "/" << G[i] -> f_time << " ";
    }
    cout << endl;
    for (int i = 1; i < G.size(); i++) {
        cout << G[i] -> getId() << ":" << G[i] -> pi -> getId() << " ";
    }
    cout << endl;
}

//DS版 BFS (Queue)
void BFS(GraphNode* s, int n) {
    vector<bool> visited(n, false);
    queue<GraphNode*> queue;
    queue.push(s);
    visited[s -> getId()] = true;
    cout << s -> getId() << " ";
    while (!queue.empty()) {
        s = queue.front();
        queue.pop();
        
        for (int i = 0; i < s -> adjacency.size(); i++) {
            if (!visited[s -> adjacency[i] -> getId()]) {
                visited[s -> adjacency[i] -> getId()] = true;
                cout << s -> adjacency[i] -> getId() << " ";
                queue.push(s -> adjacency[i]);
            }
        }
    }
}

//ALGO版
void BFS(GraphNode* s) {
    s -> color = 'G'; //拜訪到的點設為灰色
    cout << s -> getId() << " ";
    s -> dist = 0;
    s -> pi = nullptr;
    queue<GraphNode*> queue;
    queue.push(s);
    while (!queue.empty()) {
        s = queue.front();
        queue.pop();
        
        for (int i = 0; i < s -> adjacency.size(); i++) {
            if (s -> adjacency[i] -> color == 'W') {
                s -> adjacency[i] -> color = 'G';
                cout << s -> adjacency[i] -> getId() << " ";
                s -> adjacency[i] -> dist = s -> dist + 1;
                s -> adjacency[i] -> pi = s;
                queue.push(s -> adjacency[i]);
            }
        }
        s -> color = 'B'; // 完成對 s 所有相鄰點的拜訪，s 設成黑色。
    }
}

int main(int argc, const char * argv[]) {
    // create undirected graph
    GraphNode* v0 = new GraphNode(0);
    GraphNode* v1 = new GraphNode(1);
    GraphNode* v2 = new GraphNode(2);
    GraphNode* v3 = new GraphNode(3);
    GraphNode* v4 = new GraphNode(4);
    GraphNode* v5 = new GraphNode(5);
    GraphNode* v6 = new GraphNode(6);
    GraphNode* v7 = new GraphNode(7);
    vector<GraphNode*> Graph;
    Graph.assign({v0, v1, v2, v3, v4, v5, v6, v7});
    
    v0 -> adjacency.assign({v1, v2});
    v1 -> adjacency.assign({v0, v3, v4});
    v2 -> adjacency.assign({v0, v5, v6});
    v3 -> adjacency.assign({v1, v7});
    v4 -> adjacency.assign({v1, v7});
    v5 -> adjacency.assign({v2, v7});
    v6 -> adjacency.assign({v2, v7});
    v7 -> adjacency.assign({v3, v4, v5, v6});
    
    DFS(Graph);
//    BFS(v0, 8);
//    BFS(v0);
    return 0;
}
