#include "Collection.h"

Collection::Collection()
{
}

Collection::~Collection()
{
}

bool Collection::add_track(Track *in_track)
{
  /*
   * IMPLEMENT ME
   */
  
  return true;
}

bool Collection::add_playlist(Playlist *in_playlist)
{
  /*
   * IMPLEMENT ME
   */

  return true;
}

/*
 * Find a track that matches on title
 */
Track *Collection::find_track(string &track_title)
{
  Track * track_p;
  /*
   * IMPLEMENT ME
   */

  return track_p;
}

/*
 * Remove a track that matches on title
 */
void Collection::remove_track(string &track_title)
{
  /*
   * IMPLEMENT ME
   */

  return;
}

Playlist *Collection::find_playlist(string &pl_title)
{
  Playlist * playlist_p;
  /*
   * IMPLEMENT ME
   */

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
   */
}

/*PRINT*/
void Collection::print_tracks_by_title(ostream &os)
{
  os << "  *******************" << endl;
  os << "  * Tracks by title *" << endl;
  os << "  *******************" << endl;

  /*
   * IMPLEMENT ME
   */
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

  os << endl;

  /*
   * IMPLEMENT ME
   * tracks by artist
   */

  os << endl;

  os << "*******************" << endl;
  os << "*    Playlists    *" << endl;
  os << "*******************" << endl;

  /*
   * IMPLEMENT ME
   * playlists by title
   */

  os << endl;
  
  return os;
}
