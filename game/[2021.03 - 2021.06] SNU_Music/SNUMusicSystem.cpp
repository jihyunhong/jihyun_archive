#include "SNUMusicSystem.h"

SNUMusicSystem::~SNUMusicSystem() {
  // TODO
  // implement memory-safe destructor!
    for (int i=0; i<numAlbum; i++){
        //for (int j=0; j<albumList[i]->GetNumMusic(); j++){
        //    delete (albumList[i]->GetMusicList())[j];
        //}
        delete albumList[i];
    }
    delete []albumList;
    delete client;
}

void SNUMusicSystem::Loop() {
  while(true) {
    std::cout << std::endl
    << "Choose Service"<< std::endl 
    << "  0: Show entire album list" << std::endl
    << "  1: Purchase an entire album" << std::endl
    << "  2: Purchase a song" << std::endl
    << "  3: View my song list" << std::endl
    << "  4: View my SNU Money balance" << std::endl
    << "  5: Charge SNU Money" << std::endl
    << "  6: Register a bank account to SNU PAY" << std::endl
    << "  7: Register a card to SNU PAY" << std::endl
    << "  8: View my bank account list" << std::endl
    << "  9: View my card list" << std::endl
    << "  10: Quit" << std::endl;

    std::cout << "What service do you need?: ";
    int choice;
    std::cin >> choice;

    std::cout << std::endl;
    if(choice == 0) PrintEntireAlbumList();
    else if(choice == 1) PurchaseAlbum();
    else if(choice == 2) PurchaseSong();
    else if(choice == 3) client->PrintMusicList();
    else if(choice == 4) PrintSNUMoney();
    else if(choice == 5) ChargeSNUMoney();
    else if(choice == 6) RegisterBankAccount();
    else if(choice == 7) RegisterCard();
    else if(choice == 8) client->PrintBankAccountList();
    else if(choice == 9) client->PrintCardList();
    else if(choice == 10) break;
    else {
      std::cout << "Wrong Input, Choose Again!" << std::endl;
    } 
  }
}

// service 0
void SNUMusicSystem::PrintEntireAlbumList(){
  for(int i = 0; i < numAlbum; i++) {
    std::cout << std::right << std::setw(4) << i << ". ";
    albumList[i]->PrintAlbumName();
  }
}

// service 1
void SNUMusicSystem::PurchaseAlbum(){
  
  PrintEntireAlbumList();
  std::cout << "Choose the album number: ";
  int albumNumber;
  std::cin >> albumNumber;
  if(albumNumber < 0 || albumNumber >= numAlbum) {
    std::cout << "Wrong Album Number!" << std::endl;
    return;
  }
  
  // TODO
    
    int payment;
    int totalAlbumPrice = albumList[albumNumber]->GetNumMusic() * 700;
    int sign = 0;
    Music** musicList;
    
    // 구매하려고 하는 앨범이 기존 보유 중인지, 아닌지 판단
    for (int i=0; i<client->GetNumAlbums(); i++){
        if (*albumList[albumNumber] == client->GetAlbum(i)) { // 앨범이 겹친다면
            musicList = client->GetAlbum(i).GetMusicList();
            sign = 1; // 아래 if문에서 사용
            break;
        }
    }
    
    // 총 (예정) 결제 대금 계산
    if (sign == 1) { // 구매하려고 하는 앨범이 기존 보유 중인 경우
        int leftSongNum = 0;
        for (int i=0; i<albumList[albumNumber]->GetNumMusic(); i++){
            if (musicList[i]->IsOwned() == false){
              leftSongNum += 1;
            }
        }
        if (leftSongNum == 0) { // 만약 현재 해당 앨범 수록곡 전체 소유 중이라면
            std::cout << "You already have the entire songs in this album. Bye" << std::endl;
            return;
        }
        int leftSongsPrice = leftSongNum * 1000;
        if (leftSongsPrice < totalAlbumPrice) {
            payment = leftSongsPrice;
        }
        else {
            payment = totalAlbumPrice;
        }
    }
    else { // 구매하려고 하는 앨범이 보유 중이지 않은 경우
        payment = totalAlbumPrice;
    }

    // 결제 방법 선택
    std::cout << "0. SNUMoney" << std::endl;
    std::cout << "1. Card" << std::endl;
    std::cout << "Select a payment method: ";
    int paymethod;
    std::cin >> paymethod;
    
    // 결제
    if (paymethod == 0) { // SNUMoney로 결제
        bool result1 = client->PayBySNUMoney(payment); // 결제 가능 여부 확인
        if (result1) { // 결제 가능
            bool result2 = client->AddAlbum(*albumList[albumNumber]); // 앨범 추가 가능 여부 확인
            if (result2) { // 앨범 추가 가능
                std::cout << "Successfully Purchased the Album " << albumNumber << "!!!" << std::endl;
            }
            else { // 결제 가능, but 앨범 추가 불가
                std::cout << "You can't add an album anymore. Payment is cancelled." << std::endl;
                bool temp = client->PayBySNUMoney(-payment); // 환불
            }
        }
        else { // 결제 불가
            std::cout << "Balance is not enough. Invalid Payment." << std::endl;
        }
    }
    else if (paymethod == 1) { // Card로 결제
        client->PrintCardList();
        std::cout << "Select a Card: ";
        int cardIndex;
        std::cin >> cardIndex;
        bool result1 = client->PayByCard(payment, cardIndex);
        if (result1) { // 결제 가능
            bool result2 = client->AddAlbum(*albumList[albumNumber]); // 앨범 추가 가능 여부 확인
            if (result2) { // 앨범 추가 가능
                std::cout << "Successfully Purchased the Album " << albumNumber << "!!!" << std::endl;
            }
            else { // 결제 가능, but 앨범 추가 불가
                std::cout << "You can't add an album anymore. Payment is cancelled." << std::endl;
                bool temp = client->PayByCard(-payment, cardIndex); // 환불
            }
        }
        else { // 결제 불가
            std::cout << "Balance is not enough. Invalid Payment." << std::endl;
        }
    }
    else {
        std::cout << "Wrong payment method number!" << std::endl;
        return;
    }
    
    

  
  // TODO - explanation
  // implement album purchasing management
  // and payment
  // this step can fail due to various reasons
  // -not enough SNUMoney balance, if SNUMoney was chosen
  // -not enough bank account balance for card payments
  // -wrong indices chosen
  // -client already have the album in the client's albumList
  // -etc
  // just return in those cases

  // price of a album: 700 * (number of songs in the album)
  // however, if the price of buying the songs, that the client
  // does not have, one by one is cheaper,
  // that price is applied.
  // i.e. 1000 * (number of songs in the album that client do not have)
  //
  // for example, when album is composed of 10 songs 
  // and the client already have 4 songs among them and
  // do not have only 6 songs,
  // 6000 won will be charged, not 7000 won.
}

// service 2
void SNUMusicSystem::PurchaseSong(){
    
  PrintEntireAlbumList();
  std::cout << "Choose the album number: ";
  int albumNumber;
  std::cin >> albumNumber;
  if(albumNumber < 0 || albumNumber >= numAlbum) {
    std::cout << "Wrong Album Number!" << std::endl;
    return;
  }

  // show the list of musics in the album
  albumList[albumNumber]->PrintMusics();

  std::cout << "Choose the track number: ";
  int trackNumber;
  std::cin >> trackNumber;
  
  if(trackNumber < 0 || trackNumber >= albumList[albumNumber]->GetNumMusic()) {
    std::cout << "Wrong Track Number!" << std::endl;
    return;
  }

  // TODO
    
    int payment = 1000; // 결제 대금은 항상 1000원
    Music** musicList;
    
    // 구매하려고 하는 곡이 기존 보유 중인지, 아닌지 판단
    for (int i=0; i<client->GetNumAlbums(); i++){
        if (albumList[albumNumber]->GetAlbumName() == client->GetAlbum(i).GetAlbumName()) {
            musicList = client->GetAlbum(i).GetMusicList();
            if (musicList[trackNumber]->IsOwned()){
                std::cout << "You already have this song. Bye." << std::endl;
                return;
            }
            
        }
    }
    /*
    for (int i=0; i<100; i++){
        musicList = client->GetAlbum(i).GetMusicList();
        if (musicList == nullptr) { // client의 i번째 앨범 자리가 비어 있다면
            continue;
        }
        else if (musicList[trackNumber]->IsOwned()){
            std::cout << "You already have this song. Bye." << std::endl;
            return;
        }
    }
    */
    
    musicList = albumList[albumNumber]->GetMusicList();
    
    // 결제 방법 선택
    std::cout << "0. SNUMoney" << std::endl;
    std::cout << "1. Card" << std::endl;
    std::cout << "Select a payment method: ";
    int paymethod;
    std::cin >> paymethod;
    
    // 결제
    if (paymethod == 0) { // SNUMoney로 결제
        bool result1 = client->PayBySNUMoney(payment); // 결제 가능 여부 확인
        if (result1) { // 결제 가능
            bool result2 = client->AddMusic(*musicList[trackNumber]); // 곡 추가 가능 여부 확인
            if (result2) { // 곡 추가 가능
                std::cout << "Successfully Purchased the Song " << trackNumber;
                std::cout << " in the Album " << albumNumber << "!!!" << std::endl;
            }
            else { // 결제 가능, but 곡 추가 불가 (신규 앨범 자리가 꽉 차서...)
                std::cout << "You can't add an album (i.e, song) anymore. Payment is cancelled." << std::endl;
                bool temp = client->PayBySNUMoney(-payment); // 환불
            }
        }
        else { // 결제 불가
            std::cout << "Balance is not enough. Invalid Payment." << std::endl;
        }
    }
    else if (paymethod == 1) { // Card로 결제
        client->PrintCardList();
        std::cout << "Select a Card: ";
        int cardIndex;
        std::cin >> cardIndex;
        bool result1 = client->PayByCard(payment, cardIndex);
        if (result1) { // 결제 가능
            bool result2 = client->AddMusic(*musicList[trackNumber]); // 곡 추가 가능 여부 확인
            if (result2) { // 곡 추가 가능
                std::cout << "Successfully Purchased the Song " << trackNumber;
                std::cout << " in the Album " << albumNumber << "!!!" << std::endl;
            }
            else { // 결제 가능, but 곡 추가 불가 (신규 앨범 자리가 꽉 차서...)
                std::cout << "You can't add an album (i.e, song) anymore. Payment is cancelled." << std::endl;
                bool temp = client->PayByCard(-payment, cardIndex); // 환불
            }
        }
        else { // 결제 불가
            std::cout << "Invalid Payment. (Balance is not enough or No back account exists)" << std::endl;
        }
    }
    else {
        std::cout << "Wrong payment method number!" << std::endl;
        return;
    }
    
  // TODO - explanation
  // implement song purchasing management
  // and payment
  // this step can fail due to various reasons
  // -not enough SNUMoney balance, if SNUMoney was chosen
  // -not enough bank account balance for card payments
  // -wrong indices chosen
  // -client already have that song in the client's albumList
  // -etc
  // just return in those cases
  // price of a song: 1000 won
}
  

// service 4
void SNUMusicSystem::PrintSNUMoney(){
  std::cout << "My SNU Money balance: " << client->GetSNUMoney()
            << " Won." << std::endl;
}

// service 5
void SNUMusicSystem::ChargeSNUMoney(){
  std::cout << "How much money do you want to charge?: ";
  int money;
  std::cin >> money;

  client->PrintBankAccountList();
  std::cout << "Charge from which account?: ";
  int accountIndex;
  std::cin >> accountIndex;
  
  // TODO
  // implement SNU Money charging process
  // this step can fail due to various reasons
  // -low bank account balance, etc 
  if (client->GetBankAccount(accountIndex) == nullptr){
    std::cout << "There is no Bank Account of such index!"<< std::endl;
    return;
  }
  else{
    bool result = client->ChargeSNUMoney(money, accountIndex);
    if (result == true){
      std::cout << "Successfully charged!"<< std::endl;
    }
    else{
      std::cout << "balance is not enough!"<< std::endl;
    }
  }
  return;
}


// service 6
void SNUMusicSystem::RegisterBankAccount(){
  // TODO
  // register bank account to Client Class
  int money;
  std::string bankname;
  std::cout << "Enter the bank name: ";
  std::cin >> bankname;
  std::cout << "How much money is in the bank account? : ";
  std::cin >> money;

  bool result = client->AddBankAccount(bankname, money);
  if (result) {
      std::cout << "Successfully registered!"<< std::endl;
  }
  else {
      std::cout << "Failed to register!"<< std::endl;
  }
}

// service 7
void SNUMusicSystem::RegisterCard(){
  // TODO
  // register card to Client Class
  int money;
  int bankIndex;
  std::string cardname;
  std::cout << "Enter the card name: ";
  std::cin >> cardname;
  client->PrintBankAccountList();
  std::cout << "Which bank?: ";
  std::cin >> bankIndex;
  bool result = client->AddCard(cardname, bankIndex);
  if (result) {
    std::cout << "Successfully registered!"<< std::endl;
  }
  else {
    std::cout << "Failed to register!"<< std::endl;
  }
}




// For Students: You do not need to know what the functions
// below this line does. 
// -------------------------------------------------------------  

SNUMusicSystem::SNUMusicSystem(std::string filename) {
  _LoadMusicList(filename);
  _Initialize();
}

void SNUMusicSystem::_Initialize() {
  std::cout << "Welcome to SNU Music System!" << std::endl;
  // ASCII Art LoL
  std::cout
  << "     _______..__   __.  __    __     .___  ___.  __    __       _______. __    ______ " << std::endl
  << "    /       ||  \\ |  | |  |  |  |    |   \\/   | |  |  |  |     /       ||  |  /      |" << std::endl
  << "   |   (----`|   \\|  | |  |  |  |    |  \\  /  | |  |  |  |    |   (----`|  | |  ,----'" << std::endl
  << "    \\   \\    |  . `  | |  |  |  |    |  |\\/|  | |  |  |  |     \\   \\    |  | |  |     " << std::endl
  << ".----)   |   |  |\\   | |  `--'  |    |  |  |  | |  `--'  | .----)   |   |  | |  `----." << std::endl
  << "|_______/    |__| \\__|  \\______/     |__|  |__|  \\______/  |_______/    |__|  \\______|" << std::endl
  << "                                                                                      " << std::endl;
  
  std::cout << "Enter Your Name: ";
  char nameBuffer[100];
  std::cin.getline(nameBuffer, 100);
  client = new Client(nameBuffer);
}

// Load Music List and Parse Them
// For Students: You do not need to know what this function does
void SNUMusicSystem::_LoadMusicList(std::string filename) {
  std::ifstream musicListFile(filename);
  if(!musicListFile) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    std::cerr << "Check file path." << std::endl;
    exit(1);
  }
  // the csv list is long: 100 lines
  // but may contain duplicate albums
  // so just use 50 albums for siplicity
  numAlbum = 50;
  albumList = new Album* [numAlbum];

  // input csv format
  // albumName[;]artistName[;][/]Track1[/]Track2[/]...[/]TrackN[\r][\n]

  int albumIndex = 0;
  std::string musicBuffer [40]; // temporary track holder
  while (musicListFile.peek() != EOF && albumIndex < numAlbum) {
    std::string albumName, artistName, entireTracks;
    std::getline(musicListFile, albumName, ';');
    std::getline(musicListFile, artistName, ';');
    std::getline(musicListFile, entireTracks);

    entireTracks.erase(0,1);
    int posReturnCarriage = entireTracks.find('\r');
    if(posReturnCarriage != std::string::npos) {
      entireTracks.erase(posReturnCarriage, 1);
    }
    entireTracks = entireTracks + "/";
    int nameStart = 0;
    int nameEnd = entireTracks.find('/');
    // parse track string and split into musicBuffer
    int trackIndex = 0;
    while(nameEnd != std::string::npos && trackIndex < 40) {
      musicBuffer[trackIndex] = entireTracks.substr(nameStart, nameEnd - nameStart);
      nameStart = nameEnd + 1;
      nameEnd = entireTracks.find('/', nameStart);
      trackIndex += 1;
    }
    // check if the same album already exists in the albumList
    bool duplicate = false;
    for(int i=0; i < albumIndex; i++) {
      if(albumList[i]->GetAlbumName() == albumName &&
          albumList[i]->GetArtistName() == artistName) {
        duplicate = true;
        break;
      }
    }
    // fill in album information
    if(duplicate == false) {
      albumList[albumIndex] = new Album(albumName, artistName, trackIndex);
      for(int i = 0; i < trackIndex; i++) {
        (albumList[albumIndex]->GetMusicList())[i] = new Music(musicBuffer[i], albumList[albumIndex]);
      }

      albumIndex += 1;
    }
  }
}
