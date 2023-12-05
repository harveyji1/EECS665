fn1 : (arg1: int) void{
    a: int;
    a = arg1;
    give a;
    give '/n';
}

fn2: () void{
    give "test";
    give '/n';
}

fn3: () void{
    c: bool;
    c = true;
    give c;
}

main : () int{
    fn1(3);
    fn2();
    fn3();
}