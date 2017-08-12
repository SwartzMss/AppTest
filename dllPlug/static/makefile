CXXFLAGS = -g

TARGETSO = libStaticFun.a
OBJS = StaticFun.o 

all: $(TARGETSO)
	cp $(TARGETSO) ../Test/

$(TARGETSO): $(OBJS)
	ar cr   $(TARGETSO) $(OBJS)
	
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
clean:
	@rm -rvf $(OBJS) $(TARGETSO)