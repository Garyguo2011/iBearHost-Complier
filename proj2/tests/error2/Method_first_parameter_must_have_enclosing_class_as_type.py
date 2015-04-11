class A:
	x = 0
	def __init__(self):
		self.x = 1
		print 1
	def f(a, b, c):
		print "should be error!"
a = A()
