CPP_FLAGS = -std=c++26 -Werror=vla -Wall -g
COMPILER = g++

build: main.cpp
	@echo "Compiling main.cpp";
	@$(COMPILER) $(CPP_FLAGS) main.cpp -o main

clean: main
	@echo "Cleaning up...";
	@rm main

default:
	clean;
	build;