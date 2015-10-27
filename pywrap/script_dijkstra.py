from cdepo.data_structures.graph import *

dim = 32

g = matrix_graph(dim)
put_rect(g, 0,3,30,5)
put_rect(g, 2,10,32,13)
put_rect(g, 10,15,12,32)

start = 0
finish = (dim**2)-2
g.pathfind(start, finish)

