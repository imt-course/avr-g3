
all: file.exe

file.exe: main.o file1.o file2.o
	@echo Linking ...
	@gcc main.o file1.o file2.o -o file.exe
	@echo file.exe generated successfully.

main.o: main.c file1.h file2.h
	@echo Compiling main.c ...
	@gcc -c main.c -o main.o
	
file1.o: file1.c file1.h
	@echo Compiling file1.c ...
	@gcc -c file1.c -o file1.o
	
file2.o: file2.c file2.h
	@echo Compiling file2.c ...
	@gcc -c file2.c -o file2.o
	
clean:
	@IF EXIST *.o DEL /f *.o 
	@IF EXIST *.exe DEL /f *.exe
	@echo Clean Success.