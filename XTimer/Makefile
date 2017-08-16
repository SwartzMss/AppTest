TARGET = XTimer.exe
CXXFLAGS = -g -fPIC 
LDFLAGS =  -lpthread
OBJS = main.o XTimer.o

all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c   $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)
