p : bool = true;
f : (x : int) bool { return true; }

main : () void {
    a : int;
	a = (true + 3) * 4;     // true + 3 is an error; the * is OK
}