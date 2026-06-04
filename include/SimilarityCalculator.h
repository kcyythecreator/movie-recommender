#pragma once
#include <vector>
#include "Rating.h" 

class SimilarityCalculator {
public:
    // 매직 넘버 제거: 공통 영화가 없을 때 반환할 예외 값
    static constexpr int NO_COMMON_MOVIE = -100;
    // 매직 넘버 제거: 공통 영화 개수에 곱해줄 가중치
    static constexpr int WEIGHT = 10;

    static int calculate(
        const std::vector<Rating>& user1,
        const std::vector<Rating>& user2
    );
};