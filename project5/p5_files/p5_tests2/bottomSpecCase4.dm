p : bool = true;
f : (x : int) bool { return true; }

main : () void {
    c:bool;
    c = f("a" * 4);             // "a" * 4 is an error; the call is OK
}