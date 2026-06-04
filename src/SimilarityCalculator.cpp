#include "SimilarityCalculator.h"
#include <cstdlib> 

int SimilarityCalculator::calculate(
    const std::vector<Rating>& user1,
    const std::vector<Rating>& user2) 
{
    int commonCount = 0;   
    int scoreDiffSum = 0;  

    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {
            if (r1.getMovieId() == r2.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
            }
        }
    }

    // 공통으로 평가한 영화가 아예 없는 경우, 취향 비교가 무의미하므로 예외 상수 반환
    if (commonCount == 0) {
        return NO_COMMON_MOVIE;
    }

    // 공통 영화가 많을수록 높은 기본 점수(가중치)를 주고, 평점 차이가 클수록 감점하여 유사도 도출
    return (commonCount * WEIGHT) - scoreDiffSum;
}