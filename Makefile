CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRCDIR = src
INCDIR = include
OBJDIR = obj

OBJECTS = $(OBJDIR)/main.o \
          $(OBJDIR)/Movie.o \
          $(OBJDIR)/MovieManager.o \
          $(OBJDIR)/User.o \
          $(OBJDIR)/UserManager.o \
          $(OBJDIR)/Rating.o \
          $(OBJDIR)/RatingManager.o \
          $(OBJDIR)/Recommender.o \
          $(OBJDIR)/SimilarityCalculator.o

TARGET = movie_app

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all run clean