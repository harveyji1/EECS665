Person : class{
	a : int;
	b : bool;
	fn : () bool {}
	func : (c : int, d : bool) int {}
};

main : () void 
{
	z : int; 
	t : Person;
	
	z = t--func(true, 1);
	z = t--func(1, true);
	z = t--a;
	z = t--b;
	z = t--fn();
}