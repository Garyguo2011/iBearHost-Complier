class C:
	x = 6
	def __init__(self, x):
		self.x = x
	def getX(self):
		return self.x
	def getX(self, y):
		return self.x
	def getX(self, z):
		return "Jinge Zhang"
c = C(6)
a :: int = c.getX()
b :: int = c.getX(6)
d :: str = c.getX(6)
print a
print b
print d

