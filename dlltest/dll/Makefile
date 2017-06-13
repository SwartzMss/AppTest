CXXFLAGS = -g -fPIC -fvisibility=hidden
LDFLAGS = -shared -lpthread 

TARGETSO = ../src/libdlltest.so
OBJS = Cdlltest.o Idlltest.o

all: $(TARGETSO)

$(TARGETSO): $(OBJS)
	$(CXX)  $(LDFLAGS) -o $@ $^ 
	
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
clean:
	@rm -rvf $(OBJS) $(TARGETSO)
