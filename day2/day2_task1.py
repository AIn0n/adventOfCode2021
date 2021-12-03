with open('input.txt', 'r') as f:
    data = [x.split() for x in f.read().split('\n')]
    data = [[dirct, int(num)] for dirct, num in data]
    sums = {'forward' : 0, 'up' : 0, 'down' : 0}
    for k, v in data:
        sums[k] += v
    print((sums['down'] - sums['up']) * sums['forward'])