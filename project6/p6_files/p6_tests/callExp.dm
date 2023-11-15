callee1 : (b: bool) int {
    if (b){
        return 1;
    }
    else{
        return 0;
    }
}

callee2 : () bool {
    return true;
}

callee3 : (a: int) void{
    a = a+1;
}

caller : () void{
    myB : bool = true;
    myA : int;
    myA = callee1(myB);
    myB = callee2();
    callee3(myA);
}