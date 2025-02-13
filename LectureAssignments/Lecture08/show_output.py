import matplotlib.pyplot as plt

xarr = []
yarr = []

with open("output.data", "r") as file:
    for line in file:
        cleanline = line.strip("()\n")
        split_coords = cleanline.split(",")
        xarr.append(float(split_coords[0]))
        yarr.append(float(split_coords[1]))

plt.plot(xarr, yarr)
plt.show()
