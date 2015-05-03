<<<<<<< HEAD
class C:
    def __init__(self):
        pass

    def g (self):
        return 6

vg::(C)->int = C.g

anC::C = C()

print vg(anC)

List = [C.g]

vg = List[0]

print vg(anC)
=======
def foo (x::int):
  def bar (y::str):
    print y
  print x
  bar("hi")
foo(5)
>>>>>>> 031c56e3b54b586c9770c7dea9d591d81187e8fd
