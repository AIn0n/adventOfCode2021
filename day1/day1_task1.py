with open("input.txt", "r") as f:
    data = [int(x) for x in f.read().split()]
    print(sum(x > y for x, y in zip(data[1:],data[:-1])))