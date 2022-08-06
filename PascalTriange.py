from math import factorial

def spaces(n):
    for i in  range(n):
        print(end=" ")
def ncr(n,r):
    t=factorial(n)//(factorial(r)*factorial(n-r))
    return t
def ele(i):
    t=i
    for j in range(0,i+1):
        print(ncr(t,j),end=" ")

n=int(input("Enter number of rows:"))

for i in range(0,n):
    spaces(n-i+1)
    ele(i)
    print()

