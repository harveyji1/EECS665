MyClass : class {
  x : int;
  myFunction : (param : int) int {
    give x + param;
  }
};

main : () void {
  obj : MyClass;
  result : int = obj--myFunction(5);
}