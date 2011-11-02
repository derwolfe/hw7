#ifndef TRACK_H
#define TRACK_H

#include <iostream>
#include <string>

class Track 
{
 public:
  Track(const std::string &in_title,
        const std::string &in_artist,
   	    const std::string &in_album,
   	    const std::string &in_comment);

  std::string get_title();
  std::string get_artist();

  friend std::ostream& operator<<(std::ostream &os, Track &in_track);

 private:
  std::string title;
  std::string artist;
  std::string album;
  std::string comment;
};

#endif
