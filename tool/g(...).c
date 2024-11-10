// @BAKE gcc -g -O0 "$@" -o "$*.out" -Wall -Wpedantic

g(...) {
	return 2;
}

main () {
	g(4, 3, 2);
}
