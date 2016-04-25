from display import *
from draw import *

screen = new_screen()
color= [ 0, 255, 0]

draw_line(screen, 0,0,0,0,color)
draw_line(screen, 250,0,250,0,color)

display(screen)
