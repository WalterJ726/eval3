CFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3 
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) cyoa_story.o Story.o Page.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o cyoa_story.o Story.o Page.o
	g++ -o $@ $^
%.o: %.cpp 
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

cyoa_story.o: cyoa_story.hpp
Story.o: Story.hpp
Page.o: Page.hpp
