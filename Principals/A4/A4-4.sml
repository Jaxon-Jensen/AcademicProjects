fun intersect ([], ys) = []
   | intersect (x::xs, ys) =
       if List.exists (fn y => x = y) ys then x :: intersect (xs, ys)
       else intersect (xs, ys)

fun multiSetIntersection [] = []
  | multiSetIntersection [xs] = xs
  | multiSetIntersection (xs::xss) = intersect (xs, multiSetIntersection xss);