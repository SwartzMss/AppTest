CXX  = g++

CXXFLAGS = -g -fPIC 
LDFLAGS =  -ldl
CPPFLAGS = -I../dll

TARGETSO = a.out
OBJS = main.o 

all: $(TARGETSO)
	cd ../dll && $(MAKE) -e CXX='${CXX}'

$(TARGETSO): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ 
	
%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@
clean:
	cd ../dll && $(MAKE) clean
	@rm -rvf $(OBJS) $(TARGETSO)