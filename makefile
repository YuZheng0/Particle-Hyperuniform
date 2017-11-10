EXEC = mc.out

ODIR = obj
OBJS = $(addprefix $(ODIR)/, mc.o particle.o system.o)

SDIR = src
IDIR = include
DEPS = $(addprefix $(IDIR)/, particle.hpp, system.hpp)

CC = g++ -std=c++11
CFLAGS = -c -I $(IDIR)
LFLAGS =


$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) $< -o $@
