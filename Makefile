GTKMM_CF = `pkg-config gtkmm-3.0 --cflags`
GTKMM_LD = `pkg-config gtkmm-3.0 --libs`

CC = g++
CFLAGS = $(GTKMM_CF) -Wall
LDFLAGS = $(GTKMM_LD)

SRC = main.cpp Vue.cpp
PROG = main
OBJS = $(SRC:.cpp=.o)
.SUFFIXES: .cpp .o

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: Modele.hpp Vue.hpp Controleur.hpp
Vue.o: Vue.hpp Controleur.hpp

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o $(PROG)
