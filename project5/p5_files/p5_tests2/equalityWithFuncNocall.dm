fn : () int {
    return 42;
}

main : () void {
    a : bool;
	a = (fn == 42);
}
