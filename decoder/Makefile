TARGET = decode
#GCC = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc -g -std=c99 -Wall -Wshadow -Wvla -pedantic

SRCS = main.c tree.c decompress.c read.c utility.c

OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

val_gophers:
	$(VALGRIND) ./decode ../test_files/compressed/gophers.hbt decompressed.out
val_empty:
	$(VALGRIND) ./decode ../test_files/compressed/empty.hbt decompressed.out
val_lorum:
	$(VALGRIND) ./decode ../test_files/compressed/lorum.hbt decompressed.out
val_binary:
	$(VALGRIND) ./decode ../test_files/compressed/binary1.hbt decompressed.out
val_stone:
	$(VALGRIND) ./decode ../test_files/compressed/stone.hbt decompressed.out
val_woods:
	$(VALGRIND)	./decode ../test_files/compressed/woods.hbt decompressed.out

val_tree:
	$(VALGRIND) ./decode ../test_files/compressed/gophers.hbt tree.out

tree:
	./decode ../test_files/compressed/gophers.hbt tree.out
	diff tree.out ../test_files/tree/gophers.tree
	./decode ../test_files/compressed/stone.hbt tree.out
	diff tree.out ../test_files/tree/stone.tree
	./decode ../test_files/compressed/lorum.hbt tree.out
	diff tree.out ../test_files/tree/lorum.tree
	./decode ../test_files/compressed/binary1.hbt tree.out
	diff tree.out ../test_files/tree/binary1.tree

test: gophers lorum stone woods binary empty

binary:
	./decode ../test_files/compressed/binary1.hbt decompressed.out
	diff decompressed.out ../test_files/original/binary1

empty:
	./decode ../test_files/compressed/empty.hbt decompressed.out
	diff decompressed.out ../test_files/original/empty

gophers:
	./decode ../test_files/compressed/gophers.hbt decompressed.out
	diff decompressed.out ../test_files/original/gophers

lorum:
	./decode ../test_files/compressed/lorum.hbt decompressed.out
	diff decompressed.out ../test_files/original/lorum
	
stone:
	./decode ../test_files/compressed/stone.hbt decompressed.out
	diff decompressed.out ../test_files/original/stone
	
woods:
	./decode ../test_files/compressed/woods.hbt decompressed.out
	diff decompressed.out ../test_files/original/woods
aaa:
	$(VALGRIND) ./decode test_cases/aaa a.out b.out c.out d.out
nonexistent:
	$(VALGRIND) ./decode test_cases/filenonexistent a.out b.out c.out d.out
exe:
	./decode test_cases/Revit_2019_G1_Win_64bit_Trial_wi_en-US_Setup.exe a.out b.out c.out d.out

clean:
	rm -f $(OBJS) $(TARGET) memcheck? output/* valout *.out
