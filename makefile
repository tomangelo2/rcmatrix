matrix: matrix.o array.o test_matrix.cpp
	g++ -g -Wall -pedantic $^ -o $@

matrix.o: matrix.cpp matrix.h 
	g++ -g -c -Wall -pedantic $< -o $@
	
array.o: array.cpp array.h
	g++ -g -c -Wall -pedantic $< -o $@

.PHONY: clean

clean:
	-rm matrix.o matrix array.o
