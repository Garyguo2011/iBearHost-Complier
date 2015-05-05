x::int = 4
while truth(x):
    print x
    x = x - 1
    if not x:
        break
else:
    print "Done"

