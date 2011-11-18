#include "Collection.h"

Collection::Collection()
{
}

Collection::~Collection()
{
}

bool Collection::add_track(Track *in_track)
{
  if (in_track == NULL) {
    return false;
  } else { //just insert in the tree.
    /* add track to both the search tree and the linked list.
     *
     * _bst is the search tree for the tracks, keyed by title.
     * _by_artist is a search tree for tracks, keyed by artist.
     * _p is the LL of the tracks.
     */
    tracks_bst.insert(in_track->get_title(), in_track); //creates a sorted list
    tracks_by_artist.insert(in_track->get_artist(), in_track);// creates a sorted list
    tracks_ll.append(in_track);
  }
  return true;
}

bool Collection::add_playlist(Playlist *in_playlist)
{
  /*
   * IMPLEMENT ME
   *
   * if for what ever reason a NULL ptr is passed, don't add it.
   * Otherwise, append the playlist to the list of playlists.
   *
   * This means there already IS a playlist.
   */
  if (in_playlist == NULL) {
    return false;
  } else { 
    playlists_bst.insert(in_playlist->get_title(), in_playlist);
    playlists_ll.append(in_playlist);
  }
  return true;
}

/*
 * Find a track that matches on title
 */
Track *Collection::find_track(string &track_title)
{
  Track *track_p;
  /*
   * IMPLEMENT ME
   */
  /* search through the BST for the track. 
   * If after the search has execucted and the track isn't found
   * NULL will be returned*/
  track_p = tracks_bst.search(track_title);
  return track_p;
}

/*
 * Remove a track that matches on title
 *
 * Remove from both data-structures!
 */
void Collection::remove_track(string &track_title)
{
  /*
   * IMPLEMENT ME
   */
  /* easy remove from BST. the bst structure handles find&remove. The list will take longer.
   *
   * What about removal from playlists?*/
  tracks_bst.remove(track_title);
  tracks_by_artist.remove(track_title);
 
  /* now the linked list, I definitely should have created a list iterator. */
  int len = tracks_ll.get_size();
  int inc = 1;
  while (inc <= len) {
    if (track_title.compare(tracks_ll.retrieve(inc)->get_title()) == 0) {
      tracks_ll.remove(inc);
      return;
    } else {
      ++inc;
    }
  }
  return;
}

Playlist *Collection::find_playlist(string &pl_title)
{
  Playlist *playlist_p;
  /*
   * IMPLEMENT ME
   */
  /* search through one tree, if it is there, it should be in all; */
  playlist_p = playlists_bst.search(pl_title);
  return playlist_p;
}

/*PRINT*/
void Collection::print_tracks_by_artist(ostream &os)
{
  os << "  ********************" << endl;
  os << "  * Tracks by artist *" << endl;
  os << "  ********************" << endl;

  /*
   * IMPLEMENT ME
   *
   */
   
  tracks_by_artist.print_inorder(os);
}

/*PRINT*/
void Collection::print_tracks_by_title(ostream &os)
{
  os << "  *******************" << endl;
  os << "  * Tracks by title *" << endl;
  os << "  *******************" << endl;

  /*
   * IMPLEMENT ME
   *
   * this is the original key of the BST
   */
  tracks_bst.print_inorder(os);
}

/*PRINT*/
void Collection::print_playlists_by_title(ostream &os)
{
  os << "  **********************" << endl;
  os << "  * Playlists by title *" << endl;
  os << "  **********************" << endl;

  /*
   * IMPLEMENT ME
   */
  playlists_bst.print_inorder(os);
}

void Collection::print_playlists_by_added_order(std::ostream &os)
{
  playlists_ll.print(os);
}

/*PRINT*/
ostream& operator<<(ostream &os, Collection &in_collection)
{
  os << "**********************************" << endl;
  os << "*      Collection as a Whole     *" << endl;
  os << "**********************************" << endl;

  os << endl;

  os << "********************" << endl;
  os << "*      Tracks      *" << endl;
  os << "********************" << endl;

  /*
   * IMPLEMENT ME
   * tracks by title
   */
  in_collection.print_tracks_by_title(os);
  os << endl;

  /*
   * IMPLEMENT ME
   * tracks by artist
   */
  in_collection.print_tracks_by_artist(os);
  os << endl;

  os << "*******************" << endl;
  os << "*    Playlists    *" << endl;
  os << "*******************" << endl;

  /*
   * IMPLEMENT ME
   * playlists by title
   */
  in_collection.print_playlists_by_title(os);
  os << endl;
  
  return os;
}
