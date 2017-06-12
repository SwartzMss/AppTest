TARGET = SqliteTest.exe
CXXFLAGS = -I../depend/sqlite -I../depend
LDFLAGS =  -L../depend/sqlite -lsqlite3 -lpthread -ldl -L../depend/log4cplus -llog4cplus
OBJS = main.o MyLogger.o CppSQLite3DB.o

all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c -w $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)