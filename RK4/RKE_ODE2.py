def RKE(g, x, y, z, h):
    f = lambda x,y,z : z
    k1 = h*f(x,y,z)
    l1 = h*g(x,y,z)
    
    k2 = h*f(x + h/2, y + k1/2, z + l1/2)
    l2 = h*g(x + h/2, y + k1/2, z + l1/2)
    
    k3 = h*f(x + h/2, y + k2/2, z + l2/2)
    l3 = h*g(x + h/2, y + k2/2, z + l2/2)
    
    k4 = h*f(x + h, y + k3, z + l3)
    l4 = h*g(x + h, y + k3, z + l3)
    
    y_next = y + (k1/6 + k2/3 + k3/3 + k4/6)
    z_next = z + (l1/6 + l2/3 + l3/3 + l4/6)
    
    return (y_next, z_next)


       
    




    
