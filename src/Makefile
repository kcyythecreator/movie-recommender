CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET   = movie_app
OBJS     = main.o movie.o user.o rating.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp movie.h user.h rating.h
	$(CXX) $(CXXFLAGS) -c $<

movie.o: movie.cpp movie.h
	$(CXX) $(CXXFLAGS) -c $<

user.o: user.cpp user.h
	$(CXX) $(CXXFLAGS) -c $<

rating.o: rating.cpp rating.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean run

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)