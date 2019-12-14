          // this is solution of 1553 of timus, querries on nodes
          #include <bits/stdc++.h>
          using namespace std;
          int const N = 100009;
          int const LN = 23;
          int pa[N][LN],baseArray[N],chainId[N],chainhead[N],posInbase[N];
          int depth[N],subsize[N];
          vector<int> adj[N];
          int tree[6*N];
          int ptr,chainNo;

          void build_segtree(int id,int l,int r)
          {
            if(l==r)
              tree[id] = baseArray[l];
            else
            {
              int mid = (l+r)/2;
              build_segtree(2*id,l,mid);
              build_segtree(2*id+1,mid+1,r);
              tree[id] = max(tree[2*id],tree[2*id+1]);
            }
          }

          void update_segtree(int id,int l,int r,int pos,int val)
          {
            if(l==r)
            {
              baseArray[l]+=val;
              tree[id] = baseArray[l];
            }
            else
            {
              int mid = (l+r)/2;
              if(pos<=mid)
                update_segtree(2*id,l,mid,pos,val);
              else 
                update_segtree(2*id+1,mid+1,r,pos,val);
              tree[id] = max(tree[2*id],tree[2*id+1]);
            }
          }

          int querry_segtree(int id,int l,int r,int tl,int tr)
          {
            if(tr<l || tl>r)
              return INT_MIN;
            else if(l>=tl&&r<=tr)
              return tree[id];
            else
            {
              int mid = (l+r)/2;
              return max(querry_segtree(2*id,l,mid,tl,tr),
                              querry_segtree(2*id+1,mid+1,r,tl,tr));
            }
          }

          int querry_up(int u,int v)
          {
            if(u==v)
              return baseArray[posInbase[u]];
            int uchain,vchain = chainId[v];
            int ans = INT_MIN;
            while(1)
            {
              uchain = chainId[u];
              if(uchain == vchain)
              {
                ans = max(ans,querry_segtree(1,1,ptr-1,posInbase[v],posInbase[u]));
                return ans;
              }
              ans = max(ans,querry_segtree(1,1,ptr-1,posInbase[chainhead[uchain]],posInbase[u]));
              u = pa[chainhead[uchain]][0];
            }
          }


          int LCA(int p,int q)
          {
            int log;
            if(depth[q]>depth[p])swap(p,q);
            for(log=1; 1<<log <= depth[p]; log++);
            log--;
            for(int i=log; i>=0; i--)
            {
              if(depth[p]-(1<<i)>=depth[q])p=pa[p][i];
            }
            if(p==q)return p;
            for(int i=log; i>=0; i--)
            {
              if(pa[p][i]!=-1 && pa[p][i]!=pa[q][i])
              {
                p=pa[p][i]; q=pa[q][i];
              }
            }
            return pa[p][0];
          }

          void querry(int a,int b)
          {
            int lca =LCA(a,b);
            int ans = querry_up(a,lca);
            ans = max(ans,querry_up(b,lca));
            cout << ans << '\n';
          }

          void update(int a,int addend)
          {
            update_segtree(1,1,ptr-1,posInbase[a],addend);
            return;
          }

          void hld(int v,int p)
          {
            if(chainhead[chainNo]==-1)
            {
              chainhead[chainNo] = v;
            }
            chainId[v] = chainNo;
            posInbase[v] = ptr;
            baseArray[ptr++] = 0;
            int id=-1;
            for(auto u:adj[v])
            {
              if(u!=p && (id==-1 || subsize[id] < subsize[u]))
                id = u;
            }
            if(id!=-1)
            {
              hld(id,v);
            }
            for(auto u:adj[v])
            {
              if(u!=p && u!=id)
              {
                chainNo++;
                hld(u,v);
              }
            }
          }


          void dfs(int v,int p,int d)
          {
            subsize[v] = 1;
            depth[v] = d;
            pa[v][0] = p;
            for(int u:adj[v])
            {
              if(u!=p)
              {
                dfs(u,v,d+1);
                subsize[v] += subsize[u];
              }
            }
          }


          int main()
          {
        
          int n;
          cin >> n;
          for(int i=1; i<=n-1; i++)
          {
            int aa,bb;
            cin >> aa >> bb;
            adj[aa].push_back(bb);
            adj[bb].push_back(aa);
          }
          memset(pa,-1,sizeof(pa));
          memset(chainhead,-1,sizeof(chainhead));
          ptr = 1;
          chainNo = 1;
          dfs(1,-1,0);
          hld(1,-1);
          build_segtree(1,1,ptr-1);
          for(int j=1; j<LN; j++)
          {
            for(int i=1; i<=n; i++)
              if(pa[i][j-1]!=-1)
                pa[i][j] = pa[pa[i][j-1]][j-1];
          }
    
          }