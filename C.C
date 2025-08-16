// check the extension
int f(int, int, int, int) {
	return 1;
}

extern int my_extern_i1; // valid
extern "C" my_extern_i2; // valid
int my_extern() {
    extern int my_extern_i3; // valid
    // extern "C" int my_extern_i3; // invalid
}

int main(){

}
