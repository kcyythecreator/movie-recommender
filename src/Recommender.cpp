#include "Recommender.h"
#include "SimilarityCalculator.h"
#include <cstdlib> //std::abs (절댓값 계산)
#include <algorithm> 
#include <set> // 중복 없는 탐색
#include <map> // (키-값 쌍 점수 누적)
#include <iostream>

Recommender::Recommender(MovieManager& mm, RatingManager& rm, UserManager& um)
    : movieManager(mm), ratingManager(rm), userManager(um) {}

int Recommender::Similaritycalculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB) {
    int commonCount = 0; // 겹치는 영화 개수
    int scoreDiffSum = 0; // 평점 차이의 합

    for (const auto& rA : ratingsA) { 
        for (const auto& rB : ratingsB) {
            if (rA.getMovieId() == rB.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(rA.getScore() - rB.getScore());
            }
        }
    }

    if (commonCount == 0) {
        return -100;
    }
    return (commonCount * 10) - scoreDiffSum;
}

std::vector<std::pair<int, int>> Recommender::recommend(int targetUserId, int K, int N) {
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

    //유사도 계산
    for (int otherId : allUserIds) {
        if (otherId == targetUserId) continue; 

        std::vector<Rating> otherRatings = ratingManager.findByUser(otherId);
        int sim = SimilarityCalculator::calculate(myRatings, otherRatings);
        if (sim != -100) {
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
    int limitN = std::min(N, (int)sortedScores.size());
    if (limitN == 0) {
        return recommendations; 
    }

    for (int i = 0; i < limitN; ++i) { 
        recommendations.push_back(sortedScores[i]);
    }

    return recommendations; 
}