#include <iostream>
#include <vector>
#include <string>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"
#include "Movie.h"
#include "User.h"
#include "Rating.h"

using namespace std;

void showMenu() {
    cout << "\n=== Movie Recommender ===\n\n";
    
    cout << "[ 영화 ]\n";
    cout << "  1. 영화 추가\n";
    cout << "  2. 제목으로 검색\n";
    cout << "  3. 전체 목록 출력\n";
    cout << "  4. 평점순 정렬 출력\n\n";
    
    cout << "[ 사용자 ]\n";
    cout << "  5. 사용자 추가\n";
    cout << "  6. 사용자 목록 출력\n\n";
    
    cout << "[ 평점 ]\n";
    cout << "  7. 평점 입력\n";
    cout << "  8. 영화별 평점 보기\n\n";

    cout << "[ 추천 ]\n";
    cout << "  9. 맞춤 영화 추천 받기\n\n";
    
    cout << "  0. 종료\n\n";
    
    cout << "선택 > ";
}

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;

    movieMgr.loadFromFile("data/movies.csv");
    userMgr.loadFromFile("data/users.csv");
    ratingMgr.loadFromFile("data/ratings.csv");

    movieMgr.addMovie(Movie(1, "Inception", "Sci-Fi", 2010));
    movieMgr.addMovie(Movie(2, "Parasite", "Thriller", 2019));
    userMgr.addUser(User(20253108, "최윤영", "choi@ssu.ac.kr"));

    Recommender recommender(movieMgr, ratingMgr, userMgr);

    int choice;
    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        if (choice == 0) break;

        switch (choice) {
            case 1: {
                int id, year; string title, genre;
                cout << "영화 ID: "; cin >> id;
                cout << "제목: "; cin.ignore(); getline(cin, title);
                cout << "장르: "; getline(cin, genre);
                cout << "연도: "; cin >> year;
                movieMgr.addMovie(Movie(id, title, genre, year));
                break;
            }
            case 2: {
                string title;
                cout << "검색할 제목: "; cin.ignore(); getline(cin, title);
                movieMgr.searchByTitle(title);
                break;
            }
            case 3: movieMgr.displayAll(); break;
            case 4: movieMgr.sortByRating(); break;
            case 5: {
                int id; string name, email;
                cout << "사용자 학번: "; cin >> id;
                cout << "이름: "; cin >> name;
                cout << "이메일: "; cin >> email;
                userMgr.addUser(User(id, name, email));
                break;
            }
            case 6: userMgr.displayAllUsers(); break;
            case 7: {
                int uId, mId; double score;
                cout << "사용자 학번: "; cin >> uId;
                cout << "영화 ID: "; cin >> mId;
                cout << "평점(0-5): "; cin >> score;
                movieMgr.updateMovieRating(mId, score); 
                ratingMgr.addRating(Rating(uId, mId, score));
                break;
            }
            case 8: {
                int mId;
                cout << "조회할 영화 ID: "; cin >> mId;
                ratingMgr.displayRatingsByMovie(mId);
                break;
            }
            case 9: {
                int targetId;
                cout << "추천받을 사용자 학번 입력: "; cin >> targetId;
                vector<pair<int, int>> results = recommender.recommend(targetId, 5, 3);
                if (!results.empty()) {
                    cout << "\n=== 추천 결과 상위 3개 ===" << endl;
                    for (const auto& r : results) {
                        cout << "추천 영화 ID: " << r.first << " | 매칭 점수: " << r.second << endl;
                    }
                }
                break;
            }
            default: cout << "잘못된 선택입니다.\n";
        }
    }

    movieMgr.saveToFile("data/movies.csv");
    userMgr.saveToFile("data/users.csv");
    ratingMgr.saveToFile("data/ratings.csv");

    return 0;
}