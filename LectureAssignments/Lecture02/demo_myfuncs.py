def sqrt(x, kmax):
    guess = x
    for i in range(kmax):
        guess = 0.5 * (guess + (x/guess))
    return guess

def factorial(x):
    if(x == 0):
        return 1
    
    s = 1
    for i in range(1,x):
        s = s * (i+1)
    return s

def exp(x):
    e = 2.7182818284590451
    x_0 = int(round(x))
    z = x - x_0
    e_to_z = 0
    for i in range(10):
        val_to_add = ((z**i)/(factorial(i)))
        print(f"Iter {i} " + str(val_to_add))
        e_to_z = e_to_z + val_to_add
    print("e_to_z" + str(e_to_z))
    return (e**x_0) * (e_to_z)

z = sqrt(19562, 100)
#print(z)
fac = factorial(10)
#print(fac)
expon = exp(5.782)
print(expon)
