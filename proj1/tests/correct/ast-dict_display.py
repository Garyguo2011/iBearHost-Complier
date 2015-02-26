a = {"a" : 0, "b" : 1}
print a
b = {}
print b
for (k, v) in a.iteritems():
	b[k] = v
print b
c = {"a" : 0, "a" : 1}
print c