(* =========================================================================================================== *)
structure Model =

struct 

exception runtime_error;

fun getLeaf( term ) = CONCRETE.leavesToStringRaw term

(* For your typeChecker you may want to have a datatype that defines the types 
  (i.e., integer, boolean and error) in your language. *)
datatype types = INT | BOOL | ERROR;


(* It is recommended that your model store integers and Booleans in an internal form (i.e., as terms belonging to
   a userdefined datatype (e.g., denotable_value). If this is done, the store can be modeled as a list of such values.
*)
datatype denotable_value =  Boolean of bool 
                          | Integer of int;


type loc   = int
type env   = (string * types * loc) list
type store = (loc * denotable_value) list


(* The model defined here is a triple consisting of an environment, an address counter, and a store. The environment
   and the store are lists similar to what we have used in class. The address counter serves as an implementation of
   new(). Note that, depending on your implementation, this counter either contains the address of (1) the
   next available memory location, or (2) the last used memory location -- it all depends on when the counter is 
   incremented. *)
val initialModel = ( []:env, 0:loc, []:store )

fun error msg = ( print msg; raise runtime_error )

fun accessEnv1(varName:string, []) = (ERROR, ~1)
  | accessEnv1(varName, (name, t, loc)::rest) = if varName = name then (t, loc)
                                             else accessEnv1(varName, rest);

fun accessEnv(id1, (env, loc, s)) =
  let
      val msg = "Error: accessEnv " ^ id1 ^ " not found."

      fun aux [] = error msg
        | aux ((id, t, loc)::env) = 
              if id1 = id then (t, loc)
              else aux env
  in
      aux env
  end


fun accessStoreList(_:loc, []) = error "Error: accessStore variable not initialized"
    | accessStoreList(loc:loc, ((l, v)::rest):store) = 
        if loc = l then v
        else accessStoreList(loc, rest)

fun accessStore(_:loc, (_:env, _:loc, []:store)) = error "Error: accessStore variable not initialized"
  | accessStore(loc:loc, (env:env, loc_l:loc, store:store)) = accessStoreList(loc:loc, store:store)

fun accessStore2(loc:loc, []) = (ERROR, false)
  | accessStore2(loc, (l, v)::rest) = if loc = l then (v, true)
                                     else accessStore2(loc, rest)


fun updateEnv(varName:string, varType:types, (env:env, loc:loc, store:store)) = ((varName, varType, loc)::env:env, loc + 1:loc, store:store)

fun updateStoreList([], (x, y)) = [(x, y)]:store
  | updateStoreList((x1, y1)::storeList, (x2, y2)) = 
    if x1 = x2 then (x2, y2)::storeList
    else (x1, y1)::updateStoreList(storeList, (x2, y2))

fun updateStore(loc:loc, newValue, (env:env, loc_1:loc, store:store)) = (env, loc_1, updateStoreList(store, (loc, newValue)))
                     
fun getLoc1(varName:string, []) = ~1 
  | getLoc1(varName, (name, _, l)::rest) = if varName = name then l
                                       else getLoc1(varName, rest)

fun getLoc(types:types, loc:loc) = loc
                                       
fun getType2(varName:string, []) = ERROR
  | getType2(varName, (name, t, _)::rest) = if varName = name then t
                                           else getType2(varName, rest)

fun getType(types:types, loc:loc) = types

fun getInt(Integer value) = value
    | getInt(_) = error "Error: getInt incorrect type"
    
fun getBool(Boolean value) = value
    | getBool(_) = error "Error: getInt incorrect type"

fun showEnv([]) = ()
  | showEnv((name, t, l)::rest) = 
                              let 
                                    val _ = print ("Variable Name: " ^ name ^ "\n")
                                    val _ = if t = INT then print "Type: INT\n"
                                            else if t = BOOL then print "Type: BOOL\n"
                                            else print "Type: ERROR\n"
                                    val _ = print("Location: " ^ Int.toString(1) ^ "\n\n")
                              in 
                                    showEnv(rest)
                              end
                                       
                                       
                                       
(* =========================================================================================================== *)
end; (* struct *) 












