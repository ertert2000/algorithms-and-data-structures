import matplotlib.pyplot as plt

sizes = []
times = []

with open("results.txt", "r") as f:
    for line in f:
        try:
            size, time = map(int, line.strip().split())
            sizes.append(size)
            times.append(time)
        except ValueError:
            continue

plt.figure(figsize=(10, 6))
plt.plot(sizes, times, marker='o', linestyle='-', color='royalblue')
plt.title("Зависимость времени выполнения от размера входа")
plt.xlabel("Размер входа")
plt.ylabel("Время выполнения (мкс)")
plt.grid(True)
plt.tight_layout()
plt.savefig("timing_plot.png")
plt.show()
