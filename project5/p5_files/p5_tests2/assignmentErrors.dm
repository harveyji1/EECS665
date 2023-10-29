a : int;
b : bool;

fn : () void {}

func : () int {}
main : () int {
	a = true;
	a = false;
	b = 1;
	a = func();
	b = func();
	a = fn;
	b = fn;
	a = func;
	b = func;
	
}