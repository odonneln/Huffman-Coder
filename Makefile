TARGET = encode
GCC = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic

SRCS = main.c count.c tree.c codes.c compress.c

OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

val_gophers:
	$(VALGRIND) ./encode test_files/original/gophers  tree.out code.out compressed.out
val_empty:
	$(VALGRIND) ./encode test_files/original/empty  tree.out code.out compressed.out
val_lorum:
	$(VALGRIND) ./encode test_files/original/lorum  tree.out code.out compressed.out
val_binary:
	$(VALGRIND) ./encode test_files/original/binary1  tree.out code.out compressed.out
val_stone:
	$(VALGRIND) ./encode test_files/original/stone  tree.out code.out compressed.out
val_woods:
	$(VALGRIND)	./encode test_files/original/woods  tree.out code.out compressed.out

test: gophers lorum stone woods binary empty

binary:
	./encode test_files/original/binary1  tree.out code.out compressed.out
	diff tree.out test_files/tree/binary1.tree
	diff code.out test_files/code/binary1.code
	diff compressed.out test_files/compressed/binary1.hbt

empty:
	./encode test_files/original/empty  tree.out code.out compressed.out
	diff tree.out test_files/tree/empty.tree
	diff code.out test_files/code/empty.code
	diff compressed.out test_files/compressed/empty.hbt

gophers:
	./encode test_files/original/gophers  tree.out code.out compressed.out
	diff tree.out test_files/tree/gophers.tree
	diff code.out test_files/code/gophers.code
	diff compressed.out test_files/compressed/gophers.hbt

lorum:
	./encode test_files/original/lorum  tree.out code.out compressed.out
	diff tree.out test_files/tree/lorum.tree
	diff code.out test_files/code/lorum.code
	diff compressed.out test_files/compressed/lorum.hbt
	
stone:
	./encode test_files/original/stone  tree.out code.out compressed.out
	diff tree.out test_files/tree/stone.tree
	diff code.out test_files/code/stone.code
	diff compressed.out test_files/compressed/stone.hbt
	
woods:
	./encode test_files/original/woods  tree.out code.out compressed.out
	diff tree.out test_files/tree/woods.tree
	diff code.out test_files/code/woods.code
	diff compressed.out test_files/compressed/woods.hbt
aaa:
	$(VALGRIND) ./encode test_cases/aaa a.out b.out c.out d.out
nonexistent:
	$(VALGRIND) ./encode test_cases/filenonexistent a.out b.out c.out d.out
exe:
	./encode test_cases/Revit_2019_G1_Win_64bit_Trial_wi_en-US_Setup.exe a.out b.out c.out d.out

clean:
	rm -f $(OBJS) $(TARGET) memcheck? output/* valout *.out
