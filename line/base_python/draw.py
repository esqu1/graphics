from display import *

def draw_line( screen, x0, y0, x1, y1, color ):
    dx = x1 - x0
    dy = y1 - y0
    x = x0
    y = y0
    if dy >= 0:
        d = 2*dy - dx
        if dx >= dy: # Octant 1
            while x <= x1:
                plot(screen,color,x,y)
                if d > 0:
                    y += 1
                    d -= 2*dx
                x += 1
                d += 2*dy
        else:
            while y <= y1:
                plot(screen,color,x,y)
                if d < 0:
                    x += 1
                    d += 2*dy
                y += 1
                d -= 2*dx
    else:
        d = 2*dy + dx
        if -dy >= dx:
            while y <= y1:
                plot(screen,color,x,y)
                if d > 0:
                    x += 1
                    d += 2*dy
                y -= 1
                d += 2*dx
        else:
            while x <= x1:
                plot(screen,color,x,y)
                if d > 0:
                    y -= 1
                    d -= 2*dx
                x += 1
                d -= 2*dy
