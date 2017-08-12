TARGET = libeventSever.exe
CXXFLAGS = -g -fPIC -I../depend/libevent/include 
LDFLAGS =  -L../depend/libevent/lib -levent -levent_pthreads -lpthread
OBJS = libeventSever.o EventSocket.o

all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c   $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)
