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
		 -fopenmp   \
         -std=c++14 

RM = rm -rf

all: $(PROJ_NAME)

$(PROJ_NAME): 
	@ echo 'Compilando o arquivo $(CPP_SOURCE)...'
	$(CC) $(CC_FLAGS) $(CPP_SOURCE) -o dist/$@
	@ echo 'Concluido! Executavel criado: $@'
	@ echo ' '

clean:
	@ $(RM) ./objects
