# Makefile

BINDIR := bin
LIBDIR := lib

CCFLAGS := -pedantic

CC := g++ -std=c++11

# src/ (declaracoes de funcoes, de classes + codigo)
# main/ (programas principais)
# bin/ (temporarios, .o, .exe)
# lib/ (bibliotecas) biblioteca FC

# making library
# - static: .a
# - shareable: .so

VPATH = main:src

ROOTLIB := $(shell root-config --libs)
ROOTINC := $(shell root-config --incdir)

SRC := $(wildcard src/*.C)
OBJ := $(patsubst %.C, $(BINDIR)/%.o, $(notdir $(SRC)))
INC := $(wildcard src/*.h)

lib: $(LIBDIR)/libFC.a

$(LIBDIR)/libFC.a: $(OBJ)
	@echo make lib...
	ar ruv $@ $^
	ranlib $@

%.exe: $(BINDIR)/%.o $(LIBDIR)/libFC.a
	@echo compilink and linking...
	$(CC) -I src $< -o $(BINDIR)/$@ -L lib -l FC $(ROOTLIB)

$(BINDIR)/%.o: %.C | $(INC)
	@echo compiling... $<
	$(CC) -I src -I $(ROOTINC) -c $< -o $@

prob1: $(BINDIR)/prob1.o $(LIBDIR)/libFC.a
	@echo compiling and linking prob1... $<
	$(CC) -I src $< -o $(BINDIR)/prob1.exe -L lib -l FC $(ROOTLIB)

prob2: $(BINDIR)/prob2.o $(LIBDIR)/libFC.a
	@echo compiling and linking prob2... $<
	$(CC) -I src $< -o $(BINDIR)/prob2.exe -L lib -l FC $(ROOTLIB)

prob3: $(BINDIR)/prob3.o $(LIBDIR)/libFC.a
	@echo compiling and linking prob3... $<
	$(CC) -I src $< -o $(BINDIR)/prob3.exe -L lib -l FC $(ROOTLIB)


######### clean

tilde := $(wildcard */*~) $(wildcard *~)
exe := $(wildcard */*.exe) $(wildcard *.exe)
obj := $(wildcard */*.o) $(wildcard *.o) $(wildcard */*.so) $(wildcard */*.pcm) $(wildcard */*.d)
libs := $(wildcard */*.a) $(wildcard *.a)

clean:
	@echo cleaning dir...
	rm -f $(exe) $(obj) $(tilde) $(libs)
