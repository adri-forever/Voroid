from matplotlib import pyplot as plt
import numpy as np

def sq(x: float):
    return x*x

def drawpoints(points):
    x: list[float] = []
    y: list[float] = []
    labels: list[str] = []
    for point in points:
        x.append(point[1][0])
        y.append(point[1][1])
        labels.append(point[0])

    plt.scatter(x, y, label = 'Points')
    
    for point in points:
        plt.annotate(point[0], point[1]+.01, textcoords='data')

def drawlines(lines):

    for line in lines:
        pass

if __name__=='__main__':
    A = np.array([.25, .75])
    B = np.array([.75, .25])
    C = np.array([.5, .6])

    ABv = B-A
    pv = np.array([-ABv[1], ABv[0]]) # perpendicular

    M = .5*(A+B) # midpoint
    t: float = (C[0]*(A[1] - B[1]) + C[1]*(B[0] - A[0]) + A[0]*B[1] - A[1]*B[0]) / (sq(A[1]-B[1])+sq(B[0]-A[0]))

    Mp = M + pv#/pow(pv[0]*pv[0]+pv[1]*pv[1], .5)

    H = M + t*pv
    
    plt.figure(0)
    drawpoints([('A', A), ('B', B), ('C', C), ('M', M), ('M\'', Mp), ('H', H)])
    drawlines([(['[AB]', A, B]), ('(M,pv)', M, M+pv)])
    plt.gca().set_aspect('equal')
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
