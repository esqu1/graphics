from display import *
from matrix import *
import math

def add_circle( points, cx, cy, cz, r, step ):
    n = step
    start = 0
    while start <= 1:
        x0 = r*math.cos(2 * math.pi * start) + cx
        y0 = r*math.sin(2 * math.pi * start) + cy
        x1 = r*math.cos(2 * math.pi * (start + n)) + cx
        y1 = r*math.sin(2 * math.pi * (start + n)) + cy
        add_edge(points,x0,y0,cz,x1,y1,cz)
        start += n
        

def add_curve( points, x0, y0, x1, y1, x2, y2, x3, y3, step, curve_type ):
    if curve_type == HERMITE:
        add_hermite_curve(points, x0, y0, x1, y1, x2, y2, x3, y3, step)
    elif curve_type == BEZIER:
        add_bezier_curve(points, x0, y0, x1, y1, x2, y2, x3, y3, step)

def add_hermite_curve( points, x0, y0, x1, y1, x2, y2, x3, y3, step):
    xmat = generate_curve_coefs(x0,x2,x1,x3,HERMITE)[0]
    ymat = generate_curve_coefs(y0,y2,y1,y3,HERMITE)[0]
    print xmat
    print ymat
    n = step
    start = 0
    while start <= 1:
        a0 = xmat[0] * start**3 + xmat[1] * start**2 + xmat[2] * start + xmat[3]
        b0 = ymat[0] * start**3 + ymat[1] * start**2 + ymat[2] * start + ymat[3]
        a1 = xmat[0] * (start + n)**3 + xmat[1] * (start + n)**2 + xmat[2] * (start + n) + xmat[3]
        b1 = ymat[0] * (start + n)**3 + ymat[1] * (start + n)**2 + ymat[2] * (start + n) + ymat[3]
        add_edge(points,a0,b0,0,a1,b1,0)
        #print [a0,b0,a1,b1]
        start += n

def add_bezier_curve( points, x0, y0, x1, y1, x2, y2, x3, y3, step):
    xmat = generate_curve_coefs(x0,x1,x2,x3,BEZIER)[0]
    ymat = generate_curve_coefs(y0,y1,y2,y3,BEZIER)[0]
    n = step
    start = 0
    while start <= 1:
        a0 = xmat[0] * start**3 + xmat[1] * start**2 + xmat[2] * start + xmat[3]
        b0 = ymat[0] * start**3 + ymat[1] * start**2 + ymat[2] * start + ymat[3]
        a1 = xmat[0] * (start + n)**3 + xmat[1] * (start + n)**2 + xmat[2] * (start + n) + xmat[3]
        b1 = ymat[0] * (start + n)**3 + ymat[1] * (start + n)**2 + ymat[2] * (start + n) + ymat[3]
        add_edge(points,a0,b0,0,a1,b1,0)
        start += n


    

def draw_lines( matrix, screen, color ):
    if len( matrix ) < 2:
        print "Need at least 2 points to draw a line"
        
    p = 0
    while p < len( matrix ) - 1:
        draw_line( screen, matrix[p][0], matrix[p][1],
                   matrix[p+1][0], matrix[p+1][1], color )
        p+= 2

def add_edge( matrix, x0, y0, z0, x1, y1, z1 ):
    add_point( matrix, x0, y0, z0 )
    add_point( matrix, x1, y1, z1 )

def add_point( matrix, x, y, z=0 ):
    matrix.append( [x, y, z, 1] )


def draw_line( screen, x0, y0, x1, y1, color ):
    dx = x1 - x0
    dy = y1 - y0
    if dx + dy < 0:
        dx = 0 - dx
        dy = 0 - dy
        tmp = x0
        x0 = x1
        x1 = tmp
        tmp = y0
        y0 = y1
        y1 = tmp
    
    if dx == 0:
        y = y0
        while y <= y1:
            plot(screen, color,  x0, y)
            y = y + 1
    elif dy == 0:
        x = x0
        while x <= x1:
            plot(screen, color, x, y0)
            x = x + 1
    elif dy < 0:
        d = 0
        x = x0
        y = y0
        while x <= x1:
            plot(screen, color, x, y)
            if d > 0:
                y = y - 1
                d = d - dx
            x = x + 1
            d = d - dy
    elif dx < 0:
        d = 0
        x = x0
        y = y0
        while y <= y1:
            plot(screen, color, x, y)
            if d > 0:
                x = x - 1
                d = d - dy
            y = y + 1
            d = d - dx
    elif dx > dy:
        d = 0
        x = x0
        y = y0
        while x <= x1:
            plot(screen, color, x, y)
            if d > 0:
                y = y + 1
                d = d - dx
            x = x + 1
            d = d + dy
    else:
        d = 0
        x = x0
        y = y0
        while y <= y1:
            plot(screen, color, x, y)
            if d > 0:
                x = x + 1
                d = d - dy
            y = y + 1
            d = d + dx

