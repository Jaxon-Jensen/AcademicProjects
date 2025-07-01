fun createTuple(x, []) = []
  | createTuple(x, y::ys) = (x, y) :: createTuple(x, ys);

fun crossProduct ([], ys) = []
  | crossProduct (xs, []) = []
  | crossProduct (x::xs, ys) = createTuple(x, ys) @ crossProduct(xs, ys);