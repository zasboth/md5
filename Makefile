
default:
	g++ -c *.cc -O2 -Wall
	g++ -o main.exe *.o
	rm -f *.o *~
