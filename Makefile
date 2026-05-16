CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude

TARGET = recommend

SRCS = src/main.cpp \
       src/MovieManager.cpp \
       src/UserManager.cpp \
       src/RatingManager.cpp \
       src/Recommender.cpp \
       src/Movie.cpp \
       src/User.cpp \
       src/Rating.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET)