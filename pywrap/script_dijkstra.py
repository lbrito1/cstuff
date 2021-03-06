import matplotlib.pyplot as plt
from cdepo.data_structures.graph import *

dim = 32

g = matrix_graph(dim)
put_rect(g, 0,3,30,5)
put_rect(g, 2,10,32,13)
put_rect(g, 10,15,12,32)

start = 0
finish = (dim**2)-2
dists = g.pathfind(start, finish)

# plt.imshow(g.bgfx_mat(), interpolation='nearest', cmap='Oranges')
# plt.show()

plt.imshow(g.dist_mat(dists), interpolation='nearest', cmap='gnuplot')
plt.show()
