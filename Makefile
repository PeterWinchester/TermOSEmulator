TermOSEmulator.exe : main.o TOSEBasicData.o TOSECommands.o
	g++ -g main.o TOSEBasicData.o TOSECommands.o -o TermOSEmulator
main.o : src/main.cpp
	g++ -g -c -I include src/main.cpp
TOSEBasicData.o : src/TOSEBasicData.cpp
	g++ -g -c -I include src/TOSEBasicData.cpp
TOSECommands.o : src/TOSECommands.cpp
	g++ -g -c -I include src/TOSECommands.cpp
