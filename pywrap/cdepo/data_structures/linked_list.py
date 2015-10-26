from cdepo import *

def intref(value):
	return ct.byref(ct.c_int(value))

class LinkedList():
	def __init__(self):
		self.ll = libdata.new_list(libutil.compare_integer, ct.sizeof(ct.c_int))

	def add(self, value):
		libdata.add_ll(self.ll, intref(value))

	def add_many(self, values):
		for v in values: self.add(v)

	def contains(self, value):
		return libdata.search_ll(self.ll, intref(value))

	def delete(self, value):
		libdata.delete_ll(self.ll, intref(value))

	def __str__(self):
		libdata.print_ll(self.ll)
		return ""

	def free(self):
		libdata.delete_linked_list(self.ll)