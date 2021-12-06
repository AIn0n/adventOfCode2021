fish = [int(x) for x in open("input.txt").read().split(',')]

for day in range(80):
    new_fish = len(tuple(filter(lambda x : x == 0, fish)))
    fish = list(map(lambda x : 6 if x - 1 < 0 else x - 1, fish))
    fish.extend([8] * new_fish)

print(len(fish))