#include "Track.h"

using namespace std;

Track::Track(const string &in_title,
             const string &in_artist,
   	         const string &in_album,
   	         const string &in_comment)
{
  title   = in_title;
  artist  = in_artist;
  album   = in_album;
  comment = in_comment;
}

string Track::get_title()
{
  return title;
}

string Track::get_artist()
{
  return artist;
}

/*PRINT*/
std::ostream& operator<<(std::ostream &os, Track &in_track)
{
  os << "Title: "    << in_track.title << endl;
  os << "  Artist:  " << in_track.artist << endl;
  os << "  Album:   " << in_track.album << endl;
  os << "  Comment: " << in_track.comment << endl;
  os << endl;
  return os;
}

