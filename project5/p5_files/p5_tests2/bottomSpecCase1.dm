p : bool = true;
f : (x : int) bool { return true; }

main : () void {
    give p + 1;           // p + 1 is an error; the write is OK
}