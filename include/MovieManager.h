#pragma once
#include "BaseManager.h" 
#include "Movie.h"
#include <vector>
#include <string>

// BaseManager를 상속받아 특정 데이터 관리만 전담
class MovieManager : public BaseManager {
private:
    std::vector<Movie> movies;

public:
    void addMovie(const Movie& m);          
    void searchByTitle(const std::string& title) const; 
    void displayAll() const;                 
    void sortByRating();      
    void updateMovieRating(int movieId, double score);
    
    // M4 확장 기능 - ID로 장르 검색
    std::string getGenreById(int movieId) const; 

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};