from display import *
from matrix import *
from draw import *

commands = ['line','circle','hermite','bezier','scale','translate','xrotate','yrotate','zrotate']

def parse_file( fname, points, transform, screen, color ):
    f = open(fname, 'r').read()
    l = f.split('\n')
    i = 0
    while i < len(l):
        cmd = l[i].strip()
        print cmd
        if cmd in commands:
            i += 1
            args = l[i].split()
            j = 0
            while j < len(args):
                args[j] = float(args[j])
                j+= 1
            if cmd == 'line':
                add_edge( points, args[0], args[1], args[2], args[3], args[4], args[5] )
            elif cmd == 'circle':
                add_circle( points, args[0], args[1], 0, args[2], 0.01 )
            elif cmd == 'hermite':
                add_curve( points, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], 0.01, HERMITE )
            elif cmd == 'bezier':
                add_curve( points, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], 0.01, BEZIER )
            elif cmd == 'scale':
                matrix_mult(make_scale(args[0], args[1], args[2]), transform)
            elif cmd == 'translate':
                matrix_mult(make_translate(args[0], args[1], args[2]), transform)
            elif cmd == 'xrotate':
                matrix_mult(make_rotX(args[0]), transform)
            elif cmd == 'yrotate':
                matrix_mult(make_rotY(args[0]), transform)
            elif cmd == 'zrotate':
                matrix_mult(make_rotZ(args[0]), transform)
        else:
            if cmd == 'ident':
                ident(transform)
            elif cmd == 'apply':
                matrix_mult(transform,points)
            elif cmd == 'display':
                screen = new_screen()
                draw_lines( points, screen, color )
                display(screen)
            elif cmd == 'save':
                screen = new_screen()
                draw_lines( points, screen, color )
                i += 1
                out = l[i]
                save_extension(screen,out)
            elif cmd[0] == '#':
                pass
            else:
                print "Invalid command."
        i += 1
            

