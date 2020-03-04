CXX = gcc -Wall
exec = function_tests consoleapp

libdef = prob_func.c
libhead = prob_func.h

all : $(exec)

function_tests : function_tests.c $(libdef) $(libhead)
	$(CXX) $< $(libdef) -o $@

consoleapp : consoleapp.c $(libdef) $(libhead)
	$(CXX) $< $(libdef) -o $@

reset :
	rm -f $(exec)
