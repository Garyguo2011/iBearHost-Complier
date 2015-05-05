L = [ ( "chicken", "chick"), ( "goose", "gosling"), ( "duck", "duckling"),
      ( "cow", "calf"), ( "horse", "colt") ]

D = {"dog": " puppy"}
for d in L:
	print 1
for animal, child in L:
    print animal
    print child
    

# for animal, child in L:
#     if child == D[animal]:
#         print "The child of a", animal, "is a", child
