TARGET = SqliteWork.exe
CXXFLAGS = -g -fPIC -I../depend/sqlite/include
LDFLAGS =  -L../depend/sqlite/lib -lsqlite3 -lpthread
OBJS = main.o CppSQLite3DB.o

all:$(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $^  $(LDFLAGS) -o $@ 
	
%.o : %.cpp
	$(CXX) -c  $(CXXFLAGS) $< -o $@
	
clean:
	@rm -rvf $(OBJS) $(TARGET)
