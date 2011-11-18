#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include <string>
#include "Bst_template.h"
#include "Playlist.h"
#include "Linked_List_template.h"

class Collection 
{
 public:
  Collection();
  ~Collection();

  bool      add_track(Track *in_track);
  bool      add_playlist(Playlist *in_playlist);

  Track    *find_track(std::string &track_title);
  void      remove_track(std::string &track_title);

  Playlist *find_playlist(std::string &pl_title);

  void      print_tracks_by_artist(std::ostream &os);
  void      print_tracks_by_title(std::ostream &os);
  void      print_playlists_by_title(std::ostream &os);
  void      print_playlists_by_added_order(std::ostream &os);

  friend std::ostream& operator<<(std::ostream &os, Collection &in_collection);

 private:
  Linked_List<Playlist> playlists_ll;
  Bst<Playlist>         playlists_bst;
  
  Linked_List<Track>    tracks_ll;
  Bst<Track>            tracks_bst;
  Bst<Track>            tracks_by_artist;
//  Bst<Track>            tracks_by_title;


};

#endif
