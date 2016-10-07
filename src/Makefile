COMPILER = g++
#COMPILER = clang++
#COMPILER = g++-4.4
CFLAGS    = -g -Wall -Wextra -Winit-self -Wno-unused-parameter -Wfloat-equal -std=c++11
#CFLAGS   += `root-config --cflags`
LDFLAGS   =
#LDFLAGS  += `root-config --libs`
LIBS      =
INCLUDE   = -I../include

#TARGET   = ../bin/$(shell basename `readlink -f ..`)
TARGET = Lasagna_PDF_transposition

SOURCES  = $(wildcard *.cc)
OBJECTS  = $(SOURCES:.cc=.o)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)
	chmod u+x $(TARGET)

%.o: %.cc
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET) *~ ../include/*~
