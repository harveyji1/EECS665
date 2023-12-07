main : () void{
    myB : int = 2;
    myA : int = 1;
    myC : int;
    myD : int;
    myC = myA + myB;
    myD = myC * 3;
    myB = myD / 3;
    myA = myB - 2;
    give myA;
    give "\n";
    give myB;
    give "\n";
    give myC;
    give "\n";
    give myD;
}