from matplotlib import pyplot as plt
import numpy as np

def sq(x: float):
    return x*x

def drawpoints(points):
    x: list[float] = []
    y: list[float] = []

    for point in points:
        x.append(point[0])
        y.append(point[1])
    
    plt.scatter(x, y, label = 'Points')

if __name__=='__main__':
    A = np.array([.25, .75])
    B = np.array([.75, .25])
    C = np.array([.5, .6])

    ABv = B-A
    pv = np.array([-ABv[1], ABv[0]]) # perpendicular

    M = .5*(A+B) # midpoint
    t: float = (C[0]*(A[1] - B[1]) + C[1]*(B[0] - A[0]) - A[0]*A[1] + B[0]*B[1]) / (sq(A[1]-B[1])+sq(B[0]-A[0]))

    H = M + t*pv
    
    plt.figure(0)
    drawpoints([A, B, C, M, H])
    plt.show()
    # plt
    """
    create a figure
    
    draw points A, B, M, H
    draw segment [AB]
    draw line (M,pv)
    draw segment [CH]
    write value of t as textfor
    """
