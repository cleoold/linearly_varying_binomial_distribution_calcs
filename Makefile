output = function_tests.exe consoleapp.exe

all : $(output) clean

function_tests.exe : function_tests.c prob_func.c prob_func.h
	cl function_tests.c prob_func.c

consoleapp.exe : consoleapp.c prob_func.c prob_func.h
	cl consoleapp.c prob_func.c

clean :
	del /f /q *.obj

reset :
	del /f /q $(output)