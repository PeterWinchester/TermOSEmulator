all : main.o TOSEBasicData.o TOSECommands.o TOSEInstaller.o
	g++ -g main.o TOSEBasicData.o TOSECommands.o -o TermOSEmulator
	g++ -g TOSEBasicData.o TOSECommands.o TOSEInstaller.o -o TOSEInstaller
main.o : src/main.cpp
	g++ -g -c -I include src/main.cpp
TOSEInstaller.o : src/TOSEInstaller.cpp
	g++ -g -c -I include src/TOSEInstaller.cpp
TOSEBasicData.o : src/TOSEBasicData.cpp
	g++ -g -c -I include src/TOSEBasicData.cpp
TOSECommands.o : src/TOSECommands.cpp
	g++ -g -c -I include src/TOSECommands.cpp
SHELL=cmd.exe
clean:
	del *.o
install:
	TOSEInstaller
