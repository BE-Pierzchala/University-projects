from random import random
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D




def Walk3D(n):
    x = [0]
    y = [0]
    z = [0]
    

    for i in range(n):
    
        dx = 2*(random() - 0.5)
        dy = 2*(random() - 0.5)
        dz = 2*(random() - 0.5)
        L = ( dx**2 + dy**2 + dz**2 ) **0.5
        
        dx = dx/L
        dy = dy/L
        dz = dz/L
        
        x.append( x[-1] + dx)
        y.append( y[-1] + dy)
        z.append( z[-1] + dz)
        
    return (x,y,z)
    
def plot(x,y,z):
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.plot(x, y, z, label='random walk')
    ax.legend()
    plt.show()