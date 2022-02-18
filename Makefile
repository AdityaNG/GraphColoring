all: serial parallel
	./bin/WelshPowellSerial < input.txt > output.txt

serial: src/serial/main.cpp
	g++ -o bin/WelshPowellSerial src/serial/main.cpp

parallel: src/parallel/main.cpp
	g++ -o bin/WelshPowellParallel src/parallel/main.cpp

clean:
	rm bin/*