#pragma once
#include <string>
#include <iostream>

class Movie {
private:
    int id;
    std::string title;
    std::string genre;
    int year;
    double rating;

public:
    Movie(int id, const std::string& title, const std::string& genre, int year, double rating = 0.0);

    int getId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    int getReleaseYear() const;
    double getRating() const;

    void addRating(double score);

    bool operator<(const Movie& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
};