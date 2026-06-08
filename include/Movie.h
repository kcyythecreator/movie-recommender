#pragma once
#include <string>
#include <iostream>

// 데이터 보호를 위해 멤버 변수를 private으로 캡슐화하고, 외부 조작은 getter/setter로만 허용
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