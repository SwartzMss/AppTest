CXXFLAGS = -g -fPIC -I../depend/mq/include
LDFLAGS = -shared -L../depend/mq/lib -lrabbitmq -L../depend/openssl -lssl -lcrypto -ldl -lpthread

TARGETSO = libAMQP.so
OBJS = AMQP.o  AMQPBase.o AMQPException.o AMQPExchange.o AMQPMessage.o  AMQPQueue.o

all: $(TARGETSO)
	cp $(TARGETSO) ../depend/mq/lib
	
$(TARGETSO): $(OBJS)
	$(CXX)  $(LDFLAGS) -o $@ $^ 
	
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
clean:
	@rm -rvf $(OBJS) $(TARGETSO)
