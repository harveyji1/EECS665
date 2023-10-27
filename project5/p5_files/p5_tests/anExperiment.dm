fn: () int{
    hello: int = 1;
    return hello;
}

f: (c: int) int{
    return 1;
}

main: () void{
    a: int;
    a = f;
    a = f(1);
    a = fn;
    f = fn();
    fn = f();
}