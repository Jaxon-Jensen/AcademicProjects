fun update(flr, (x,y)) =
    let
        fun updateHelper ([], (x,y) ) = [(x,y)]
          | updateHelper ((a,b) :: rest, (x,y)) = 
                if a = x then (x,y) :: rest
                else (a,b) :: updateHelper(rest,(x,y))
    in
        updateHelper( flr , (x,y) )
    end;