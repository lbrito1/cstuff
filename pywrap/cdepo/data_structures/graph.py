from cdepo import *

def intref(value):
	return ct.byref(ct.c_int(value))

def matrix_graph(m):
	g = Graph(libgraph.build_matrix_graph(m**2))
	g.bgfx = libutil.create_bgfx(m, m)
	libgraph.clear_graph(g.cgraph, 1)
	# libgraph.put_wgt_rect(g.cgraph, 0, 0, m, m, 1)
	return g

def put_rect(g, x1, y1, x2, y2):
	libgraph.put_wgt_rect(g.cgraph, x1, y1, x2, y2, 100)

class Graph():
	def __init__(self, graph = None):
		self.cgraph = None
		if graph: self.cgraph = graph
		self.bgfx = None

	def pathfind(self, start, end):
		st_str = ct.c_char('S')
		fs_str = ct.c_char('F')
		libgraph.set_vertex(self.cgraph, start, ct.byref(st_str))
		libgraph.set_vertex(self.cgraph, end, ct.byref(fs_str))
		d = self.dijkstra(0, -1)
		libutil.clean_burger(self.bgfx)
		libgraph.print_trace(self.bgfx, self.cgraph, d, start, end)
		libgraph.draw_vertices_spec(self.cgraph, self.bgfx, 1);
		libutil.print_burger(self.bgfx)

	def dijkstra(self, start, end):
		d = libgraph.dijkstra(self.cgraph, start, end)
		libgraph.print_path(self.cgraph, d)
		return d

	def __str__(self):
		if not self.bgfx: 
			return "GFX not initialized!"
		libgraph.print_graph(self.cgraph, self.bgfx)	
		libgraph.print_vertex_status(self.cgraph, self.bgfx);
		return ""

