TARGET = huffman
GCC = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic

SRCS = main.c count.c tree.c codes.c compress.c

OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

val_gophers:
	$(VALGRIND) ./huffman test_files/original/gophers count.out tree.out code.out compressed.out
val_empty:
	$(VALGRIND) ./huffman test_files/original/empty count.out tree.out code.out compressed.out
val_lorum:
	$(VALGRIND) ./huffman test_files/original/lorum count.out tree.out code.out compressed.out
val_binary:
	$(VALGRIND) ./huffman test_files/original/binary1 count.out tree.out code.out compressed.out
val_stone:
	$(VALGRIND) ./huffman test_files/original/stone count.out tree.out code.out compressed.out
val_woods:
	$(VALGRIND)	./huffman test_files/original/woods count.out tree.out code.out compressed.out

test: gophers lorum stone woods binary empty

binary:
	./huffman test_files/original/binary1 count.out tree.out code.out compressed.out
	diff count.out test_files/count/binary1.count
	diff tree.out test_files/tree/binary1.tree
	diff code.out test_files/code/binary1.code
	diff compressed.out test_files/compressed/binary1.hbt

empty:
	./huffman test_files/original/empty count.out tree.out code.out compressed.out
	diff count.out test_files/count/empty.count
	diff tree.out test_files/tree/empty.tree
	diff code.out test_files/code/empty.code
	diff compressed.out test_files/compressed/empty.hbt

gophers:
	./huffman test_files/original/gophers count.out tree.out code.out compressed.out
	diff count.out test_files/count/gophers.count
	diff tree.out test_files/tree/gophers.tree
	diff code.out test_files/code/gophers.code
	diff compressed.out test_files/compressed/gophers.hbt

lorum:
	./huffman test_files/original/lorum count.out tree.out code.out compressed.out
	diff count.out test_files/count/lorum.count
	diff tree.out test_files/tree/lorum.tree
	diff code.out test_files/code/lorum.code
	diff compressed.out test_files/compressed/lorum.hbt
	
stone:
	./huffman test_files/original/stone count.out tree.out code.out compressed.out
	diff count.out test_files/count/stone.count
	diff tree.out test_files/tree/stone.tree
	diff code.out test_files/code/stone.code
	diff compressed.out test_files/compressed/stone.hbt
	
woods:
	./huffman test_files/original/woods count.out tree.out code.out compressed.out
	diff count.out test_files/count/woods.count
	diff tree.out test_files/tree/woods.tree
	diff code.out test_files/code/woods.code
	diff compressed.out test_files/compressed/woods.hbt
aaa:
	$(VALGRIND) ./huffman test_cases/aaa a.out b.out c.out d.out
nonexistent:
	$(VALGRIND) ./huffman test_cases/filenonexistent a.out b.out c.out d.out
exe:
	./huffman test_cases/Revit_2019_G1_Win_64bit_Trial_wi_en-US_Setup.exe a.out b.out c.out d.out

clean:
	rm -f $(OBJS) $(TARGET) memcheck? output/* valout *.out
