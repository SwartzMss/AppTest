TARGET = RSATest.exe
CXXFLAGS =  -I../depend
LDFLAGS =  -L../depend/openssl -lsqlite3 -lssl -lcrypto -ldl
OBJS = main.o RSATest.o 

all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c -w $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)