TARGET = encode
#GCC = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc -g -std=c99 -Wall -Wshadow -Wvla -pedantic

SRCS = main.c count.c tree.c codes.c compress.c

OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

val_gophers:
	$(VALGRIND) ./encode test_files/original/gophers compressed.out
val_empty:
	$(VALGRIND) ./encode test_files/original/empty compressed.out
val_lorum:
	$(VALGRIND) ./encode test_files/original/lorum compressed.out
val_binary:
	$(VALGRIND) ./encode test_files/original/binary1 compressed.out
val_stone:
	$(VALGRIND) ./encode test_files/original/stone compressed.out
val_woods:
	$(VALGRIND)	./encode test_files/original/woods compressed.out

test: gophers lorum stone woods binary empty

binary:
	./encode test_files/original/binary1 compressed.out
	diff compressed.out test_files/compressed/binary1.hbt

empty:
	./encode test_files/original/empty compressed.out
	diff compressed.out test_files/compressed/empty.hbt

gophers:
	./encode test_files/original/gophers compressed.out
	diff compressed.out test_files/compressed/gophers.hbt

lorum:
	./encode test_files/original/lorum compressed.out
	diff compressed.out test_files/compressed/lorum.hbt
	
stone:
	./encode test_files/original/stone compressed.out
	diff compressed.out test_files/compressed/stone.hbt
	
woods:
	./encode test_files/original/woods compressed.out
	diff compressed.out test_files/compressed/woods.hbt
aaa:
	$(VALGRIND) ./encode test_cases/aaa a.out b.out c.out d.out
nonexistent:
	$(VALGRIND) ./encode test_cases/filenonexistent a.out b.out c.out d.out
exe:
	./encode test_cases/Revit_2019_G1_Win_64bit_Trial_wi_en-US_Setup.exe a.out b.out c.out d.out

clean:
	rm -f $(OBJS) $(TARGET) memcheck? output/* valout *.out
