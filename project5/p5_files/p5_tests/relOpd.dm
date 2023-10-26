student: class{
    myStudent: int;
};

fn: () int{
    hello: bool = true;
    if(hello<1){
        give hello;
    }
    myStudent: student;
    bye: bool = myStudent < 1;
}

main: () void{
    fn();
}