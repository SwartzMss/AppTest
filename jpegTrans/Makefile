TARGET = jpegTrans.exe
CXXFLAGS =  -I../depend/libjpeg/include
LDFLAGS =  -L../depend/libjpeg/lib -lturbojpeg 
OBJS =  jpegTrans.o 

all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c -w $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)
