L = [ ( "chicken", "chick"), ( "goose", "gosling"), ( "duck", "duckling"),
      ( "cow", "calf"), ( "horse", "colt") ]

D::dict of [str, str] = {}
for animal, child in L:
    D[animal] = child

for animal, child in L:
    if child == D[animal]:
        print "The child of a", animal, "is a", child
