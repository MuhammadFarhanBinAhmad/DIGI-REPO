GCC_OPTIONS = -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Wconversion -Werror -Werror=vla
OBJS = qdriver.o q.o
EXEC = q.out

$(EXEC) : $(OBJS)
	gcc $(GCC_OPTIONS) $(OBJS) -o q.out
	
qdriver.o : qdriver.c q.h
	gcc $(GCC_OPTIONS) -c qdriver.c -o qdriver.o
	
q.o : q.c q.h
	gcc $(GCC_OPTIONS) -c q.c -o q.o

clean:
	rm $(OBJS) $(EXEC)

test:
	gcc -Wall -Werror -Wextra -Wconversion -Wstrict-prototypes -pedantic-errors -std=c11 -DUSE_STRING -o q.out qdriver.c q.c my_string.c
	./q.out > actual-output.txt

final:
	gcc -Wall -Werror -Wextra -Wconversion -Wstrict-prototypes -pedantic-errors -std=c11 -o q.out qdriver.c q.c my_string.c
	./q.out > actual-output.txt

compare:
	diff -y --strip-trailing-cr --suppress-common-lines actual-output.txt expected-output.txt
	