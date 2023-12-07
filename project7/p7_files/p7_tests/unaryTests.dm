main : () void{
    myB : bool = true;
    myA : int = 1;
    if(!(myB)){
        myA = -1;
    }
    give myA;
    give "\n";
    give myB;
}