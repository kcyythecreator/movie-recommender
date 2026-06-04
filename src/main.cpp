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
    cout << "  9. 맞춤 영화 추천 받기 (장르 필터 지원)\n\n";
    
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

    Recommender recommender(movieMgr, ratingMgr, userMgr);

    int choice;
    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "숫자를 입력해주세요.\n";
            continue;
        }

        if (choice == 0) {
            cout << "프로그램을 종료합니다.\n";
            break;
        }

        switch (choice) {
            case 1: {
                int id, year; double rating; string title, genre;
                cout << "ID: "; cin >> id;
                cout << "제목: "; cin.ignore(); getline(cin, title);
                cout << "장르: "; getline(cin, genre);
                cout << "출시연도: "; cin >> year;
                cout << "평점: "; cin >> rating;
                movieMgr.addMovie(Movie(id, title, genre, year, rating));
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
                cout << "학번: "; cin >> id;
                cout << "이름: "; cin.ignore(); getline(cin, name);
                cout << "이메일: "; getline(cin, email);
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
                
                // 버퍼 비우기 (cin과 getline 섞임 방지)
                cin.ignore(256, '\n');
                
                cout << "원하는 장르가 있습니까? (없으면 그냥 엔터, 있으면 입력 ex: Action): ";
                string genreInput;
                getline(cin, genreInput);

                // M4 확장 기능 적용: 입력한 장르 필터를 함께 넘겨줌 (비어있으면 전체 검색)
                vector<pair<int, int>> results = recommender.recommend(targetId, 5, 3, genreInput);
                
                if (!results.empty()) {
                    cout << "\n=== 추천 결과 상위 " << results.size() << "개 ===" << endl;
                    for (const auto& r : results) {
                        cout << "추천 영화 ID: " << r.first << " | 매칭 점수: " << r.second << endl;
                    }
                } else {
                    cout << "조건에 맞는 추천 영화가 없습니다." << endl;
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