import ctypes as ct
from pdb import set_trace as bp
libutil = ct.CDLL('shared/utils.so')
libdata = ct.CDLL('shared/data_structures.so')
libsort = ct.CDLL('shared/sorting.so')
libgraph = ct.CDLL('shared/graphs.so')
__all__ = ['ct', 'bp', 'libutil', 'libdata', 'libsort', 'libgraph']