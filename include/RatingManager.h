#pragma once
#include "BaseManager.h" 
#include "Rating.h" 
#include <vector>
#include <string>

class RatingManager : public BaseManager {
private:
    std::vector<Rating> ratings;

public:
    void addRating(const Rating& r);
    void displayRatingsByMovie(int movieId) const;

    std::vector<Rating> findByUser(int userId) const;


    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};