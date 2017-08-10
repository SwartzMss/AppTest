TARGET = LogApp.exe
CXXFLAGS = -g -fPIC -I../depend/log4cplus/include
LDFLAGS =  -L../depend/log4cplus/lib -llog4cplus -lpthread
OBJS = main.o MyLogger.o

all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c  $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)
