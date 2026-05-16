#pragma once

class Rating {
private:
    int    userId;
    int    movieId;
    double score;

public:
    Rating(int userId, int movieId, double score);

    int    getUserId()  const;
    int    getMovieId() const;
    double getScore()   const;

    void   display()    const;
};