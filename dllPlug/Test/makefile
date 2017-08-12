CXXFLAGS = -g -fPIC 
LDFLAGS =  -L./  -lshare -ldl
TARGETSO = Test.exe
OBJS = main.o 

all: $(TARGETSO)

$(TARGETSO): $(OBJS)
	$(CXX)  $(LDFLAGS) -o $@ $^  libStaticFun.a
	
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
clean:
	@rm -rvf $(OBJS) $(TARGETSO)