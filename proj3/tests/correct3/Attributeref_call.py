class C:
	x = 6
	def __init__(self, x):
		self.x = x
	def getX(self):
		return self.x
	def getX(self, y):
		return self.x
c = C(6)
print c.getX()
print c.getX(6)
