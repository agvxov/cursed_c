// @BAKE gcc -g -O0 "$@" -o "$*.out"

g() {
	return 2;
}

main () {
	g(4, 3, 2);
}
