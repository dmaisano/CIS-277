import numpy as np
from scipy.optimize import linprog

"""
use python readfile to read
PlusInput 
MinusInput 
"""
PlusInput = A[:][0:2]
MinusInput = B[:][0:2]
p1 = len(PlusInput)
q1 = len(PlusInput[0])
p2 = len(MinusInput)
q2 = len(MinusInput[0])
q = q1
p = 30
r = 30
Ain = PlusInput[0:p][:]
Bin = MinusInput[0:r][:]
A1 = np.concatenate([-Ain, np.ones([p, 1]), -np.eye(p), np.zeros([p, r])], axis=1)
A2 = np.concatenate([Bin, -np.ones([r, 1]), np.zeros([r, p]), -np.eye(r)], axis=1)
A3 = np.concatenate(
    [np.zeros([p, q]), np.zeros([p, 1]), -np.eye(p), np.zeros([p, r])], axis=1
)
A4 = np.concatenate(
    [np.zeros([r, q]), np.zeros([r, 1]), np.zeros([r, p]), -np.eye(r)], axis=1
)
A = np.concatenate([A1, A2, A3, A4], axis=0)

C = np.concatenate(
    [
        np.zeros([1, q]),
        np.zeros([1, 1]),
        (1.0 / p) * np.ones([1, p]),
        (1.0 / r) * np.ones([1, r]),
    ],
    axis=1,
)
b = np.concatenate([-np.ones([1, p + r]), np.zeros([1, p + r])], axis=1)
res = linprog(C, A_ub=A, b_ub=b)
print(res)
