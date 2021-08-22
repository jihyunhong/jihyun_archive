#include "music.h"

//---- Class Album ----//

Album::Album(): albumName(""),
                artistName(""),
                numMusic(0),
                musicList(nullptr) {}

Album::Album(const std::string& _albumName,
             const std::string& _artistName,
             int _numMusic) {
  // TODO
  // Construct Album class.
  // Just put names, numMusic and 
  // reserve space in musicList for putting "class Music" tracks
  // using dynamic allocation.
  // Do not fill in the music tracks in this constructor.
  // It should be filled in later.
  albumName = _albumName;
  artistName = _artistName;
  numMusic = _numMusic;
  musicList = new Music*[numMusic];
  //for (int i=0; i<numMusic; i++){
  //    musicList[i] = new Music();
  //}
}


Album::Album(const Album& rhs) {
  // TODO
  // make copy constructor (deep copy)
    albumName = rhs.albumName;
    artistName = rhs.artistName;
    numMusic = rhs.numMusic;
    musicList = new Music*[numMusic];
    for (int i=0; i<numMusic; i++){
        musicList[i] = new Music(rhs.musicList[i]->GetName(), rhs.musicList[i]->GetAlbum(), rhs.musicList[i]->IsOwned());
    }
}

Album& Album::operator=(const Album& rhs) {
// TODO
// make assignment operator (deep copy)
// be sure to make it memory-safe
    if (this == &rhs) return *this;

    for (int i=0; i<numMusic; i++){
        delete musicList[i];
    }
    delete []musicList;
    
    albumName = rhs.albumName;
    artistName = rhs.artistName;
    numMusic = rhs.numMusic;
    musicList = new Music*[numMusic];
    for (int i=0; i<numMusic; i++){
        musicList[i] = new Music(rhs.musicList[i]->GetName(), rhs.musicList[i]->GetAlbum(), rhs.musicList[i]->IsOwned());
    }

    return *this;
}

Album::~Album() {
  // TODO
  // make destructor 
  // be sure to make it memory-safe
  for (int i=0; i<numMusic; i++){
    delete musicList[i];
  }
  delete []musicList;
}

bool Album::operator== (const Album& rhs) {
  // TODO
  // equalness checking operation
  // should be used in client.cpp
  // only check albumName and artistName
  if (albumName == rhs.albumName && artistName == rhs.artistName){
    return true;
  }
  return false;
}

void Album::PrintAlbumName() const {
  std::cout << artistName << " - " << albumName << std::endl;
}

// print list of musics
void Album::PrintMusics() const {
  PrintAlbumName();
  for(int i = 0; i < numMusic; i++) {
    std::cout << std::right << std::setw(4) << i << ". ";
    std::cout << musicList[i]->GetName() << std::endl;
  }
}

// print list of musics that are owned by client 
void Album::PrintClientOwnedMusics() const {
  PrintAlbumName();
  for(int i = 0; i < numMusic; i++) {
    if(musicList[i]->IsOwned()) {
      std::cout << std::right << std::setw(4) << i << ". ";
      std::cout << musicList[i]->GetName() << std::endl;
    }
  }
}

// Getter functions
const std::string& Album::GetAlbumName() const {
  return albumName;
}
const std::string& Album::GetArtistName() const{
  return artistName;
}
int Album::GetNumMusic() const {
  return numMusic;
}
Music** Album::GetMusicList() const {
  return musicList;
}

// Set owned when copying to client's albumList
void Album::SetEntireAlbumOwned() const {
  // TODO
  // set all the tracks in the musicList to owned
  // should be used for purchasing an album
  // and album is being copied to the client's albumList
  for (int i=0; i<numMusic; i++){
    musicList[i]->SetOwned();
  }
}

void Album::SetOneSongOwned(int trackNumber) const {
  // TODO
  // set just one song in the album to owned
  // should be used for purchasing a song
  // and the album containing the song
  // is being copied to the client's albumList
  musicList[trackNumber]->SetOwned();
}

//---- Class Music ----//

Music::Music(): musicName(""), album(nullptr), owned(false) {}

Music::Music(const std::string& _musicName,
             Album* _album,
             bool _owned) {
  // TODO
  // constructor
  musicName = _musicName;
  album = _album;
  owned = _owned;
}

// return music name
const std::string& Music::GetName() const {
  return musicName;
}

// return owned
// 'owned' variable is very special
// it signifies whether this music belongs to the client.
// this value should be set to true only when the music
// is copied to client's albumList.
bool Music::IsOwned() const {
  return owned;
}

// return the album pointer
Album* Music::GetAlbum() const {
  return album;
}

void Music::SetOwned() {
  owned = true;
}
