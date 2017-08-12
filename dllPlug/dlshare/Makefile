CXXFLAGS = -g -fPIC -fvisibility=hidden
LDFLAGS = -shared 

TARGETSO = libdlshare.so
OBJS = dlshare.o 

all: $(TARGETSO)
	cp $(TARGETSO) ../Test/
	
$(TARGETSO): $(OBJS)
	$(CXX)  $(LDFLAGS) -o $@ $^ 
	
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
clean:
	@rm -rvf $(OBJS) $(TARGETSO)
