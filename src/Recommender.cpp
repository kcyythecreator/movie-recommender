#include "Recommender.h"
#include "SimilarityCalculator.h"
#include <cstdlib>
#include <algorithm> 
#include <set>
#include <map>
#include <iostream>
#include <chrono>
#include <string>
#include <iterator>

// RAII 패턴: 타이머 객체의 수명 주기(생성자~소멸자)를 활용해 개발자가 수동으로 시간을 재지 않아도 종료 시 자동 측정
class Timer {
    std::chrono::high_resolution_clock::time_point start;
    std::string label;
public:
    Timer(const std::string& l) : label(l) {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "[" << label << "] 소요 시간: " << us.count() << " us\n";
    }
};

Recommender::Recommender(MovieManager& mm, RatingManager& rm, UserManager& um)
    : movieManager(mm), ratingManager(rm), userManager(um) {}

int Recommender::Similaritycalculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB) {
    int commonCount = 0;
    int scoreDiffSum = 0;

    for (const auto& rA : ratingsA) { 
        for (const auto& rB : ratingsB) {
            if (rA.getMovieId() == rB.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(rA.getScore() - rB.getScore());
            }
        }
    }

    if (commonCount == 0) {
        return SimilarityCalculator::NO_COMMON_MOVIE;
    }
    return (commonCount * SimilarityCalculator::WEIGHT) - scoreDiffSum;
}

std::vector<std::pair<int, int>> Recommender::recommend(int targetUserId, int K, int N, const std::string& genreFilter) {
    // M4 성능 측정용 RAII 타이머 
    Timer t("recommend");

    std::vector<std::pair<int, int>> recommendations;
    std::vector<Rating> myRatings = ratingManager.findByUser(targetUserId);

    if (myRatings.empty()) {
        return recommendations;
    }

    std::set<int> myMovieIds; 
    for (const auto& r : myRatings) { 
        myMovieIds.insert(r.getMovieId()); 
    }

    std::vector<std::pair<int, int>> similarities; 
    std::vector<int> allUserIds = userManager.getAllUserIds(); 

    for (int otherId : allUserIds) {
        if (otherId == targetUserId) continue; 

        std::vector<Rating> otherRatings = ratingManager.findByUser(otherId);
        int sim = SimilarityCalculator::calculate(myRatings, otherRatings);
        
        if (sim != SimilarityCalculator::NO_COMMON_MOVIE) {
            similarities.push_back({otherId, sim}); 
        }
    }

    std::sort(similarities.begin(), similarities.end(),
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second > b.second; 
        });
    
    int limitK = std::min(K, (int)similarities.size()); 
    if (limitK == 0) {
        return recommendations; 
    }

    std::map<int, int> movieScores;

    for (int i = 0; i < limitK; ++i) {
        int similarUserId = similarities[i].first; 
        std::vector<Rating> simUserRatings = ratingManager.findByUser(similarUserId);

         for (const auto& r : simUserRatings) { 
            if (myMovieIds.find(r.getMovieId()) == myMovieIds.end()) {
                movieScores[r.getMovieId()] += r.getScore();
            }
        }
    }

    std::vector<std::pair<int, int>> sortedScores(movieScores.begin(), movieScores.end());
    std::sort(sortedScores.begin(), sortedScores.end(),
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second > b.second;
        });
        
    // M4 확장 기능: 장르 필터 적용 
    std::vector<std::pair<int, int>> filteredScores;
    if (genreFilter.empty()) {
        filteredScores = sortedScores; // 필터 없으면 그대로 사용
    } else {
        std::copy_if(sortedScores.begin(), sortedScores.end(), std::back_inserter(filteredScores),
            [&](const std::pair<int, int>& p) {
                // 영화 ID를 이용해 장르를 가져와서 비교
                return movieManager.getGenreById(p.first) == genreFilter;
            });
    }

    int limitN = std::min(N, (int)filteredScores.size());
    if (limitN == 0) {
        return recommendations; 
    }

    for (int i = 0; i < limitN; ++i) { 
        recommendations.push_back(filteredScores[i]);
    }

    return recommendations; 
}