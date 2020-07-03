#include<bits/stdc++.h>
using namespace std;
const int maxn=123456789;
struct node{
    int to;
    int cap;
    int coc;
    int cost;
};
vector<node>data[50005];
int dx[50005],pre1[50005],pre2[50005],incf[50005],n,m,s,t,ans,maxf;
bool inq[50005];
void add(int u,int v,int w,int f){
    data[u].push_back((node){v,w,int(data[v].size()),f});
    data[v].push_back((node){u,0,int(data[u].size()-1),-f});
}
bool test(){
    fill(dx+1,dx+n+1,maxn);
    queue<int>q;
    memset(inq,0,sizeof(inq));
    q.push(s);
    dx[s]=0;
    inq[s]=1;
    incf[s]=maxn;
    while(!q.empty()){
        int now=q.front();
        inq[now]=0;
        q.pop();
        for(int i=0;i<data[now].size();i++){
            node &tmp=data[now][i];
            if(tmp.cap>0&&tmp.cost+dx[now]<dx[tmp.to]){
                dx[tmp.to]=dx[now]+tmp.cost;
                incf[tmp.to]=min(incf[now],tmp.cap);
                pre1[tmp.to]=now;
                pre2[tmp.to]=i;
                if(!inq[tmp.to]){
                    inq[tmp.to]=1;
                    q.push(tmp.to);
                }
            }
        }
    }
    return dx[t]!=maxn;
}
void update(){
    int x=t;
    while(x!=s){
        int y=pre1[x];
        int i=pre2[x];
        data[y][i].cap-=incf[t];
        data[x][data[y][i].coc].cap+=incf[t];
        x=y;
    }
    maxf+=incf[t];
    ans+=dx[t]*incf[t];
}
void MCMF(){
    while(test()){
        update();
    }
}

int main(){
    ifstream file;
    file.open("MCMF.in");
    file>>n>>m>>s>>t;
    for(int i=1;i<=m;i++){
        int u,v,w,f;
        file>>u>>v>>w>>f;
        add(u,v,w,f);
    }
    file.close();
    MCMF();
    cout<<maxf<<" "<<ans<<endl;
}