student: class{
    studentID: int;
};

fn: () int{
    hello: int = 1;
    myStudent: student;
    bye: bool = true;
    if(bye==hello){
        give hello;
    }
}

main: () void{
    fn();
}