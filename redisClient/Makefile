TARGET = example-libevent.exe
CXXFLAGS = -g -fPIC -I../depend/redis/include/ -It../depend/libevent/include
LDFLAGS =  -L../depend/redis/lib -lhiredis  -L../depend/libevent/lib -levent -lpthread
OBJS = example-libevent.o 
CXX = g++
all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c  $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)
