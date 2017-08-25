CXXFLAGS = -g -fPIC -I../depend/mq/include
LDFLAGS =  -L../depend/mq/lib -lrabbitmq -lAMQP 

TARGETSO = MqClient
OBJS = MqClient.o  

all: $(TARGETSO)
	cp ../depend/mq/lib/* ./ -av
	
	
$(TARGETSO): $(OBJS)
	$(CXX)  $(LDFLAGS) -o $@ $^ 
	
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
clean:
	@rm -rvf $(OBJS) $(TARGETSO)
