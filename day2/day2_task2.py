with open('input.txt', 'r') as f:
    data = [x.split() for x in f.read().split('\n')]
    data = [[dirct, int(num)] for dirct, num in data]
    hor = ver = aim = 0
    for k, x in data:
        if k == 'down': aim += x
        if k == 'up' : aim -= x
        if k == 'forward':
            hor += x
            ver += x * aim
    print(hor * ver)