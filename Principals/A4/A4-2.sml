fun minus ([],[]) = []
   | minus (xs, []) = xs
   | minus ([], ys) = []
   | minus (x::xs, y::ys) = 
        if x = y then minus (xs, ys)
        else if x > y then minus(x::xs, ys)
        else x :: minus (xs,y::ys);