# Nome do projeto
PROJ_NAME=exLista
#wildcard vai pegar todos os arquivos cpp
C_SOURCE=$(wildcard ./*.c)

#wildcard vai pegar todos os arquivos hpp
H_SOURCE=$(wildcard ./*.h)

#Arquivos compilados
OBJ=$(subst .c,.o,$(subst source,objects,$(C_SOURCE)))

# Compiler and linker
CC=gcc

# Flags para o compilador
# C: Compila mas não chama o linker
# Wall: mostra todos os warnings
# Wextra:  Warnings que o wall não mostra
# ansi: Só roda c++ padrão.  
# pedantic: Rejeita c++ não padrão
CC_FLAGS=-c         \
	 -Wextra    \
         -Wall      \
         -ansi      \
         -pedantic

# Command used at clean target
RM = rm -rf


# Compilation and linking

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using G++ linker: $@'
	$(CC) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./objects/%.o: ./*.cpp ./*.hpp
	@ echo 'Building target using G++ compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./objects/main.o: ./main.cpp (HPP_SOURCE)
@ echo 'Building target using G++ compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

clean:
	@ $(RM) ./*.o $(PROJ_NAME) *~
	
run:    all
	./exLista


.TUDO: all clean
