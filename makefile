# Compiler
CC = gcc
CFLAGS = -Wall -g

# Object files
OBJ = asc2int.o asm_mnmo.o asm_space.o cal_drctv.o cal_expr.o cal_mnmo.o cal_term.o dctab.o main.o optab.o put_list.o rdline.o str2int.o symtab.o

# Header files
HEADERS = asc2int.h asm_mnmo.h asm_space.h cal_drctv.h cal_expr.h cal_mnmo.h cal_term.h dctab.h main.h optab.h put_list.h rdline.h str2int.h symtab.h

# Output executable
TARGET = asm_s10

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rules to compile each .c file into .o file
asc2int.o: asc2int.c asc2int.h
	$(CC) $(CFLAGS) -c asc2int.c

asm_mnmo.o: asm_mnmo.c asm_mnmo.h
	$(CC) $(CFLAGS) -c asm_mnmo.c

asm_space.o: asm_space.c asm_space.h
	$(CC) $(CFLAGS) -c asm_space.c

cal_drctv.o: cal_drctv.c cal_drctv.h
	$(CC) $(CFLAGS) -c cal_drctv.c

cal_expr.o: cal_expr.c cal_expr.h
	$(CC) $(CFLAGS) -c cal_expr.c

cal_mnmo.o: cal_mnmo.c cal_mnmo.h
	$(CC) $(CFLAGS) -c cal_mnmo.c

cal_term.o: cal_term.c cal_term.h
	$(CC) $(CFLAGS) -c cal_term.c

dctab.o: dctab.c dctab.h
	$(CC) $(CFLAGS) -c dctab.c

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

optab.o: optab.c optab.h
	$(CC) $(CFLAGS) -c optab.c

put_list.o: put_list.c put_list.h
	$(CC) $(CFLAGS) -c put_list.c

rdline.o: rdline.c rdline.h
	$(CC) $(CFLAGS) -c rdline.c

str2int.o: str2int.c str2int.h
	$(CC) $(CFLAGS) -c str2int.c

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)
