#Tower of Hanoi
def solve(n,l,m,r):
    if n==1: print("Move the ring 1 from",l,"peg to",m,"peg")
    else:
        solve(n-1,l,r,m)
        print("Move the ring",n,"from",l,'peg to',m,"peg")
        solve(n-1,r,m,l)
num=int(input("Enter the Number of the disc:"))
solve(num,"left","middel","Last")        

