
make: example1.cc example2.cc
	g++ example1.cc -o example1 -I. -std=c++1y
	g++ example2.cc -o example2 -I. -std=c++1y
	time ./example1
