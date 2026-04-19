#include <iostream>
#include <vector>
#include "movie.h"
#include "user.h"
#include "rating.h"

int main() {
    std::cout << "=== 영화 목록 ===" << std::endl;
    std::vector<Movie> movies;

    movies.push_back(Movie(1, "Inception", "Sci-Fi", 2010));
    movies.push_back(Movie(2, "Parasite", "Thriller", 2019));
    movies.push_back(Movie(3, "Interstellar", "Sci-Fi", 2014));

    movies[0].addRating(4.5);
    movies[0].addRating(5.0);
    movies[1].addRating(4.0);

    for (const Movie& m : movies) {
        m.display();
    }
    std::cout << "총 " << movies.size() << "편" << std::endl << std::endl;

    std::cout << "=== 사용자 정보 ===" << std::endl;
    User u1(20253108, "최윤영", "choi@ssu.ac.kr");
    u1.display();
    std::cout << std::endl; 

    User u2(20260326, "김숭실", "kim@ssu.ac.kr");
    u2.display();
    std::cout << std::endl;

    std::cout << "=== 평점 정보 ===" << std::endl;
    Rating r1(20253108, 1, 4.5);
    r1.display();
    std::cout << std::endl;

    Rating r2(20260326, 2, 7.5); 
    r2.display();
    std::cout << std::endl;

    return 0;
}