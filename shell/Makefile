all: shellDemo

CFLAGS = -g -O2

shellDemo: shellDemo.o shell.o myToc.o
	cc -o shellDemo shellDemo.o shell.o myToc.o
clean:
	rm -f  *.o 
demo: shellDemo
	./shellDemo
