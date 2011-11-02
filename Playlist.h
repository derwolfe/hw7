#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
#include "Bst_template.h"
#include "Linked_List_template.h"
#include "Track.h"

class Playlist 
{
 public:
  Playlist(const std::string &in_title);

  bool add_track(Track *in_track);
  bool matches(std::string &pl_title);
  std::string get_title();
  void print_title(std::ostream &os);
  void play_by_added_order(ostream &os);
  void play_by_randomized(ostream &os, int repetitions);
  void print_by_artist(std::ostream &os);
  void print_by_title(std::ostream &os);
  void print_by_added_order(std::ostream &os);

  friend std::ostream& operator<<(std::ostream &os, Playlist &in_playlist);

 private:
  std::string           title;
  /*
   * IMPLEMENT ME
   */
};

#endif
