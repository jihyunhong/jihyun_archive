# 430.211 프로그래밍 방법론 : Project2

<br/>
<br/>

# SNU Music 
- 간편결제 시스템을 탑재한 음악 다운로드 서비스
- 간편 결제 시스템 SNU PAY (은행계좌 잔고로부터 SNU Money 충전, 체크카드 등록)
- 음악 관리 시스템 (앨범 별 음악 관리, 시스템으로부터 음악별 및 앨범별 다운로드)
<br/>
<br/>

## 파일 구성:
- bank.cpp / bank.h : 은행 계좌 클래스 BankAccount
- card.cpp / card.h : 체크카드 클래스 Card
- client.cpp / client.h : 고객 클래스 Client
- music.cpp / music.h : 음악 클래스 Music & 앨범 클래스 Album
- SNUMusicSystem.cpp / SNUMusicSystem.h : 관리 시스템 클래스 SNUMusicSystem
- main.cpp / musicList.txt
<br/>
<br/>

## 클래스 설명:
### class BankAccount
1. Member Variable
- const std::string bankName (은행 계좌 이름)
- int balance (은행 잔고)
2. Member Function
- Constructor로 은행 이름과 잔고를 자유롭게 초기 설정 기능
- Member Variable Getter 함수
- 은행 예금 / 출금 기능
- 출금의 경우 잔고가 부족할 시 실패
<br/>
<br/>

### class Card
1. Member Variable
- const std::string cardName (카드 이름)
- BankAccount* withdrawalAccount (출금 계좌)
2. Member Function
- 이 클래스는 신용카드가 아니라 체크카드를 상징합니다
- Constructor 로 카드 이름과 출금 계좌를 지정해야 한다
- Member Variable 의 Getter 함수
- 결제 기능
- 은행계좌와 마찬가지로 출금 계좌의 잔고가 부족하면 결제가 실패
<br/>
<br/>

### class Card
1. Member Variable
- const std::string clientName (고객 이름)
- int SNUMoney (은행계좌로부터 충전해서 사용하는 온라인 캐시 SNU Money 카드로 충전 불가능)
- BankAccount * accountList[5] (등록한 은행계좌 리스트 , 5 개까지 가능)
- Card* cardList[5] (등록한 카드 리스트 , 5 개까지 가능)
- Album albumList [100] (SNU Music 에서 구매한 앨범 리스트 , 앨범 전체를 구매하지 않아도 음악은 해당 리스트에 앨범 별로 보관)
- int numAlbums (고객이 구매한 앨범의 개수/ 앨범 전체를 구매하지 않고, 한 앨범의 한 트랙만 가지고 있어도 카운트)
2. Member Function
- Constructor
- Getter
- 간편 결제 시스템 SNU PAY
- 등록한 은행 계좌로부터 SNU Money 충전
- 은행 계좌 등록
- 카드 등록
- SNU Money 를 이용한 앨범 및 음악 결제
- 카드를 이용한 앨범 및 음악 결제
- 가지고 있는 앨범 및 음악 리스트 관리
- 은행 계좌에서 바로 결제할 수는 없음 (SNU Money 를 충전하여서 이용)
- 카드로는 SNU Money 충전이 불가
- 잔고 부족 시 결제 실패
<br/>
<br/>

### class Music
1. Member Variable
- std::string musicName (음악 트랙의 제목)
- Album* album (이 음악이 들어있는 앨범의 포인터)
- bool owned (고객이 이 음악을 가지고 있는지 여부)
2. Member Function
- Constructor (이 클래스는 앨범 안에 들어 있는 한 트랙을 상징합)
- owned 는 client 의 albumList 안에서만 의미가 있음 (SNUMusicSystem 안에서는 항상 false)
- 이 클래스는 복사될 수 있음에 유의하세요 (ex) SNUMusicSystem 에서 client 의 albumList 로 복사)
<br/>
<br/>

### class Album
1. Member Variable
- std::string albumName (앨범의 이름)
- std::string artistName (아티스트의 이름)
- int numMusic (앨범의 수록곡 개수)
- Music** musicList (앨범 수록곡의 dynamic array, Music* 의 array)
2. Member Function
- Constructor
- Operator ==
<br/>
<br/>

### class class SNUMusicSystem
1. Member Variable
- Client* client (고객 단 한 명만 이용)
- Album** albumList (SNUMusicSystem 에 등록된 전체 앨범 리스트 (owned = false), Album* 의 array)
- int numAlbum (SNUMusicSystem 에 등록된 전체 앨범의 개수)
<br/>
<br/>

#### 10 가지 서비스 제공
0. Show entire album list
    - 시스템에 존재하는 전체 앨범 리스트 출력
<br/>

1. Purchase an entire album
    - 앨범 전체를 구매
    - 가격 : 700 * 앨범 전체 곡 개수 )
    - 단 , 1000 * 앨범 수록곡 중 아직 갖고 있지 않은 곡의 수 ) ₩ 이 더 저렴할 경우 , 해당 가격으로 결제
<br/>

2. Purchase a song
    - 곡 한 개를 구매 : 1000 원
<br/>

3. View my song list
    - 내가 가지고 있는 앨범 및 곡 목록 출력
<br/>

4. View my SNU Money balance
    - 내가 가지고 있는 SNU Money 충전금 출력 이미 거의 구현
<br/>

5. Charge SNU Money
    - 은행 계좌로부터 SNU Money 충전
<br/>

6. Register a bank account to SNU PAY
    - SNU PAY 에 은행 계좌 등록
<br/>

7. Register a card to SNU PAY
    - SNU PAY 에 카드 등록
<br/>

8. View my bank account list
    - SNU PAY 에 등록된 은행 계좌 목록 출력
<br/>

9. View my card list
    - SNU PAY 에 등록된 카드 목록 출력
<br/>
<br/>
