fun powerSet [] = [[]]
   |powerSet (x::xs) = 
        let
            val remainingSet = powerSet xs
        in
            remainingSet @ List.map (fn xs => x::xs) remainingSet
        end;