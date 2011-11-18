#include "Playlist.h"
#include "time.h"

// allocation spawn delete!

Playlist::Playlist(const std::string &in_title)
{
  /* imp me
   */ 
  title = in_title;
}

/*
 * Add a track to this playlist. Return true if successful, and false
 * if not
 */
bool Playlist::add_track(Track *in_track)
{
  if (in_track == NULL) {
    return false;
  } else {
    playlist.append(in_track);//add ptr to track
    play_by_title.insert(in_track->get_title(), in_track);//add to trees!
    play_by_artist.insert(in_track->get_artist(), in_track);
    return true;
  }
}

bool Playlist::matches(string &in_title)
{
  /*
   * use the size of the list to loop through the tracks. Retrieve 
   * track information to check the title against the track.
   */
  int count = playlist.get_size();
  while (count >= 0) 
    if (in_title.compare(playlist.retrieve(count)->get_title()) == 0) {
      return true;
    } else {
      --count;
    }
    return false;
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
  play_by_artist.print_inorder(os);
}

/*PRINT - perfect for a BST, make the tree, loop through it inorder to take
 * advantage of the sorting, et voila, a tree is made. 
 *
 * Then just traverse the tree inorder.*/
void Playlist::print_by_title(ostream &os)
{
  os << "  *************************" << endl;
  os << "  * Playlist (by title): " << title << endl;
  os << "  *************************" << endl;
  /* use the inorder sorted printed method. */
  play_by_title.print_preorder(os); 
}

/*PRINT - a bit simpler, print the nodes from the linked list*/
void Playlist::print_by_added_order(ostream &os)
{
  os << "  ******************************" << endl;
  os << "  * Playlist (by added order): " << title << endl;
  os << "  ******************************" << endl;
  // use the LL print method.
  playlist.print(os);
}

/*PRINT - not sure if i should be deleting the pointer from the list
 * once the item has been played.
 */
void Playlist::play_by_added_order(ostream &os)
{
  /*
   * IMPLEMENT ME
   * traverse the list, remove the head node as you go!
   */
  os << "  ******************************" << endl;
  os << "  * Play (by added order): " << title << endl;
  os << "  ******************************" << endl;
  int inc = 1;
  int size = playlist.get_size();
 
  while (inc) { //since inc starts at size
    os << "  Play : " << playlist.retrieve(1) << endl;
    playlist.remove(1);
    --inc;
  }
}

/*PRINT - play a playlist, randomized, n times.*/
void Playlist::play_by_randomized(ostream &os, int repetitions)
{
// you need to create a random number generator modulo get_size 
// in order to repeat less than size times.
  os << "  ******************************" << endl;
  os << "  * Play (randomized): " << title << endl;
  os << "  * Repetitions: " << repetitions << endl;
  os << "  ******************************" << endl;
  
  int limit = repetitions;
  int rando;
  srand(time(NULL));
  /* choose track at random, limit list to number of reps.
   * make a playlist, play the top!
    *   
    */ 
  while (limit) {
    rando = (rand() % repetitions) + 1;
    play_by_random.append(playlist.retrieve(rando));
    --limit;
  } /* play the top track! */
  os << "  Play : " << play_by_random.retrieve(1)<< endl;
}

/*PRINT*/
std::ostream& operator<<(std::ostream &os, Playlist &in_playlist)
{
  /*
   * print playlist in title order by default
   */
  //inorder chosen because it will take the sorting into account.
  //must call print method
  in_playlist.print_by_title(os);
  return os;
}


