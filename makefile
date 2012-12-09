compile: Better_reproduce.cpp ./Headers/headers1.h
	g++ -I /usr/include/gsl -I ./Headers Better_reproduce.cpp -lgsl -lgslcblas -lm
		
clean: 
	rm *~
	rm fast.txt
	rm output.txt
