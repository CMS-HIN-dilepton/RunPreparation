
FLAGS=$(shell ../HelperScripts/compilerFlags.sh ) -o
SOURCES:=$(shell find . -name  "*.cpp")
HEADERS:=$(shell find . -name  "*.h")
STATICLIBS:= ../OniaIO/libOniaIO.a ../TreeIO/libTreeIO.a ../Utils/libUtils.a
INC:=-I $(shell $(ROOTSYS)/bin/root-config --cflags)
LIBS:=$(shell $(ROOTSYS)/bin/root-config --ldflags --glibs) -lRooFit -lRooFitCore -lMinuit
OUTPUT:=ploteff

${OUTPUT} : ${SOURCES} ${HEADERS} ${STATICLIBS}
	g++ ${SOURCES} ${STATICLIBS} ${INC} ${LIBS} ${FLAGS} ${OUTPUT}
	objdump $(shell ../HelperScripts/objdumpFlags.sh) ${OUTPUT} > ${OUTPUT}.s

clear :
	rm -f ${OUTPUT} *.o *.s