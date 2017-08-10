TARGET = RSATest.exe
CXXFLAGS =  -I../depend
LDFLAGS =  -L../depend/openssl -lssl -lcrypto -ldl
OBJS = main.o RSATest.o 

all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c -w $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)
