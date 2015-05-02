class Hello:
	x = 5
	y = "haha"
	def __init__(self, param):
		self.x = param

	def set_x(self, param):
		self.x = param

	def set_y(self, param):
		self.y = param

world = Hello(6)
print world.x
world.set_x(7)
print world.x
world.set_y("foo")
print world.y
