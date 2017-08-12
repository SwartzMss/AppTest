TARGET = ThriftClient.exe
CXXFLAGS = -g -fPIC -I../depend/thrift/include
LDFLAGS =  -L../depend/thrift/lib -lthrift -lthriftnb -L../depend/libevent/lib -levent -levent_pthreads -lpthread
OBJS = ThriftClient.o HelloService.o hello_constants.o hello_types.o

all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c   $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)
