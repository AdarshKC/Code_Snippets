void build(int id,int l,int r)
{
    if(l==r)tree[id]=make_data(arr[l]);
    else
    {
        int mid=(l+r)/2;
        build(2*id,l,mid);
        build(2*id+1,mid+1,r);
        tree[id]=combine(tree[2*id],tree[2*id+1]);
    }
}
void update(int id,int l,int r,int pos,int val)
{
    if(l==r)
    {
        tree[id]=make_data(val);
    }
    else
    {
        int mid=(l+r)/2;
        if(pos<=mid)update(2*id,l,mid,pos,val);
        else update(2*id+1,mid+1,r,pos,val);
        tree[id]=combine(tree[2*id],tree[2*id+1]);
    }
}
data querry(int id,int l,int r,int tl,int tr)
{
    if(tl>r||tr<l)return make_data(-1); // change needed here
    if(l>=tl&&r<=tr)return tree[id];
    int mid=(l+r)/2;
    return combine(querry(2*id,l,mid,tl,tr),querry(2*id+1,mid+1,r,tl,tr));
}
