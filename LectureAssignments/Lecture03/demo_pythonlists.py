# declare x

x = []
# add numbers 0 to 19 to x
for i in range(20):
    x.append(i)

# print x
print(x)

# set y to copy of x
y = x.copy()

# print y
print(y)


# clear x
x.clear()

# print x
print(x)

# add 10 twice to y
y.append(10)
y.append(10)

# print count of 10s (should be 3)
print(y.count(10))

# make z a copy of y and reverse it
z = y.copy()
z.reverse()

# print y and z
print(y)
print(z)

# insert 3 at position 6 to z
z.insert(6, 3)

# print z
print(z)

# add entire y list to z
z.extend(y)

# print z
print(z)


# remove first instance of 10 in z
z.remove(10)

# print z
print(z)

# pop from z
z.pop()

# print z
print(z)

# find and print first occurance of 7 in z
print(z.index(7))

# sort z
z.sort()

# print final sorted z
print(z)
