p : bool;
f : (x : int) bool { return true; }

main : () void {
    d : int;
    d = 1 + p();                 // p() is an error; the + is OK
}