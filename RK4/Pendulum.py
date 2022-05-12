import matplotlib.pyplot as plt
import math
from RKE_ODE2 import RKE

theta = [0]
theta_dot = [0]

x = [math.cos(theta[-1])]
y = [1 - math.sin(theta[-1])]

time = [0]
h = 0.001


def update():
    def g(time, theta, theta_dot):
        return 9.81*math.cos(theta)
    theta_new = RKE(g, time[-1], theta[-1], theta_dot[-1], h) [0]
    theta_dot_new = RKE(g, time[-1], theta[-1], theta_dot[-1], h) [1]
    
    if theta_new > math.pi/2:
        theta_dot_new = - theta_dot[-1]
        theta_new = RKE(g, time[-1], theta[-1], theta_dot_new, h) [0]
    theta.append(theta_new)
    theta_dot.append(theta_dot_new)


for i in range(1000):
    time.append(time[-1] + h)
    update()
    x.append(  math.cos(theta[-1]) )
    y.append(1 - math.sin(theta[-1]) )

plt.figure(0)
plt.scatter(time, theta, s = 0.1)
plt.scatter(time, theta_dot, s = 0.1)

plt.savefig('results.jpg')

plt.figure(1)
plt.xlim(0,2)
plt.ylim(0,2)
plt.plot(x,y)

s = []
for i in range(len(x)):
    s.append(x[i]**2 + (1 - y[i])**2)
