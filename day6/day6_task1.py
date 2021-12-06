fish = [int(x) for x in open("input.txt").read().split(',')]

for day in range(80):
    fish = list(map(lambda x : x - 1, fish))
    new_fish = len(fish) - len(tuple(filter(lambda x : x > -1, fish)))
    fish = list(map(lambda x : 6 if x < 0 else x, fish))
    fish += [8] * new_fish

print(len(fish))