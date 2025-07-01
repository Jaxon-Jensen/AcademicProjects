fun alternate ([],[]) = []
   | alternate (x::xs, y::ys) = x :: y :: alternate (xs,ys);