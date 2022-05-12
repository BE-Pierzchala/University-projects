import random
import matplotlib.pyplot as plt
from numpy import linspace

def Walk(n):
    random.seed(None)
    x = [0]
    y = [0]
    R = []
    
    for i in range(n):
    
        dx = 2*(random.random() - 0.5)
        dy = 2*(random.random() - 0.5)
        L = ( dx**2 + dy**2 ) **0.5
        
        dx = dx/L
        dy = dy/L
        
        x.append(x[-1] + dx)
        y.append(y[-1] + dy)
        
        R.append((x[-1]**2 + y[-1]**2))
    
    return (x,y,R)


def R_sq(n):
    RR = []
    for i in range(int(n**0.5)):
        (x,y,R) = Walk(n)
        RR.append(R[-1])
    return sum(RR)/len(RR)


for n in linspace(4, 90000, num = 10):
    N = int(n)
    r = R_sq(N)
    plt.scatter(N**0.5,r**0.5)
        