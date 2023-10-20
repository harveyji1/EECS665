Person : class {
    age : int;
    
};

main : () int {
    a : Person;
    b : int = a--age;
    return a--age;
}