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

z = sqrt(19562, 100)
print(z)
fac = factorial(7)
print(fac)
