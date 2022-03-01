all: serial parallel
	echo Done

serial: src/serial/main.cpp
	g++ -o bin/WelshPowellSerial src/serial/main.cpp

parallel: src/parallel/main.cpp
	g++ -o bin/WelshPowellParallel src/parallel/main.cpp

clean: bin/*
	rm bin/*
