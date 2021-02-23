TermOSEmulator.exe : main.o TOSEBasicData.o
	g++ main.o TOSEBasicData.o -o TermOSEmulator
main.o : src/main.cpp
	g++ -c src/main.cpp
TOSEBasicData.o : src/TOSEBasicData.cpp
	g++ -c src/TOSEBasicData.cpp
