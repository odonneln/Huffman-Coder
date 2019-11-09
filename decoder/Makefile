TARGET = decode
#GCC = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc -g -std=c99 -Wall -Wshadow -Wvla -pedantic

SRCS = main.c tree.c

OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

val_gophers:
	$(VALGRIND) ./decode ../encoder/test_files/compressed/gophers.hbt decompressed.out
val_empty:
	$(VALGRIND) ./decode ../encoder/test_files/compressed/empty.hbt decompressed.out
val_lorum:
	$(VALGRIND) ./decode ../encoder/test_files/compressed/lorum.hbt decompressed.out
val_binary:
	$(VALGRIND) ./decode ../encoder/test_files/compressed/binary1.hbt decompressed.out
val_stone:
	$(VALGRIND) ./decode ../encoder/test_files/compressed/stone.hbt decompressed.out
val_woods:
	$(VALGRIND)	./decode ../encoder/test_files/compressed/woods.hbt decompressed.out

tree:
	./decode ../encoder/test_files/tree/gophers.tree tree.out
	diff tree.out ../encoder/test_files/tree/gophers.tree
	./decode ../encoder/test_files/tree/stone.tree tree.out
	diff tree.out ../encoder/test_files/tree/stone.tree
	./decode ../encoder/test_files/tree/lorum.tree tree.out
	diff tree.out ../encoder/test_files/tree/lorum.tree
	./decode ../encoder/test_files/tree/binary1.tree tree.out
	diff tree.out ../encoder/test_files/tree/binary1.tree

test: gophers lorum stone woods binary empty

binary:
	./decode ../encoder/test_files/compressed/binary1.hbt decompressed.out
	diff decompressed.out ../encoder/test_files/original/binary1

empty:
	./decode ../encoder/test_files/compressed/empty.hbt decompressed.out
	diff decompressed.out ../encoder/test_files/original/empty

gophers:
	./decode ../encoder/test_files/compressed/gophers.hbt decompressed.out
	diff decompressed.out ../encoder/test_files/original/gophers

lorum:
	./decode ../encoder/test_files/compressed/lorum.hbt decompressed.out
	diff decompressed.out ../encoder/test_files/original/lorum
	
stone:
	./decode ../encoder/test_files/compressed/stone.hbt decompressed.out
	diff decompressed.out ../encoder/test_files/original/stone
	
woods:
	./decode ../encoder/test_files/compressed/woods.hbt decompressed.out
	diff decompressed.out ../encoder/test_files/original/woods
aaa:
	$(VALGRIND) ./decode test_cases/aaa a.out b.out c.out d.out
nonexistent:
	$(VALGRIND) ./decode test_cases/filenonexistent a.out b.out c.out d.out
exe:
	./decode test_cases/Revit_2019_G1_Win_64bit_Trial_wi_en-US_Setup.exe a.out b.out c.out d.out

clean:
	rm -f $(OBJS) $(TARGET) memcheck? output/* valout *.out
