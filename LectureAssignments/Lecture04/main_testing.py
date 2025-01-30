"""Main testing"""

import math

import demo_myfuncs

sqr = demo_myfuncs.sqrt(19562, 100)
print(f"square root of 19562 = {sqr} using demo_myfuncs")
sqr = math.sqrt(19562)
print(f"square root of 19562 = {sqr} using math library")
fac = demo_myfuncs.factorial(10)
print(f"factorial of 10 = {fac} using demo_myfuncs")
fac = math.factorial(10)
print(f"factorial of 10 = {fac} using math library")
expon = demo_myfuncs.exp(5.782)
print(f"e^5.782 = {expon} using demo_myfuncs")
expon = math.exp(5.782)
print(f"e^5.782 = {expon} using math library")
nlog = demo_myfuncs.ln(18, 100)
print(f"ln(18) = {nlog} using demo_myfuncs")
nlog = math.log(18)
print(f"ln(18) = {nlog} using math library")
