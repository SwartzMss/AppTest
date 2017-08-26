TARGET = log4Test.exe
CXXFLAGS = -g -fPIC -I../depend/log4cxx/include
LDFLAGS =  -L../depend/log4cxx/lib -llog4cxx -lpthread
OBJS = log4Test.o 

all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c  $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)
