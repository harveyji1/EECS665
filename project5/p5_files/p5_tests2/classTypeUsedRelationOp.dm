student : class {
	myStudentID: int;
};

fn : () int {
	hello: bool;
	hello = true;
	
	myStudent: student;
	bye : bool;
	bye = myStudent < 1;
	
}

main : () void{
	fn();
}