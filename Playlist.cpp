#include "Playlist.h"


Playlist::Playlist(const string &in_title)
{
  title = in_title;
}

/*
 * Add a track to this playlist. Return true if successful, and false
 * if not
 */
bool Playlist::add_track(Track *in_track)
{
  /*
   * IMPLEMENT ME
   */
  return true;

}

bool Playlist::matches(string &in_title)
{
  /*
   * IMPLEMENT ME
   */

  return true;
}

string Playlist::get_title()
{
  return title;
}

/*PRINT*/
void Playlist::print_title(std::ostream &os)
{
  os << title;
}

/*PRINT*/
void Playlist::print_by_artist(ostream &os)
{
  os << "  *************************" << endl;
  os << "  * Playlist (by artist): " << title << endl;
  os << "  *************************" << endl;

  /*
   * IMPLEMENT ME
   */

}

/*PRINT*/
void Playlist::print_by_title(ostream &os)
{
  os << "  *************************" << endl;
  os << "  * Playlist (by title): " << title << endl;
  os << "  *************************" << endl;

  /*
   * IMPLEMENT ME
   */
}

/*PRINT*/
void Playlist::print_by_added_order(ostream &os)
{
  os << "  ******************************" << endl;
  os << "  * Playlist (by added order): " << title << endl;
  os << "  ******************************" << endl;

  /*
   * IMPLEMENT ME
   */

}

/*PRINT*/
void Playlist::play_by_added_order(ostream &os)
{
  /*
   * IMPLEMENT ME
   */
  os << "  ******************************" << endl;
  os << "  * Play (by added order): " << title << endl;
  os << "  ******************************" << endl;

  os << "  Play : " << /* IMPLEMENT ME */ << endl;



}

/*PRINT*/
void Playlist::play_by_randomized(ostream &os, int repetitions)
{
  /*
   * IMPLEMENT ME
   */
  os << "  ******************************" << endl;
  os << "  * Play (randomized): " << title << endl;
  os << "  * Repetitions: " << repetitions << endl;
  os << "  ******************************" << endl;

  os << "  Play : " << /* IMPLEMENT ME */ << endl;


}

/*PRINT*/
std::ostream& operator<<(std::ostream &os, Playlist &in_playlist)
{
  /*
   * IMPLEMENT ME
   * print playlist in title order by default
   */

  return os;
}

