
OPTIMIZATION  = -O0

test: test.cpp golf.o golf.h
	c++ $(OPTIMIZATION) golf.o test.cpp -o test

golf.o: golf.cpp golf.h
	c++ $(OPTIMIZATION) golf.cpp -c

