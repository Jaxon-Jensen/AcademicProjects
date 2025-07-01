fun union ([],[]) = []
   | union ([], ys) = ys
   | union (x::xs, ys) = 
        if List.exists (fn y => x = y) ys then union (xs, ys)
        else x :: union (xs,ys);