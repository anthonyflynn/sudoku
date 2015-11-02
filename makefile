sudoku: main.o sudoku.o
	g++ -Wall -g main.o sudoku.o -o sudoku

unit_test: unit_test.o sudoku.o
	g++ -Wall -g unit_test.o sudoku.o -o unit_test

main.o: main.cpp sudoku.h
	g++ -g -c main.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -g -c sudoku.cpp

unit_test.o: unit_test.cpp sudoku.h
	g++ -g -c unit_test.cpp

clean:
	rm -rf sudoku *.o unit_test temp.dat
