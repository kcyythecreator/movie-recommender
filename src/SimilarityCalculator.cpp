#include "../include/SimilarityCalculator.h"
#include <cstdlib> // std::abs 사용을 위해 필수!

int SimilarityCalculator::calculate(
    const std::vector<Rating>& user1,
    const std::vector<Rating>& user2) 
{
    int commonCount = 0;   // 공통으로 본 영화 수
    int scoreDiffSum = 0;  // 평점 차이의 합

    // 이중 반복문으로 공통 영화 찾기
    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {
            if (r1.getMovieId() == r2.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
            }
        }
    }

    // 공통 영화가 없으면 비교 불가하므로 -100 반환
    if (commonCount == 0) {
        return -100;
    }

    // 단순 유사도 공식 적용
    return (commonCount * 10) - scoreDiffSum;
}