CC = gcc
OPT = -Wall -Wextra -O2
TARGET = Hairpin_Checker

all: $(TARGET)

$(TARGET): main.o hairpin_check.o FASTA.o
	$(CC) $(OPT) -o $(TARGET) main.o hairpin_check.o FASTA.o -lm
	rm -f *.o

main.o: main.c
	$(CC) $(OPT) -c main.c

hairpin_check.o: ./hairpin_check/hairpin_check.c ./hairpin_check/hairpin_check.h
	$(CC) $(OPT) -c ./hairpin_check/hairpin_check.c

FASTA.o: ./FASTA/FASTA.c ./FASTA/FASTA.h
	$(CC) $(OPT) -c ./FASTA/FASTA.c

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
