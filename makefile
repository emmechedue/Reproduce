compile: Better_reproduce.cpp ./Headers/headers1.h
	g++ -I /usr/include/gsl -I ./Headers Better_reproduce.cpp -lgsl -lgslcblas -lm -Wall -O2
		
clean: 
	rm *~
	rm ./Headers/*~
	rm fast.txt
	rm output.txt
	
