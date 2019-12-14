// Point Update and Range Query 
// for Range update and Point query, DO update(l,x) and update(r+1,-x)
void update(int i,int val)
{
    while(i <= n)
    {
        fen[i] += val;
        i += (i&(-i));
    }
}
int querry(int i)
{
    int sum = 0;
    while(i > 0)
    {
        sum += fen[i];
        i -= (i&(-i));
    }
    return sum;
}
// Range Updates and Range Queries
// To support both range updates and range queries 
// we will use two BITs namely B1[] and B2[], initialized with zeros.
def add(b, idx, x):
    while idx <= N:
        b[idx] += x
        idx += idx & -idx

def range_add(l,r,x):
    add(B1, l, x)
    add(B1, r+1, -x)
    add(B2, l, x*(l-1))
    add(B2, r+1, -x*r)

def sum(b, idx):
    total = 0
    while idx > 0:
        total += b[idx]
        idx -= idx & -idx
    return total

def prefix_sum(idx):
    return sum(B1, idx)*idx -  sum(B2, idx)

def range_sum(l, r):
    return sum(r) - sum(l-1)
