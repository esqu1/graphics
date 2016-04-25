import math

def make_translate( x, y, z ):
    return [[1,0,0,x],
            [0,1,0,y],
            [0,0,1,z],
            [0,0,0,1]]

def make_scale( x, y, z ):
    return [[x,0,0,0],
            [0,y,0,0],
            [0,0,z,0],
            [0,0,0,0]]
    
def make_rotX( theta ):
    return [[1,0,0,0],
            [0,math.cos(math.pi * theta / 180),-math.sin(math.pi * theta / 180),0],
            [0,math.sin(math.pi * theta / 180), math.cos(math.pi * theta / 180),0],
            [0,0,0,1]]

def make_rotY( theta ):
    return [[math.cos(math.pi * theta / 180),0,-math.sin(math.pi * theta / 180),0],
            [0,1,0,0],
            [math.sin(math.pi * theta / 180),0, math.cos(math.pi * theta / 180),0],
            [0,0,0,1]]

def make_rotZ( theta ):
    return [[math.cos(math.pi * theta / 180),-math.sin(math.pi * theta / 180),0,0],
            [math.sin(math.pi * theta / 180), math.cos(math.pi * theta / 180),0,0],
            [0,0,1,0],
            [0,0,0,1]]

def new_matrix(rows = 4, cols = 4):
    m = []
    for c in range( cols ):
        m.append( [] )
        for r in range( rows ):
            m[c].append( 0 )
    return m

def print_matrix( matrix ):
    for L in matrix:
        print L

def ident( matrix ):
    L = []
    for asdf in range( len(matrix) ):
        L.append([])
    for i in xrange(len(matrix)):
        for j in xrange(len(matrix[0])):
            if i != j:
                L[i] += [0]
            else:
                L[i] += [1]
    return L

def scalar_mult( matrix, x ):
    m = new_matrix(len(matrix),len(matrix))
    for i in xrange(len(matrix)):
        for j in xrange(len(matrix[0])):
            m[i][j] *= x
    return m

#m1 * m2 -> m2
def matrix_mult( m1, m2 ):
    m = new_matrix(len(m2[0]), len(m1))
    for x in xrange(len(m1)):
        for y in xrange(len(m2[0])):
            sum = 0
            for i in xrange(len(m2)):
                sum += m1[x][i] * m2[i][y]
            m[x][y] = sum
    return m
