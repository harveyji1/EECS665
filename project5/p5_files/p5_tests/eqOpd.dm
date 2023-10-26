student: class{
    studentID: int;
};

fn: () int{
    hello: int = 1;
    myStudent: student;
    if(myStudent==1){
        give hello;
    }
}

main: () void{
    fn();
}