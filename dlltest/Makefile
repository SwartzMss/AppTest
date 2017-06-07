CXX  = g++

%.o : %.cpp
	$(CXX) -c $(OPTS) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

clean:
	rm -rvf $(OBJS) $(TARGETSO)