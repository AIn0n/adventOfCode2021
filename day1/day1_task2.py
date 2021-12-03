with open("input.txt", "r") as f:
    data = [int(x) for x in f.read().split()]
    diffs = 0
    for x, y in zip(range(1, len(data) - 2), range(2, len(data) - 1)):
        r = range(-1, 2)
        a = sum(data[n + x] for n in r)
        b = sum(data[n + y] for n in r)
        diffs += b > a
    print(diffs)