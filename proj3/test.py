def foo (x::int):
  def bar (y::str):
    print y
  print x
  bar("hi")
foo(5)
