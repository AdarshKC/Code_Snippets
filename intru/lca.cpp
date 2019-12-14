
int const N=200003;
vector<int> adj[N];
int T[N],P[N][18],d[N];
bool visited[N];

void dfs(int v)
{
  visited[v]=1;
  for(int u:adj[v])
  {
    if(!visited[u])
    {
      T[u]=v;
      d[u]=d[v]+1;
      dfs(u);
    }
  }
}
void preprocess()
{
  for(int i=0; i<N; i++)
  {
    for(int j=0; 1<<j<N; j++)P[i][j]=-1;
  }
  for(int i=0; i<N; i++)P[i][0]=T[i];

  for(int j=1; 1<<j<N; j++)
  {
    for(int i=0; i<N; i++)
    {
      if(P[i][j-1]!=-1)P[i][j]=P[P[i][j-1]][j-1];
    }
  }
}

int lca(int p,int q)
{
  int log;
  if(d[q]>d[p])swap(p,q);
  for(log=1; 1<<log <= d[p]; log++);
  log--;
  for(int i=log; i>=0; i--)
  {
    if(d[p]-(1<<i)>=d[q])p=P[p][i];
  }
  
  if(p==q)return p;
  for(int i=log; i>=0; i--)
  {
    if(P[p][i]!=-1&&P[p][i]!=P[q][i])
    {
      p=P[p][i]; q=P[q][i];
    }
  }
  return T[p];
}
int main()
{ 
    int n;
    cin>>n;
    int aa,bb;
    for(int i=0; i<n-1; i++)
    {
    cin>>aa>>bb;
    aa--;bb--;
    adj[aa].push_back(bb);
    adj[bb].push_back(aa);
    }
    dfs(0);
    preprocess();
    cout<<lca(0,3)<<endl;
    return 0;
}
