# Add extra warnings to stress how horrid the code is
WARNINGS := -Wall -Wextra -Wpedantic
# Remove some that would show up too many times to be enjoyable
WARNINGS += -Wno-duplicate-decl-specifier -Wno-trigraphs

main: h.h.gch
	gcc ${WARNINGS} c.c -trigraphs

%.h.gch: detention/%.h
	gcc ${WARNINGS} $< -o ./$@

g:
	bake "tool/g().c"
	bake "tool/g(...).c"
	-diff -s -y -t <(objdump -S "tool/g().out") <(objdump -S "tool/g(...).out") > diff.txt

clean:
	-rm *.gch
	-rm *.out
	-rm diff.txt
	-rm tool/*.out
