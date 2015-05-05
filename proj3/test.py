class test:
	def __init__(self):
		self.one = 1
		self.two = 2
		self.true = True
		self.none = None
		self.string = 'hello'

	def printattr(self):
		print self.one
		print self.two
		print self.true
		print self.none
		print self.string

x = test()
print x.one
print x.two
print x.true
print x.none
print x.string
x.printattr()
