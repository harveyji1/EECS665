p : bool = true;
f : (x : int) bool { return true; }

fnVoid : () void {
        return 3 + true;        // in a void function: one error for the 2nd operand to + and one for returning a value
    }

main : () void {
    
    
    fnVoid();
}
