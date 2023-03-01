# build an executable named one from one.c
# build an executable named two from two.c
all: one.c two.c three.c
	gcc -g -Wall -pthread -o one one.c
	gcc -g -Wall -pthread -o two two.c
	gcc -g -Wall -pthread -o three three.c

clean:
	$(RM) one
	$(RM) two
	$(RM) three
