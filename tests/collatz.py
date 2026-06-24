n = int(input())

while(n != 1):
    if n & 1:
        n = 3*n + 1
        print(n)
    else:
        n //= 2
        print(n)