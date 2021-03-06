CXX      = g++

.DEFAULT_GOAL := all

SOURCES = 
SOURCES += Board.cpp 

OBJECTS = $(SOURCES:.cpp=.o)

CXXFLAGS += -std=c++17 -g -Wall -pedantic
LDFLAGS +=

$(OBJECTS) : %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

CLEAN_OBJECTS = $(OBJECTS)
TARGETS = 

########## demo ##########

DEMO_SOURCES = main.cpp BoardGraph.cpp MoveDeck.cpp ArtificialPlayer.cpp
DEMO_OBJECTS = $(DEMO_SOURCES:.cpp=.o)

demo : $(DEMO_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(DEMO_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(DEMO_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : demo
TARGETS += demo
CLEAN_OBJECTS += $(DEMO_OBJECTS)

########## test_board ##########

TEST_BOARD_SOURCES = test_board.cpp
TEST_BOARD_OBJECTS = $(TEST_BOARD_SOURCES:.cpp=.o)

test_board : $(TEST_BOARD_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(TEST_BOARD_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(TEST_BOARD_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : test_board
TARGETS += test_board
CLEAN_OBJECTS += $(TEST_BOARD_OBJECTS)

########## app ##########

APP_SOURCES = app.cpp
APP_OBJECTS = $(APP_SOURCES:.cpp=.o)

app : $(APP_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) -pthread $(APP_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(APP_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : app
TARGETS += app
CLEAN_OBJECTS += $(APP_OBJECTS)

########## cleanup ##########
DEPS = $(CLEAN_OBJECTS:.o=.d)

clean:
	@rm -f $(DEPS) $(TARGETS) $(CLEAN_OBJECTS)

-include $(DEPS)
