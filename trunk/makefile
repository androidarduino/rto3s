o3s:	main.o core.o
	g++ main.o core.o -o o3s
main.o:	main.cpp
	g++ -c main.cpp -o main.o
core.o:	core.cpp
	g++ -c core.cpp -o core.o
clean:
	rm core.o
	rm main.o
	rm o3s
run:	o3s
	./o3s
