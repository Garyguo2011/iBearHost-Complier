class A:
	x = 0
	def __init__(self):
		self.x = 1
	def f(self, a, b, c):
		print "should be error!"
a = A()
print a.y
