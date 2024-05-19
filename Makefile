SRCS = main.c 2048.c term_manip.c
EXEC = 2048

buildrun: $(SRCS)
	gcc -o $(EXEC) $(SRCS)
	./$(EXEC)

build: $(SRCS)
	gcc -o $(EXEC) $(SRCS)

run: $(EXEC)
	./$(EXEC)
