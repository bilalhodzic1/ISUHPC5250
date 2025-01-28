# declare x

x = []
print("add numbers 0 to 19 to x")
for i in range(20):
    x.append(i)

# print x
print(x)

print("set y to copy of x")
y = x.copy()

# print y
print(y)


print("clear x")
x.clear()

# print x
print(x)

print("add 10 twice to y")
y.append(10)
y.append(10)
print(y)
print("count of 10s (should be 3)")
print(y.count(10))

print("make z a copy of y and reverse it")
z = y.copy()
z.reverse()

print("print y and z")
print(y)
print(z)

print("insert 3 at position 6 to z")
z.insert(6, 3)

# print z
print(z)

print("add entire y list to z")
z.extend(y)

# print z
print(z)


print("remove first instance of 10 in z")
z.remove(10)

# print z
print(z)

print("pop from z")
z.pop()

# print z
print(z)

print("find and print first occurance of 7 in z")
print(z.index(7))

print("sort z")
z.sort()

# print final sorted z
print(z)
