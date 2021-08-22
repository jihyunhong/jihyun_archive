#include "client.h"

Client::Client(const std::string& name) : clientName(name),
                                          SNUMoney(0),
                                          numAlbums(0) {
  // TODO
  // Initialize Client's SNUMusic Wallet
  // start with SNUMoney 0
  // arrays should be filled with nullptr
  for (int i=0; i<5; i++){
    accountList[i] = nullptr;
    cardList[i] = nullptr;
  }
  for (int i=0; i<100; i++){
    albumList[i] = Album();
  }
}

Client::~Client() {
  // TODO
  // implement memory-safe destructor

  // ---------------------------------------------------------------------확인필요
    for (int i=0; i<5; i++){
        delete accountList[i];
        delete cardList[i];
    }
}

const std::string& Client::GetClientName() const {
  return clientName;
}

int Client::GetSNUMoney() const{
  return SNUMoney;
}

// this function can return nullptr
BankAccount* Client::GetBankAccount(int accountIndex) const {
  if(accountIndex >= 0 && accountIndex < 5) {
    return accountList[accountIndex];
  }
  else {
    return nullptr;
  }
}

// this function can return nullptr
Card* Client::GetCard(int cardIndex) const {
  if(cardIndex >= 0 && cardIndex < 5) {
    return cardList[cardIndex];
  }
  else {
    return nullptr;
  }
}

int Client::GetNumAlbums() const {
  return numAlbums;
}


Album& Client::GetAlbum(int albumIndex) {
  // TODO
  // getter of Album& according to index
  // you have to check the range
  return albumList[albumIndex];
}


void Client::PrintBankAccountList() const {
  for(int i = 0; i < 5; i++) {
    if(accountList[i] == nullptr) {
      if(i == 0) {
        std::cout << "No bank account registered!" << std::endl;
      }
      break;
    }
    std::cout << i << ". " << accountList[i]->GetName() << std::endl;
  }
}

void Client::PrintCardList() const {
  for(int i = 0; i < 5; i++) {
    if(cardList[i] == nullptr) {
      if(i == 0) {
        std::cout << "No debit card registered!" << std::endl;
      }
      break;
    }
    std::cout << i << ". " << cardList[i]->GetName() << std::endl;
  }
}

void Client::PrintMusicList() const {
  for(int i = 0; i < numAlbums; i++) {
    albumList[i].PrintClientOwnedMusics();
  }
}

// This function charges SNUMoney by
// withdrawing money from a bank account.
// Study this function carefully!
bool Client::ChargeSNUMoney(int money, int accountIndex) {
  if(accountIndex < 0 || accountIndex >= 5) {
    return false;
  }
  if(accountList[accountIndex] == nullptr) {
    return false;
  }
  bool result = accountList[accountIndex]->Withdraw(money);
  if(result == true) {
    SNUMoney += money;
  }
  return result;
}

// *** README *** ///
// The accountList and cardList should be filled from index 0.
// When we remove an entry from the array, the array element
// should be filled with nullptr

// Also if the array was like
// 0. Woori
// 1. Sinhan
// 2. Hana
// 3. Nonghyup
// 4. nullptr

// After performing RemoveBankAccount(1)
// it should look like
// 0. Woori
// 1. Hana
// 2. Nonghyup
// 3. nullptr
// 4. nullptr
// after the removement.
// i.e. there should not be a blank nullptr space in between.
// the same rule applies for cardList.

// Note that removing entry mean destructing those entries.
// This is a little counter-intuitive 
// BE CAREFUL ABOUT MEMORY LEAKS!

bool Client::AddBankAccount(std::string bankName, int money) {
  // TODO
  // creates a BankAccount and put it into the list
  // fails if list is full

  for (int i=0; i<5; i++){
    if (accountList[i] == nullptr){
      accountList[i] = new BankAccount(bankName, money);
      return true;
    }
  }
  // nullptr가 없으면
  return false;
}

bool Client::AddCard(std::string cardName, int bankIndex) {
  // TODO
  // creates a Card and put it into the list
  // note that the bank account associated with the card
  // must be in the accountList
  // fails if list is full or bank account does not exist for the index
 
    if (bankIndex < 0 || bankIndex >= 5){
        return false;
    }
    else if (accountList[bankIndex] == nullptr){ // 해당 인덱스의 은행계좌 없음
        return false;
    }
    else{
        for (int i=0; i<5; i++){
            if (cardList[i] == nullptr){ // 신규 카드를 위한 빈 자리 존재
                cardList[i] = new Card(cardName, accountList[bankIndex]);
                return true;
            }
        }
        return false; // 신규 카드를 위한 빈 자리 없음
    }
}

bool Client::PayBySNUMoney(int money) {
  // TODO
  // pay money by SNU Money.
  // If charged SNUMoney is not enough,
  // the operation fails and returns false.
  // Otherwise, decrease charged SNUMoney 
  // and return true. 
  if (SNUMoney < money){
    return false;
  }
  SNUMoney -= money;
  return true;
}

bool Client::PayByCard(int money, int cardIndex) {
  // TODO
  // pay money by debit card.
  // if the card for cardIndex does not exist or
  // the card-associated bank account has not enough balance, 
  // the operation fails and returns false.
  if (cardIndex < 0 || cardIndex >= 5){
    return false;
  }
    
  if (cardList[cardIndex] == nullptr){
    return false;
  }

  bool result = cardList[cardIndex]->Pay(money);
  if(result == true) {
    SNUMoney -= money;
  }
  return result;
}

bool Client::AddAlbum(const Album& album) {
  // TODO
  // Copy the album to the albumList.
  // If the same album already exists,
  // copy to that position in the array albumList.
  // use overloaded == operator to check if the album is same.
  // i.e. do not keep duplicate copies of the same album.

  for (int i=0; i<100; i++){
    if (albumList[i] == album){
      // same album
      albumList[i] = album;
      albumList[i].SetEntireAlbumOwned();
      return true;
    }
    else if (albumList[i].GetNumMusic() == 0){
      // empty album
      albumList[i] = album;
      albumList[i].SetEntireAlbumOwned();
      numAlbums += 1;
      return true;
    }
  }
  // If 'album' is different from all other albums,
  // and there is no empty album in albumList,
  // then adding 'album' should be banned at that moment.
  return false;
}

bool Client::AddMusic(const Music& music) {
  // TODO
  // Copy the music to the albumList.
  // If the album of the music already exists,
  // copy to that position in the array albumList.
  // If not, create a new album entry in the array.
  // use overloaded == operator to check if the album is same.
  // i.e. do not keep duplicate copies of the same album.
  
  Album* ptr_album = music.GetAlbum();
  Album album = *ptr_album;
  
  Music** musicList = album.GetMusicList();
  const std::string& music_name = music.GetName();
  int music_index;

  for (int i=0; i<album.GetNumMusic(); i++){
    if(music_name == musicList[i]->GetName()){
      music_index = i;
      break;
    }
  }

  for (int i=0; i<100; i++){
    if (albumList[i] == album){
      // same album
      albumList[i].SetOneSongOwned(music_index);
      return true;
    }
    else if(albumList[i].GetNumMusic() == 0){
      // empty album
      albumList[i] = album;
      albumList[i].SetOneSongOwned(music_index);
      numAlbums += 1;
      return true;
    }
  }
  return false;
}
