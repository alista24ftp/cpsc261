CFLAGS = -g

all:		testadd testfib testmax testsum

testadd:	testadd.o add.o
testfib:	testfib.o fib.o
testmax:	testmax.o max.o
testsum:	testsum.o sum.o

add.o:		add.s
fib.o:		fib.s
max.o:		max.s
sum.o:		sum.s

clean:
	rm -f *.o testadd testfib testmax testsum

run:	testadd testfib testmax testsum
	./testadd
	./testfib
	./testmax
	./testsum

.s.o:;	gcc $(CFLAGS) -c -o $*.o $*.s
