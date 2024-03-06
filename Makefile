main: h.h.gch
	gcc c.c -trigraphs -Wall -Wextra -Wpedantic

%.h.gch: detention/%.h
	gcc $< -o ./$@

g:
	bake "g().c"
	bake "g(...).c"
	diff -s -y -t <(objdump -S "g().out") <(objdump -S "g(...).out") > diff.txt

clean:
	-rm *.gch
	-rm *.out
