main:
	gcc c.c -trigraphs -Wall -Wextra -Wpedantic

g:
	bake "g().c"
	bake "g(...).c"
	diff -s -y -t <(objdump -S "g().out") <(objdump -S "g(...).out") > diff.txt

clean:
	rm *.out
