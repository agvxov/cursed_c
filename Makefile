# Add extra warnings to stress how horrid the code is
WARNINGS := -Wall -Wextra -Wpedantic
# Remove some that would show up too many times to be enjoyable
WARNINGS += -Wno-duplicate-decl-specifier -Wno-trigraphs

CFLAGS := ${WARNINGS} -trigraphs -ggdb

main: h.h.gch
	gcc ${CFLAGS} c.c

%.h.gch: detention/%.h
	gcc ${CFLAGS} $< -o ./$@

g:
	bake "tool/g().c"
	bake "tool/g(...).c"
	-diff -s -y -t <(objdump -S "tool/g().out") <(objdump -S "tool/g(...).out") > diff.txt

clean:
	-rm *.gch
	-rm *.out
	-rm diff.txt
	-rm tool/*.out
