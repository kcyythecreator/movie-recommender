<C++ Movie Recommender System 영화 추천 시스템 (M4)>

1. 프로젝트 개요
    -c++을 기반으로 작성된 맞춤형 영화 추천 시스템이다. 
    -객체 지향 프로그래밍의 핵심 원리인 캡슐화, 상속, 다형성을 적용하였고, STL을 이용하여 데이터를 효율적으로 관리하고 추천 알고리즘을 최적화하였다.

2. 주요 기능
    1) 데이터 관리 Manage System
    -영화(Movie),사용자(User),평점(Rating) 데이터의 추가 및 검색
    -CSV 파일의 I/O를 통한 영구적인 데이터 저장 및 불러오기
    -데이터 파싱 오류를 방어하는 예외 처리 (try-catch)적용

    2) 맞춤형 추천 알고리즘 Recommender
    -두 사용자 간의 공통 영화 평가 기록을 이용해 유사도를 계산 (sort와 Lamda식을 활용해 유사도 및 추천 점수 내림차순 정렬)
    -RAII 패턴을 활용한 'Timer'클래스로 추천 알고리즘 소요 시간 측정
    
    3) ***  장르 필터링 Genre Filter(확장기능) ***
    -copy_if와 람다식을 이용하여 특정 장르의 영화만 필터링하여 추천하는 기능 추가
    -기존 함수의 기능을 망가뜨리지 않도록 기본인자를 활용하여 호환성 유지

3. 클래스 구조
    -Data Classes: `Movie`, `User`, `Rating` (순수 데이터 컨테이너, 캡슐화 적용)
    -Manager Classes(상속 및 다형성): `BaseManager` (순수 가상 함수와 가상 소멸자를 포함하는 추상 클래스) 
     `MovieManager`, `UserManager`,`RatingManager` (`BaseManager`를 상속받아 오버라이딩)
    -Algorithm Classes: `Recommender` (추천 로직 총괄) 
     `SimilarityCalculator` (유사도 계산 책임을 분리한 정적 클래스)

4. 빌드 방법
    -'Makefile'을 통해 쉽게 빌드 가능 -> terminal에 'make run' 입력해 실행

```bash
# 전체 소스 코드 컴파일 및 실행 파일 생성 (최적화 옵션 -O2 적용됨)
$ make

# 프로그램 실행
$ ./movie_app
# 또는
$ make run

# 컴파일된 목적 파일(*.o) 및 실행 파일 정리
$ make clean
```

5. 작성자
    -숭실대학교 컴퓨터학부 2학년
    -학번/이름 : 20253018/최윤영