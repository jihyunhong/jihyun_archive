406.426B 데이터관리와 분석
2021년 1학기

# Project #2: DB mining & Automated Recommendation System

## 프로젝트의 목표:
본 프로젝트는 추가로 제공된 데이터를 바탕으로 프로젝트 #1의 방법으로 DB를 구축하고 이를 이
용하여 DB mining 및 Automated Recommendation System 구현을 목적으로 한다. 
본 프로젝트는 크게 세 부분으로 나뉘며 Python과 MySQL을 사용하여 구현하여야 한다.
</br>
</br>
PART Ⅰ. 의사결정나무 </br>
PART Ⅱ. 연관분석 </br>
PART Ⅲ. 추천시스템 </br>
</br>

프로젝트 #2 수행에 앞서 이를 위한 데이터베이스 구축을 할 때 각 table의 column들의 순서, 자
료형, 제약은 첨부한 예시 코드를 따르도록 한다. 데이터는 프로젝트 #2에서 새로 첨부한 데이터를
insert하도록 한다.


## PART Ⅰ. 의사결정나무
PART Ⅰ는 사이트 A에서 BEST item으로 선정한 아이템 기준에 대한 의사결정나무를 만드는 것을
목표로한다. R1-1과 R1-2에서는 의사결정나무를 구성할 데이터를 만들기 위해 mysql-connectorpython을
사용해서 query를 실행하는 것을, R1-3에서는 python의 sklearn 라이브러리를 사용해서 의
사결정나무를 만들고 graphviz 라이브러리를 사용해서 결과를 시각화하는 것을 수행한다. R1-4에서는
R1-3에서 생성한 의사결정나무와는 다른 BEST item 선정 여부에 대한 의사결정나무를 만들어보는 것
을 목표로 한다.
- (R1-1) </br>
사이트 A는 사이트 유지 및 활성화에 기여하는 아이템들을 BEST item으로 선정한다. 이 사이트의
BEST item 선정 기준을 파악해보고자 한다. 먼저 주어진 best_item_list.txt를 반영하기 위해
DMA_project2의 item 테이블에 best_item이라는 새로운 column을 추가한다. 이 때, best_item의 데이
터형은 TINYINT(1)이며 Default 값은 0이다. 만약 아이템의 id가 best_item_list.txt에 포함된다면 해
당 아이템의 best_item의 값에 1을 저장한다.
- (R1-2) </br>
결과물: DMA_project2_team##_part1.csv </br>
다음과 같은 column이 포함되는 결과를 반환하는 쿼리를 작성하라. 단, Nested query를 이용하여 하
나의 SQL 문장으로 작성하여야 한다. 결과는 DMA_project2_team##_part1.csv에 저장되어야 한다.
    - id: 아이템의 id
    - best_item: 아이템의 BEST item 선정 여부
    - ratings: 아이템이 사용자들에게 받은 평가 점수 ( [-4, +4] 범위의 값, 0은 중립 )
    - num_of_specs: 아이템이 가진 스펙의 수
    - num_of_tags: 아이템에 붙어 있는 태그의 수
    - num_of_users: 아이템을 이용한 이력이 있는 사용자의 수
    - avg_usage_time: 아이템을 이용한 사용자들의 인당 평균 이용 시간 ( 사용자 한 명의 이용 시간
    은 가입 이래 총 이용 시간 )
    - num_of_reviews: 아이템에 작성된 리뷰의 수
    - sum_of_recommend: 아이템에 작성된 리뷰의 recommend 총합 ( -1도 포함 )
    - avg_review_len: 아이템에 작성된 리뷰의 평균 본문 길이

- (R1-3) </br>
결과물: DMA_project2_team##_part1_gini.pdf, DMA_project2_team##_part1_entropy.pdf </br>
R1-2에서 반환 받은 결과로부터 BEST 아이템 선정 기준에 대한 의사결정나무를 생성하고자 한다.
Node impurity 측정 방식을 gini와 entropy 두 가지로 하여 각각 의사결정 나무를 생성하며, 그 결과
는 graphviz를 통해 저장되어야 한다. 본 문제에서 만드는 의사결정나무의 속성은 아래와 같다. 보고
서에는 이를 바탕으로 만들어진 의사결정나무를 간단히 분석하는 내용이 포함되어야 한다.
    - 사용 라이브러리: sklearn.tree.DecisionTreeClassifier
    - Node impurity criterion: gini / entropy
    - 결과 파일명: node impurity criterion에 따라 DMA_project2_team##_part1_gini.pdf,
    DMA_project2_team##_part1_entropy.pdf 로 구분함.
    - 분석 목표: BEST 아이템 선정 기준
    - min_samples_leaf: 10
    - max_depth: 5
    - feature names: ratings, num_of_specs, num_of_tags, num_of_users, avg_usage_time,
    num_of_reviews, sum_of_recommend, avg_review_len
    - class names: normal, BEST
- (R1-4) </br>
R1-3에서 생성한 의사결정나무와는 다른 BEST 아이템 선정 기준에 대한 의사결정나무를 만들고
R1-3에서 생성한 의사결정나무와 비교하라. R1-3 외에 다른 input feature를 추가로 사용하거나 제거
할 수도 있고, 의사결정나무의 다른 속성을 변경할 수도 있다. 보고서에는 다음과 같은 내용이 포함되
어야 한다.
    - 의사결정나무에 사용된 input features
    - Node impurity criterion
    - sklearn.tree.DecisionTreeClassifier에 입력한 속성 ( ex. max_depth=3 )
</br>
</br>

## PART Ⅱ. 연관분석
PART Ⅱ 연관분석에서는 사이트 A의 bundle들간의 연관 분석을 목표로 한다. R2-1과 R2-2에서는
연관분석과 추천시스템을 위한 view 생성을 위해 mysql-connector-python을 사용하여 query를 실행
하는 것을, R2-3에서는 R2-2의 view에서 연관분석을 위한 horizontal table의 결과를 반환하는 것을
목표로 하며, R2-4에서는 python의 mlxtend 라이브러리를 사용하여 연관분석을 수행하고 결과를 출력하는 것을 목표로 한다.

- (R2-1) </br>
결과물: DMA_project2_team##_part2_bundle.csv </br>
본 연관분석에서는 포함된 아이템의 수, 관련된 장르의 수, 포함된 아이템을 이용한 사용자의 수가
많은 상위 30개의 bundle에 대해 진행하고자 한다. 분석을 위해 하나의 SQL 문장으로 아래의
column들이 포함되는 bundle_score라는 이름을 가지는 view를 생성하라.
    - bundle_id: 번들의 id
    - bundle_name: 번들의 name
    - num_item: 해당 번들에 포함된 아이템 수*100
    - num_genre: 해당 번들과 관련된 장르 수*100
    - num_user: 해당 번들에 포함된 아이템을 이용한 이력이 있는 사용자 수
    - score: num_item+num_gerne+num_user 의 값
이 때, score를 기준으로 내림차순 정렬되어야 하며 이를 기준으로 상위 30개만을 view에 저장해야
한다. 그리고 해당 view를 DMA_project2_team##_part2_bundle.csv에 저장하라.

- (R2-2) </br>
결과물: DMA_project2_team##_part2_UBR.csv
</br>
연관분석과 추천시스템을 위해 각 user가 bundle에 대해 가지는 관심 정도를 rating으로 정의하고자
한다. 이는 아래와 같이 정의된다. 단, 사용자가 추천/리뷰/이용 활동을 전혀 하지 않은 아이템만이 포
함된 bundle의 경우 0점이 아니라 rating을 하지 않은 것으로 한다. 여기서 '추천'은 사용자가 아이템
에 남긴 review에서 recommend 정보가 1인 것을 의미한다.
    - < Rating Equation > </br>
    rating(user, bundle) = 5 * (user가 해당 bundle에 포함된 아이템 중 추천한 아이템 개수) + min(user가 이용한 이력이 있는 item이 해당 bundle에 포함된 개수, 5)</br></br>

    예를 들어, a라는 사용자가 bundle_b에 포함된 item_c를 추천했고 bundle_b에 포함된 item 10개에 대해 이용 이력이 존재한다면 rating(user_a, bundle_b) = 5*1 + min(10, 5) 로 해당 bundle에 10이라는 관심 정도를 가진 것이다. 또 d라는 사용자가 bundle_b에 포함된 item에 추천을 남긴 리뷰는 없으나 이에 포함되는 4개의 item에 대해 이용 이력이 존재한다면 rating(user_d, bundle_b) = 5*0 + min(4, 5) 로 해당 bundle에 4라는 관심 정도를 가진 것이다. 
    </br>
    R2-1에서 정의한 총 30개의 bundle에 대해 user들의 rating 정보를 user_bundle_rating 이라는 이름의 view로 생성하여야 한다. 하나의 SQL 문장을 이용하고 이 때 bundle은 R2-1의 총 30개에 대해서만 저장되어야 하며, rating 정보가 있는 user-bundle set에 대해서만 저장해야 한다.
    </br>
    아래의 column들을 포함하는 user_bundle_rating 이라는 이름을 가지는 view를 생성하라.
    - user: user_id
    - bundle: 번들 이름 ( 상위 30개 중 하나 )
    - rating: 위에서 정의한 user가 bundle에 가지는 관심 정도 ( >= 1 ) </br> </br>

    위의 view를 만든 후, 이 view 안에서 20개 이상의 rating 정보를 가진 user들에 대한 정보만을 남
    긴 partial_user_bundle_rating 이라는 이름을 가진 view를 생성하라. partial_user_bundle_rating이 가
    지는 column은 user_bundle_rating과 동일해야 한다. 이 partial_user_bundle_rating view를
    DMA_project2_team##_part2_UBR.csv에 저장하라.

- (R2-3) </br>
결과물: DMA_project2_team##_part2_horizontal.pkl </br>
연관분석을 위해 vertical table 형태의 partial_user_bundle_rating을 horizontal table로 만든 결과를
pandas의 DataFrame으로 저장하라. DataFrame은 user id를 index로 가져야 하며, bundle name들을
column 명으로 가져야 한다. partial_user_bundle_rating에 해당 user의 해당 bundle에 대한 rating 정
보가 있다면 1, 없다면 0을 저장해야 한다. 저장된 DataFrame의 각 user는 연관분석의 transaction 역
할을, 각 bundle은 연관분석의 item 역할을 하게 된다.
이 때 horizontal table로 만들기 위해 sql query문을 사용하여도 되고, pandas 라이브러리를 사용하여
도 된다. 해당 horizontal table을 DMA_project2_team##_part2_horizontal.pkl에 저장하라.

- (R2-4) </br>
결과물: DMA_project2_team##_part2_association.pkl
</br>
R2-3에서 만든 DataFrame을 사용해서 다음의 조건을 만족하는 frequent itemset을 만들고 연관분석
을 수행하라. 그리고 이 결과에 대한 간략한 정성적, 정량적 평가를 수행하라.
    - Frequent itemset의 최소 support: 0.35
    - 연관분석 metric: lift ( lift >= 2 인 것들을 출력 )
    - 결과 파일명: DMA_project2_team##_part2_association.pkl
    </br> </br>

## PART Ⅲ. 추천시스템
PART Ⅲ 추천시스템에서는 사용자들에게 bundle을 추천하는 추천시스템 구현을 목적으로 한다.
R3-1에서는 점수 예측 결과를 반환하는 함수 작성을, R3-2부터 R3-4까지는 recommendation system
을 구현하도록 한다. 이 때 라이브러리로는 surprise를 이용한다.

- (R3-1) </br>
점수 예측 결과 top-n개 결과를 반환하는 get_top_n 함수를 작성하라. 세부 내용은 뼈대 코드를
참고하여 작성하도록 한다.

- (R3-2) </br>
User-based Recommendation 결과물: 3-2-1.txt, 3-2-2.txt
['8051826169', '8027368512', '7998746368', '8054453794', '8030770479'] 의 총 5명 user에 대하여 다
음의 알고리즘과 유사도 함수를 사용한 추천 결과 top-5 bundle을 텍스트 파일로 출력하라.
    - 알고리즘 : KNNBasic 유사도: cosine 파일명: 3-2-1.txt
    - 알고리즘 : KNNWithMeans 유사도: pearson 파일명: 3-2-2.txt </br></br>

    또한, User-based recommendation에서 다양한 알고리즘과 유사도 함수를 적용해보고 cross
validation(k=5, random_state=0)을 기준으로 가장 좋은 성능을 보이는 모델을 제출하라.
(R3-3) Item-based Recommendation 결과물: 3-3-1.txt, 3-3-2.txt
['World of Magicka Bundle', 'Borderlands Triple Pack', 'Tripwire Complete Bundle', 'Grand Theft Auto
V & Great White Shark Cash Card', 'Killing Floor 1 Complete Your Set!'] 의 총 5개 bundle에 대해 다
음 알고리즘과 유사도 함수를 사용한 추천 결과 top-10 user를 텍스트 파일로 출력하라.</br></br>

    - 알고리즘 : KNNBasic 유사도: cosine 파일명: 3-3-1.txt
    - 알고리즘 : KNNWithMeans 유사도: pearson 파일명: 3-3-2.txt </br> </br>
    
    또한, Item-based recommendation에서 다양한 알고리즘과 유사도 함수를 적용해보고 cross
validation(k=5, random_state=0)을 기준으로 가장 좋은 성능을 보이는 모델을 제출하라.
(R3-4) Matrix-based Recommendation 
</br>
결과물: 3-4-1.txt, 3-4-2.txt, 3-4-3.txt, 3-4-4.txt
['8051826169', '8027368512', '7998746368', '8054453794', '8030770479'] 의 총 5명 user에 대하여 다
음의 알고리즘을 사용한 추천 결과 top-5 bundle을 텍스트 파일로 출력하라.
</br></br>
    - SVD(n_factors=100, n_epoch=50, biased=False) 파일명: 3-4-1.txt
    - SVD(n_factors=200, n_epoch=100, biased=True) 파일명: 3-4-2.txt
    - SVD++(n_factors=100, n_epoch=50) 파일명: 3-4-3.txt
    - SVD++(n_factors=100, n_epoch=100) 파일명: 3-4-4.txt</br></br>

    또한, Matrix-based recommendation에서 다양한 알고리즘과 유사도 함수를 적용해보고 cross
    validation(k=5, random_state=0)을 기준으로 가장 좋은 성능을 보이는 모델을 제출하라.