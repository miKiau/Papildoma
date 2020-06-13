main: fun.o
	g++ -o main main.cpp fun.o
funkcijos:
	g++ -c fun.cpp
clean:
	rm main fun.o
