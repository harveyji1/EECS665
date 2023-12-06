callee1 : (b: bool) int {
    if (b){
        return 1;
    }
    else{
        return 0;
    }
    give b;
}

callee2 : () bool {
    return true;
}

callee3 : (a: int) void{
    a = a+1;
    give a;
}

main : () void{
    myB : bool = true;
    myA : int;
    myA = callee1(myB);
    myB = callee2();
    callee3(myA);
}