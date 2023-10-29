fn1 : () void {}
fn2 : () int { return 42; }

main : () void {
    fn1 = fn2;
}