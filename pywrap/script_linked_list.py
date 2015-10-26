from cdepo.data_structures.linked_list import *

print "Creating list"
clist = LinkedList()
print str(clist)

print "Adding 3 and 5"
clist.add(3)
clist.add(5)
print str(clist)

print "Adding 10, 20 and 30"
clist.add_many([10,20,30])
print str(clist)

print "Deleting 5"
clist.delete(5)
print str(clist)

print "Deleting 3 (list head)"
clist.delete(3)
print str(clist)

print "Deleting 30 (list tail)"
clist.delete(30)
print str(clist)

print "Deleting the remaining elements (list should be empty)"
clist.delete(10)
clist.delete(20)
print str(clist)