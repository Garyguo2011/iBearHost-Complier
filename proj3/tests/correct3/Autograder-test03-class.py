class A:
	x = 0
	
	def method1(self):
		print "A's value of x is", self.x

	def __init__(self, x):
		self.x = x

anA = A(3)
anotherA = A(2)
anA.method1()
anotherA.method1()
print A.x
