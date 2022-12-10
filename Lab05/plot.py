import sys
import matplotlib.pyplot as plt

comparisons = []
movements = []
with open(sys.argv[1], "r") as f:
    for line in f:
        stats = line.split()
        comparisons.append(int(stats[0]))
        movements.append(int(stats[1]))

plt.tick_params(left = False)

figure1, axis = plt.subplots(1,2)
axis[0].plot(comparisons[len(comparisons)//2 : ])
axis[0].set_title("Comparison Cost")
axis[1].plot(movements[: len(movements)//2])
axis[1].set_title("Pointer Update Cost")
plt.savefig(sys.argv[2])
