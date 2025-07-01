fun finiteListRepresentation (f,n) = 
   let  
        fun funHelper 0 acc = acc
           |funHelper n acc = funHelper(n-1) ((n , f n) :: acc)
    in
        funHelper n []
    end;