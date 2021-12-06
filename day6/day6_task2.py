start = [int(x) for x in open("input.txt").read().split(',')]
fish_categories = [0] * 9

for n in start:
    fish_categories[n] += 1

for day in range(256):
    fish_categories = fish_categories[1:] + fish_categories[0:1]
    fish_categories[6] += fish_categories[8]

print(sum(fish_categories))