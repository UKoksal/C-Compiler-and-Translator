def main():
    x=5
    sum=0
    while(x!=0):
        sum=sum+1
        x=0
    b1 = 1
    b2 = 1
    if(b1 and b2):
        return sum
    else:
        return 0

# Boilerplate
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
