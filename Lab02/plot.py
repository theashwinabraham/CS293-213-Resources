import matplotlib.pyplot as plt
import numpy as np


y = []

with open('results.txt', 'r') as f:

    lines = f.readlines()

    for line in lines[1:]:
        y.append(int(line))

x = [ind for ind, _ in enumerate(lines[1:])]

plt.bar(x, y, width=0.8, align='center')
plt.ylabel('Elements')
plt.title("Hash Function")
plt.savefig("Hash.png")
