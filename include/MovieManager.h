#pragma once
#include "BaseManager.h" 
#include "Movie.h"
#include <vector>
#include <string>

class MovieManager : public BaseManager {
private:
    std::vector<Movie> movies;

public:
    void addMovie(const Movie& m);          
    void searchByTitle(const std::string& title) const; 
    void displayAll() const;                 
    void sortByRating();      
    void updateMovieRating(int movieId, double score);

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};