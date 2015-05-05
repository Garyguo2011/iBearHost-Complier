x = [1,2]
if truth(x):
	print "Yes1"
else:
	print "No1"

y = []
if truth(y):
	print "No2"
elif truth(x):
	print "Yes2"
else:
	print "No2"

if truth(None):
	print "No3"
else:
	print "Yes3"

empty::dict of [int, int] = {}
if truth(empty):
	print "No4"
elif truth({1:2}):
	print "Yes4"
else:
	print "No4"

if truth(""):
	print "No5"
elif truth("Hi"):
	print "Yes5"
else:
	print "No5"

if truth(xrange(0,0)):
	print "No6"
elif truth(xrange(0,1)):
	print "Yes6"
else:
	print "No6"

if truth(0):
	print "No 7"
elif truth((1,2)):
	print "Yes7"
else:
	print "No7"

