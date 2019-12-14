int const N=1e3+9;
int parent[N],size[N];
void make_set(int v)
{
    parent[v]=v;
    size[v]=1;
}
int find_set(int v)
{
    if(parent[v]==v)return v;
    else return parent[v]=find_set(parent[v]);
}
void set_unite(int x,int y)
{
    int a=find_set(x);
    int b=find_set(y);
    if(a!=b)
    {
        if(size[a]<size[b])swap(a,b);
        parent[b]=a;
        size[a]+=size[b];
    }
}