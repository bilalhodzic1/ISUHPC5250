import matplotlib.pyplot as plt

xarr = []
yarr = []
xarr2 = []
yarr2 = []
with open("output.data", "r") as file:
    for line in file:
        cleanline = line.strip("()\n")
        split_coords = cleanline.split(",")
        xarr.append(float(split_coords[0]))
        yarr.append(float(split_coords[1]))
with open("output2.data", "r") as file:
    for line in file:
        cleanline = line.strip("()\n")
        split_coords = cleanline.split(",")
        xarr2.append(float(split_coords[0]))
        yarr2.append(float(split_coords[1]))


plt.plot(xarr, yarr)
# plt.plot(xarr2, yarr2)
plt.show()
