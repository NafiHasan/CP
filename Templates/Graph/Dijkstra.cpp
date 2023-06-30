const int N = 3e5 + 5;

vector<int> edge[N], cost[N];   // change to long long if needed
const int inf =1e9;

struct node{
    int u; int cost;
    node(int _u, int _cost){    // constructor
        u = _u;
        cost=_cost;
    }
    bool operator < (const node& p) const { // operator overloading
        return cost > p.cost;
    }
};

void DIJKSTRA(int source, int dest){
    vector<int> dist(N, inf);

    priority_queue<node> q;    //similar to bfs, just use the priority queue instead of using queue

    q.push(node(source, 0));
    dist[source]=0;

    while(!q.empty()){
        node top =q.top();
        q.pop();
        int u=top.u;
        
        for(int i=0; i<(int)edge[u].size(); i++){
            int v=edge[u][i];
            
            if(dist[u]+cost[u][i] < dist[v]){
                dist[v]=dist[u]+cost[u][i];
                q.push(node(v,dist[v]));
            }
        }
    }
    cout << dist[dest] << "\n" ;
}
