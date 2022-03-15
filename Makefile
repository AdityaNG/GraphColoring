all: WelshPowell BruteForceSerial BruteForcePThread BruteForceCUDA
	echo Done

WelshPowell: src/WelshPowell/main.cpp
	g++ -o bin/WelshPowell src/WelshPowell/main.cpp

BruteForceSerial: src/BruteForceSerial/main.cpp
	g++ -o bin/BruteForceSerial src/BruteForceSerial/main.cpp

BruteForcePThread: src/BruteForcePThread/main.cpp
	g++ -o bin/BruteForcePThread -pthread src/BruteForcePThread/main.cpp

BruteForceCUDA: src/BruteForceCUDA/main.cu
	nvcc -o bin/BruteForceCUDA src/BruteForceCUDA/main.cu

clean: bin/*
	rm bin/*
