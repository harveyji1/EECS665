p : bool = true;
f : (x : int) bool { return true; }

main : () void {
    w : int;
	w = true + "hello";      // one error for each of the non-int operands of the +

    x : int;
    x = 1 + f(true);         // one for the bad arg type and one for the 2nd operand of the +

    y : bool;
	y = f(1, 2);            // one for the wrong number of args and one for calling a function which is supposed to return a value in this context

    
}
