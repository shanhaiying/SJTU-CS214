#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
//Please put this source code in the same directory with SCC.in
//And do NOT change the file name.
/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/

typedef int Rank;

struct Node{
    int nodeNum;
    vector<int> neighbors;
    Node(int nodeNum=0):nodeNum(nodeNum){}
};

void dfs(vector<Node> &graph,vector<int> &vqueue,vector<bool> &visited,int src){
    visited[src]=true;
    for(int i=0;i<graph[src].neighbors.size();i++){
        int newsrc=graph[src].neighbors[i];
        if(!visited[newsrc]) dfs(graph,vqueue,visited,newsrc);
    }
    vqueue.push_back(src);
}


void DFS(vector<Node> &graph,vector<int> &vqueue,vector<bool> &visited){
    for(int i=0;i<graph.size();i++){
        if(!visited[i]) dfs(graph,vqueue,visited,i);
    }
}

void explore(vector<Node> &graph,vector<bool> &visited,int src){
    visited[src]=true;
    for(int i=0;i<graph[src].neighbors.size();i++){
        int newsrc=graph[src].neighbors[i];
        if(!visited[newsrc]) explore(graph,visited,newsrc);
    }
}

int SCC(int n, vector<pair<int,int>>& edge) {
    vector<Node> gr(n,Node());
    vector<Node> g(n,Node());
    vector<bool> visited(n,false);

    for(int i=0;i<n;i++){
        gr[i].nodeNum=g[i].nodeNum=i;
    }
    for(int i=0;i<edge.size();i++){
        g[edge[i].first].neighbors.push_back(edge[i].second);
        gr[edge[i].second].neighbors.push_back(edge[i].first);
    }
    vector<int> vqueue;
    DFS(gr,vqueue,visited);
    for(int i=0;i<visited.size();i++) visited[i]=false;
    int scc=0;
    for(int i=vqueue.size()-1;i>=0;i--){
        if(!visited[vqueue[i]]) {explore(g,visited,vqueue[i]);scc++;}

    }
    return scc;
}
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("SCC.in");
    if(!fin) {cout<<"Can not open file.\n";return 0;}
    fin>>n>>m;
    int tmp1,tmp2;
    for(int i=0;i<m;i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    fin.close();
    int ans=SCC(n,edge);
    fout.open("SCC.out");
    fout<<ans<<'\n';
    fout.close();
    return 0;
}
