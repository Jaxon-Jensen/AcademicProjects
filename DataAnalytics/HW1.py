import numpy as np
import scipy as sc
import matplotlib as mp
import pandas as pa
import sklearn as scl
import xlrd as x
import mlxtend as mx

print('numpy version', np.__version__)
print('scipy version', sc.__version__)
print('matplotlib version', mp.__version__)
print('pandas version', pa.__version__)
print('sklearn version', scl.__version__)
print('xlrd version', x.__version__)
print('mlxtend version', mx.__version__, '\n\n\n')

#program (part 3)
while True:
    try:
        x = float(input("Please enter a positive real number: "))
    except ValueError:
        print("ERROR: Invalid entry")
        continue
    else:
        if x < 0:
            print("ERROR: Number entered is not positive")
            continue
        break

while True:
    try:
        y = int(input("Please enter a positive integer: "))
    except ValueError:
        print("ERROR: Invalid entry")
        continue
    else:
        if y < 1:
            print("ERROR: Number entered is not positive")
            continue
        break
    
print(f'\n{x} ** {y} = ', x**y)
print(f'log2({x}) = ', np.log2(x))
print(f'log2({y}) = ', np.log2(y))