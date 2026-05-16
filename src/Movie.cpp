#include "Movie.h"

Movie::Movie(int id, const std::string& title, const std::string& genre, int year, double rating)
    : id(id), title(title), genre(genre), year(year), rating(rating) {}

int Movie::getId() const { 
    return id; 
}

std::string Movie::getTitle() const { 
    return title; 
}

std::string Movie::getGenre() const { 
    return genre; 
}

int Movie::getReleaseYear() const { 
    return year; 
}

double Movie::getRating() const { 
    return rating; 
}

void Movie::addRating(double score) {
    if (rating == 0.0) {
        rating = score;
    } else {
        rating = (rating + score) / 2.0;
    }
}

bool Movie::operator<(const Movie& other) const {
    return this->rating > other.rating;
}

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
    os << "[" << movie.id << "] " << movie.title << " (" << movie.year << ", " << movie.genre << ") - 평점: " << movie.rating;
    return os;
}