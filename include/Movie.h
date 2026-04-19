#pragma once
#include <string>
using namespace std;

struct Movie {
    int id;
    string title;
    int year;
    double rating;

    void print() const;
    bool isHighRated() const;
};