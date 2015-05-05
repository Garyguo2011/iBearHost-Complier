def printOnce(x::int)::int:
	print "Print", x, "once."
	return x

print 1 < printOnce(2) < 3
