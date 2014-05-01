all: main.cpp bigInt.cpp
	g++ main.cpp bigInt.cpp -o TCHMK_1 -lm
	
windows: main.cpp bigInt.cpp
	g++ main.cpp bigInt.cpp -o TCHMK_1 -lm
