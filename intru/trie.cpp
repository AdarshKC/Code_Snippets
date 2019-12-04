// This is solution of Micro's House from Hackerearth
// maximum xor-subarray problem
#include <bits/stdc++.h>
using namespace std;
#define int long long
int const N = 100009;
int trie[N*33][2]; // check carefully for memory
int nxt; // initialise it with 1
void insert(int x)
{
    int v = 0;
    int t = 31;
    while(t >= 0)
    {
        int c = ((x >> t) & 1);
        if(trie[v][c] == -1)
        {
                trie[v][c] = nxt++;
        }
        v = trie[v][c];
        t--;
    }
}

// gives maximum subarray xor-sum
int find_max(int x)
{
    int v = 0;
    int t = 31;
    int ans = 0;
    while(t >= 0)
    {
        int c = ((x >> t) & 1);
        if(trie[v][c^1] != -1)
        {
                ans |= (1 << t);
                v = trie[v][c^1];
        }
        else
            v = trie[v][c];
        t--;
    }
    return ans;
}
main()
{

    // never forget to insert(0) before
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
    int T;
    cin >> T;
    while(T--)
    {
        memset(trie,-1,sizeof(trie));
        nxt = 1;
        insert(0);

        int n;
        cin >> n;
        int a[n];
        for(int i = 0; i < n; i++)
            cin >> a[i];
        int ans = 0,cur = 0;
        for(int i = 0; i < n; i++)
        {
            cur ^= a[i];
            ans = max(ans, find_max(cur));
            insert(cur);
        }
        cout << ans << '\n';
    }
}