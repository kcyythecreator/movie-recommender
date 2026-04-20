CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g -I../include
TARGET   = movie_recommender

OBJS     = main.o movie.o movie_manager.o user.o user_manager.o rating.o rating_manager.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean run

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)