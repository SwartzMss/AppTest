TARGET = protobuf.exe
CXXFLAGS = -g -fPIC -I../depend/protobuf/include
LDFLAGS =  -L../depend/protobuf/lib -lprotobuf -lpthread
OBJS = main.o msg.pb.o

all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c  $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)
