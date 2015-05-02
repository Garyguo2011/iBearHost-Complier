class C:
    y = 6

    def __init__(self):
        pass
    def a(self, x):
        print self.y
    def b(self, z):
        print "Jinge Zhang"
    def c(self):
        d = self.y
        print d

obj = C()
obj.a(1)
obj.b(2)
obj.c()
