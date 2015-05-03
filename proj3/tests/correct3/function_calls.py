def hello():
	print "world"
hello()
def foo(x):
	print x
foo(1)
def bar(x::int, y::int):
	return x+y
print bar(1,1)
def foobar(x::int,y::int):
	z = x + y
	return z
print foobar(1,2)
print 1 + foobar(1,2)
def foobarbar():
	def foofoobarbar():
		print "foofoobarbar"
	foofoobarbar()
foobarbar()
