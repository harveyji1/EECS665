student: class{
    studentID: int;
};

fn: () int{
    hello: int = 1;
    if(hello and true){
        give hello;
    }
}

main: () void{
    fn();
}