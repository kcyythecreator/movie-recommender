CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET   = movie_app

OBJS     = main.o movie.o movie_manager.o user.o user_manager.o rating.o rating_manager.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp movie.h movie_manager.h user.h user_manager.h rating.h rating_manager.h
	$(CXX) $(CXXFLAGS) -c $<

movie.o: movie.cpp movie.h
	$(CXX) $(CXXFLAGS) -c $<

movie_manager.o: movie_manager.cpp movie_manager.h movie.h
	$(CXX) $(CXXFLAGS) -c $<

user.o: user.cpp user.h
	$(CXX) $(CXXFLAGS) -c $<

user_manager.o: user_manager.cpp user_manager.h user.h
	$(CXX) $(CXXFLAGS) -c $<

rating.o: rating.cpp rating.h
	$(CXX) $(CXXFLAGS) -c $<

rating_manager.o: rating_manager.cpp rating_manager.h rating.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean run

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

CXXFLAGS = -std=c++17 -Wall -g -I../include