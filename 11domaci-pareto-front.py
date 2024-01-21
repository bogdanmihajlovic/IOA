import matplotlib.pyplot as plt

# Read coordinates from all.txt
all_coordinates = []
with open("all.txt", "r") as all_file:
    for line in all_file:
        x, y = map(float, line.split())
        all_coordinates.append((x, y))

# Read Pareto-optimal coordinates from pareto.txt
pareto_coordinates = []
with open("pareto.txt", "r") as pareto_file:
    for line in pareto_file:
        x, y = map(float, line.split())
        pareto_coordinates.append((x, y))

# Plot all coordinates in blue
all_x, all_y = zip(*all_coordinates)
plt.scatter(all_x, all_y, color='blue', label='All Coordinates')

# Plot Pareto-optimal coordinates in red
pareto_x, pareto_y = zip(*pareto_coordinates)
plt.scatter(pareto_x, pareto_y, color='red', label='Pareto-optimal Coordinates')

# Set labels and title
plt.xlabel('H()')
plt.ylabel('R()')
plt.title('All and Pareto-optimal Coordinates')

# Show legend
plt.legend()

# Show the plot
plt.show()
