#Program to mimic Filter
def fake_filter(f,itr):
    r=[]
    for i in itr:
        if f(i):
            r.append(i)
    return r
l=["113","avvaa","HEllo,","hi"]
print(list(fake_filter(lambda x: x if x[0].isdigit()==False else None,l)))

n=input()
'''def myreduce(f,itr,a=None):
    if d==none:
        r=itr[0]
        for ele in itr[1:]:
            r=f(r,ele)                 
    else:
        r=d
        for ele in itr:
            r=f(r,ele) 
    return r               '''