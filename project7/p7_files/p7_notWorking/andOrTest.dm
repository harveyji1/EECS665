main : () bool{
    myFalse : bool = false;
    myTrue : bool = true;
    myAnd : bool = myTrue and myFalse;
    myOr : bool = myTrue or myFalse;
    give myTrue;
    give "\n";
    give myOr;
}