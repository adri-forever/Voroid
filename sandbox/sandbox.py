import matplotlib as mp
import numpy as np

def sq(x: float):
    return x*x

if __name__=='__main__':
    A: np.Array = [.25, .75]
    B: np.Array = [.75, .25]
    C: np.Array = [.5, .6]

    ABv: np.Array = B-A
    pv: np.Array = [-ABv[1], ABv[0]] # perpendicular

    M: np.Array = .5*(A+B) # midpoint
    t: float = (C[0]*(A[1] - B[1]) + C[1]*(B[0] - A[0]) - A[0]*A[1] + B[0]*B[1]) / (sq(A[1]-B[1])+sq(B[0]-A[0]))

    H: np.Array = M + t*pv
    
