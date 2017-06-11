CXX  = g++

all:
	cd systeminfo && $(MAKE) -e CXX='${CXX}';
	cd dlltest/src && $(MAKE) -e CXX='${CXX}'
	
clean:
	cd systeminfo && $(MAKE) clean;
	cd dlltest/src && $(MAKE) clean