class List of [$Type]:
	L::list of $Type = []
	def get_l(self):
		return self.L
	def set_l(self, list):
		self.L = list

my_list::List of Int = List of Int()
my_list.set_l([1, 2])
print my_list.get_l()
