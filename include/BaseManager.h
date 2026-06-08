#pragma once
#include <string>

// 다형성(Polymorphism)을 활용하여 매니저 객체들을 일관되게 다루기 위한 추상 클래스
class BaseManager {
public:
   
    virtual void loadFromFile(const std::string& filename) = 0; 
    virtual void saveToFile(const std::string& filename) const = 0;
    virtual int size() const = 0;
    // delete 시 자식 객체까지 깔끔하게 지워지도록 가상 소멸자 적용 (메모리 누수 방지)
    virtual ~BaseManager() {} 

};

