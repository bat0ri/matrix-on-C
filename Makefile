CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -g
SOURCES = s21_matrix.c
OBJECTS = $(SOURCES:.c=.o)
TEST_SOURCES = tests/*.c
OS=$(shell uname -s)


ifeq ($(OS), Darwin)
	TEST_LIBS = -lcheck
	HTML_CREATE=lcov -t a.out -o report.info -c -d .; genhtml -o report report.info
else
	TEST_LIBS = -lcheck -lsubunit -pthread -lrt -lm
	HTML_CREATE=gcov -b -l -p -c s21_string.gcno; gcovr -g -k -r . --html --html-details -o report.html; mv report.s21_string.c.html report.html
endif

all: clean gcov_report

s21_matrix.a: clean $(OBJECTS)
	ar -rcs s21_matrix.a $(OBJECTS)
	rm -f *.o

test: $(TEST_SOURCES) s21_matrix.a
	$(CC) $(CFLAGS) $(TEST_SOURCES) $(SOURCES) -o test $(TEST_LIBS) -L. --coverage
	./test

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt test.info test.dSYM *.out *.gcov
	clang-format -i *.c *.h
	rm -rf .clang-format

check: test
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
	clang-format -n *.c *.h
ifeq ($(OS), Darwin)
	leaks -atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif

gcov_report: test
	gcov -b -l -p -c *.gcno; gcovr -g -k -r . --html --html-details -o *.html


