#pragma once
#include <vector>
#include <string>
#include "movie.h" 

class MovieManager {
private:
   
    std::vector<Movie> movies;

public:
   
    void addMovie(const Movie& m);          
    void searchByTitle(const std::string& title) const; 
    void displayAll() const;                 
    void sortByRating();                    
};