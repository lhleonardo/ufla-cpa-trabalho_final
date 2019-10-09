# referencia: https://www.embarcados.com.br/introducao-ao-makefile/
# Name of the project
PROJ_NAME=cpa.exe

# .cpp files
CPP_SOURCE=src/main.cpp

# Compiler and linker
CC=g++

# Flags for compiler
CC_FLAGS=-g 		\
         -Wall      \
         -ansi      \
		 -std=c++11

RM = rm -rf

all: $(PROJ_NAME)

single:
	@ echo 'Compilando o arquivo $(CPP_SOURCE) sem o uso de OpenMP...'
	$(CC) $(CC_FLAGS) $(CPP_SOURCE) -o dist/$@
	@ echo 'Concluido! Executavel criado: $@'
	@ echo ' '

$(PROJ_NAME): 
	@ echo 'Compilando o arquivo $(CPP_SOURCE)...'
	$(CC) $(CC_FLAGS) -fopenmp $(CPP_SOURCE) -o dist/$@
	@ echo 'Concluido! Executavel criado: $@'
	@ echo ' '

clean:
	@ $(RM) ./objects
