from display import *
from draw import *

screen = new_screen()
color = [ 0, 255, 0 ]

#octant I
draw_line( screen, 0, 0, XRES - 1, YRES - 75, color )
#octant II
draw_line( screen, 0, 0, XRES - 75, YRES - 1, color )
#octant VIII
draw_line( screen, 0, YRES - 1, XRES - 1, 75, color )
#octant VII
draw_line( screen, 0, YRES - 1, XRES - 75, 0, color )


color[ GREEN ] = 0
color[ RED ] = MAX_COLOR
#octant V
draw_line( screen, XRES - 1, YRES - 1, 0, 75, color )
#octant VI
draw_line( screen, XRES - 1, YRES - 1, 75, 0, color )
#octant IV
draw_line( screen, XRES - 1, 0, 0, YRES - 75, color )
#octant III
draw_line( screen, XRES - 1, 0, 75, YRES - 1, color )


color[ BLUE ] = MAX_COLOR
color[ RED ] = 0
#y = x
draw_line( screen, 0, 0, XRES - 1, YRES - 1, color )
#y = -x
draw_line( screen, 0, YRES - 1, XRES - 1, 0, color )

color[ GREEN ] = MAX_COLOR
#horizontal
draw_line( screen, 0, YRES / 2, XRES - 1, YRES / 2, color )
#vertical
draw_line( screen, XRES / 2, 0, XRES / 2, YRES - 1, color )

display(screen)
