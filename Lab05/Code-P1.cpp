#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(){
    int n;
    //ifstream file;
    //file.open("Data-P1.txt");
    //file>>n;
    cin>>n;
    unsigned t[n],w[n];
    for (int i=0;i<n;i++) {/*file>>t[i]>>w[i];*/cin>>t[i]>>w[i];}
    vector<vector<unsigned>> dp(n+1,vector<unsigned>((n<<1)+1,0x7FFFFFFF));
    for(int i=0;i<n+1;i++) for(int j=0;j<(n<<1)+1;j++) dp[i][j]=0x7FFFFFFF;
    dp[0][0]=0;
    int sum=0;
    for (int i=1;i<=n;i++){
        sum+=t[i-1];
        for(int j=0;j<=sum;j++){
            dp[i][j] = min(dp[i][j],dp[i-1][j]+w[i-1]);
            if (j>=t[i-1])
                dp[i][j]=min(dp[i][j],dp[i-1][j-t[i - 1]]);
        }
    }
    int j;
    for(j=0;j<=sum;j++){
        if (dp[n][j]<=j)
            break;
    }
    cout<<j<<endl;
    return 0;
}