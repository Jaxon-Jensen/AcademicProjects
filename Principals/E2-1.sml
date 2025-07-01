fun isSuffixOf([], _) = true
  | isSuffixOf(_, []) = false
  | isSuffixOf(xs, ys) = if xs = ys orelse isSuffixOf(xs, tl ys) then true else false;
isSuffixOf ([1,2,3], [1,2,3])


fun listEqual([], _) = true
  | listEqual(x::xs, ys) = List.exists (fn y => x = y) ys andalso listEqual(xs, ys)

fun isEquivalentTo(xs, ys) =
    listEqual(xs, ys) andalso listEqual(ys, xs);
isEquivalentTo([1,3,2],[1,2,3])



fun sumPairs([]) = (0, 0)  
  | sumPairs((x, y)::rest) = (x + #1 (sumPairs rest), y + #2 (sumPairs rest));
sumPairs([(1,1),(2,3),(4,5)])



fun merge([], ys) = ys
  | merge(xs, []) = xs
  | merge(x::xs, y::ys) = if x <= y then x::merge(xs, y::ys) else y::merge(x::xs, ys);

fun mergeLists([]) = []
  | mergeLists([xs]) = xs
  | mergeLists(xs::ys::xxs) = mergeLists(merge(xs, ys)::xxs);


  fun listEqual([], _) = true
  | listEqual(x::xs, ys) = List.exists (fn y => x = y) ys andalso listEqual(xs, ys);

fun isEquivalentTo(xs, ys) = listEqual(xs, ys) andalso listEqual(ys, xs);

isEquivalentTo([1,3,2],[1,2,3])