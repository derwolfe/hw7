#include <cstring>
#include "Utility.h"

using namespace std;

const int MAX_INPUT_LENGTH = 100;


/*
 * Examine the input line to see what cmmand is being
 * specified. Return the command code if found, or -1 if not.
 */
Command identify_next_command(string cmd_line)
{
  Command command;

  if ( cmd_line.compare("add_track") == 0 ) {
    command = CMD_ADD_TRACK;
  } else if ( cmd_line.compare("add_playlist") == 0 ) {
    command = CMD_ADD_PLAYLIST;
  } else if ( cmd_line.compare("delete_track") == 0 ) {
    command = CMD_DELETE_TRACK;
  } else if ( cmd_line.compare("play_added_order") == 0 ) {
    command = CMD_PLAY_ADDED_ORDER;
  } else if ( cmd_line.compare("play_randomized") == 0 ) {
    command = CMD_PLAY_RANDOMIZED;
  } else if ( cmd_line.compare("print_track") == 0 ) {
    command = CMD_PRINT_TRACK;
  } else if ( cmd_line.compare("print_tracks_title") == 0 ) {
    command = CMD_PRINT_TRACKS_BY_TITLE;
  } else if ( cmd_line.compare("print_tracks_artist") == 0 ) {
    command = CMD_PRINT_TRACKS_BY_ARTIST;
  } else if ( cmd_line.compare("print_playlist") == 0 ) {
    command = CMD_PRINT_PLAYLIST;
  } else if ( cmd_line.compare("print_playlists") == 0 ) {
    command = CMD_PRINT_PLAYLISTS;
  } else if ( cmd_line.compare("print_collection") == 0 ) {
    command = CMD_PRINT_COLLECTION;
  } else {
    command = CMD_INVALID;
  }

  return command;
}

/*
 * Parse a DB defnition of DB command line of the form:
 *      cmd:value
 * Return the value in the target parameter
 */
void parse_cmd_line(const char *cmd_label, char input_line[], string &target)
{
  char *cp1;
  char *cp2;

  cp1 = strchr(input_line, ':');
  cp2 = cp1 + 1;
  *cp1 = '\0';
  if ( !strcmp(cp2, cmd_label) ) {
    cout << "ERROR: input arguments out of sequence" << endl;
    exit(-1);
  }

  target = cp2;
}

Track *process_add_track(ifstream &in_port)
{
  Track *new_track;
  char   input_line[MAX_INPUT_LENGTH];

  string title;
  string artist;
  string album;
  string comment;

  /*
   * Read the title, artist, album, and comment arguments in that
   * order
   */
  in_port.getline(input_line, MAX_INPUT_LENGTH);
  parse_cmd_line("title", input_line, title);

  in_port.getline(input_line, MAX_INPUT_LENGTH);
  parse_cmd_line("artist", input_line, artist);

  in_port.getline(input_line, MAX_INPUT_LENGTH);
  parse_cmd_line("album", input_line, album);

  in_port.getline(input_line, MAX_INPUT_LENGTH);
  parse_cmd_line("comment", input_line, comment);

  /*
   * Now construct an instance of Track initializing it with the
   * fileds just read fromt he file
   */
  new_track = new Track(title, artist, album, comment);
  return new_track;
}

Playlist *process_add_playlist(ifstream &in_port, Collection &collection)
{
  Playlist *new_playlist;
  Track    *track_ptr;
  char      input_line[MAX_INPUT_LENGTH];

  string pl_title;
  string track_title;
  string track_artist;

  /*
   * Read the title of the playlist and set the content of this
   * object's title data element using the pl_title string object.
   */
  in_port.getline(input_line, MAX_INPUT_LENGTH);
  parse_cmd_line("pl_title", input_line, pl_title);
  new_playlist = new Playlist(pl_title);

  /*
   * Now read pairs of track titles and artists that are elements of
   * the playlist. Look them up in the tracks defined in the
   * collection so far, and then add a pointer to the Track object in
   * the next playlist slot.
   *
   * Terminate the loop when we hit a blank line by executing the
   * break command.
   */
  while ( true ) {
  
    in_port.getline(input_line, MAX_INPUT_LENGTH);
    if ( input_line[0] == '\0' ) {
      /*
       * Blank line terminates the list of tracks specified for a play
       * list
       */
      break;
    }

    parse_cmd_line("title", input_line, track_title);

    in_port.getline(input_line, MAX_INPUT_LENGTH);
    parse_cmd_line("artist", input_line, track_artist);

    /*
     * Find the track in the collection by title and artist pair
     */
    track_ptr = collection.find_track(track_title);
    if (track_ptr == (Track *)0) {
      cout << "Error: could not find specified track for playlist" << endl;
    }

    /*
     * Add the pointer to the track to the playlist
     */
    new_playlist->add_track(track_ptr);
  }

  /*
   * return the constructed playlist
   */
  return new_playlist;
}

/*
 * Process the set of commands defining additions to the DB
 */
Collection *process_db_definition_file(ifstream &in_port)
{
  const int  MAX_INPUT_LENGTH = 100;
  string input_line;

  Command    cmd_id;

  Track     *new_track_p;
  Playlist  *new_playlist_p;

  Collection *collection_p;

  collection_p = new Collection;

  while ( !in_port.eof() ) {
    getline(in_port, input_line);

    /*
     * Skip blank lines and those starting with a # in column 0 which
     * we declare to be comments
     */
    if ( input_line[0] == '\0' ) {
      continue;
    }

    if ( input_line[0] == '#' ) {
      continue;
    }

    /*
     * Find out what command is next and then call the appropriate
     * routine to process the input for that command
     */
    cmd_id = identify_next_command(input_line);

    switch ( cmd_id ) {
    case CMD_ADD_TRACK:
      new_track_p = process_add_track(in_port);
      if ( !collection_p->add_track(new_track_p) ) {
        cout << "Error: failure during reading a track definition" << endl;
        return (Collection *)0;
      }
      break;

    case CMD_ADD_PLAYLIST:
      new_playlist_p = process_add_playlist(in_port, *collection_p);
      if ( !collection_p->add_playlist(new_playlist_p) ) {
        cout << "Error: failure during reading a playlist definition" << endl;
        return (Collection *)0;
      }
      break;

    default:
      cout << "ERROR: This should never happen as a proper ID should always be returned" << endl;
      break;
    }
  }
  return collection_p;;
}

/*
 *  Process the file specifying commands on the DB built
 */
void process_db_cmd_file(ifstream &in_port, Collection in_collection, 
                         ostream &out_port )
{
  const int  MAX_INPUT_LENGTH = 100;
  char       input_line[MAX_INPUT_LENGTH];

  int        cmd_id;

  string  title_value;
  string  order_value;
  string  artist_value;
  string  repetitions_str;
  int     repetitions_int;


  Track     *track_p;
  Playlist  *playlist_p;

  while ( !in_port.eof() ) {
    in_port.getline(input_line, MAX_INPUT_LENGTH);

    /*
     * Skip blank lines and those starting with a # in column 0 which
     * we declare to be comments
     */
    if ( input_line[0] == '\0' ) {
      continue;
    }

    if ( input_line[0] == '#' ) {
      continue;
    }

    /*
     * Find out what command is next and then call the appropriate
     * routine to process the input for that command
     */
    cmd_id = identify_next_command(input_line);
    switch ( cmd_id ) {
    /*PRINT*/
    case CMD_DELETE_TRACK:
      in_port.getline(input_line, MAX_INPUT_LENGTH);
      parse_cmd_line("title", input_line, title_value);

      /*
       * IMPLEMENT ME
       */
      in_collection.remove_track(title_value);
      break;

    case CMD_PLAY_ADDED_ORDER:
      in_port.getline(input_line, MAX_INPUT_LENGTH);
      parse_cmd_line("title", input_line, title_value);
      playlist_p = in_collection.find_playlist(title_value);
      /*
       * IMPLEMENT ME
       */
      playlist_p->play_by_added_order(out_port);
      if (playlist_p == NULL) {
        cout << "Error: finding playlist" << endl;
        cout << "Playlist: " << title_value << endl;
        continue;
      }
      playlist_p->play_by_added_order(out_port);
      break;

    /*PRINT*/
    case CMD_PLAY_RANDOMIZED:
      /*
       * IMPLEMENT ME
       * convert the repetitions_str to repetitions_int, plug in.
       * find the playlist as well
       *
       */

   //   in_port.getline(input_line, MAX_INPUT_LENGTH);
   //   parse_cmd_line("repetitions", input_line, repetitions_str);
   //   repetitions_int = atoi(repetitions_str);
   //   playlist_p->play_by_randomized(out_port, repetitions_int);

      break;

    /*PRINT*/
    case CMD_PRINT_TRACK:
      in_port.getline(input_line, MAX_INPUT_LENGTH);
      parse_cmd_line("title", input_line, title_value);

      in_port.getline(input_line, MAX_INPUT_LENGTH);
      parse_cmd_line("artist", input_line, artist_value);

      track_p = in_collection.find_track(title_value);
      if ( track_p == (Track *)0 ) {
        cout << "Error: failure finding a track" << endl;
        cout <<  "Title:  " << title_value  << endl;
        cout <<  "Artist: " << artist_value << endl << endl;
        continue;
      }

      out_port << "******************" << endl;
      out_port << "**  Print Track **" << endl;
      out_port << "******************" << endl;
      out_port << *track_p;
      break;

    /*PRINT*/
    case CMD_PRINT_PLAYLIST:
      in_port.getline(input_line, MAX_INPUT_LENGTH);
      parse_cmd_line("title", input_line, title_value);

      in_port.getline(input_line, MAX_INPUT_LENGTH);
      parse_cmd_line("order", input_line, order_value);

      playlist_p = in_collection.find_playlist(title_value);
      if ( playlist_p == (Playlist *)0 ) {
        cout << "Error: failure finding a playlist" << endl;
        cout <<  "Title:  " << title_value  << endl << endl;
        continue;
      }

      out_port << "*********************" << endl;
      out_port << "**  Print Playlist **" << endl;
      out_port << "*********************" << endl;
      /*
       * IMPLEMENT ME
       */
      playlist_p->print_by_added_order(out_port);
      out_port << endl;
      cout << "Error: unrecognized playlist print order" << endl << endl;
      break;

    /*PRINT*/
    case CMD_PRINT_TRACKS_BY_TITLE:
      out_port << "*****************************" << endl;
      out_port << "* Print All Tracks by title *" << endl;
      out_port << "*****************************" << endl;
      /*
       * IMPLEMENT ME
       */
      playlist_p->print_by_title(out_port);
      out_port << endl;
      break;

    /*PRINT*/
    case CMD_PRINT_TRACKS_BY_ARTIST:
      out_port << "******************************" << endl;
      out_port << "* Print All Tracks by artist *" << endl;
      out_port << "******************************" << endl;
      /*
       * IMPLEMENT ME
       */
      playlist_p->print_by_artist(out_port);
      out_port << endl;
      break;

    /*PRINT*/
    case CMD_PRINT_PLAYLISTS:
      out_port << "***********************" << endl;
      out_port << "* Print All Playlists *" << endl;
      out_port << "***********************" << endl;
      /*
       * IMPLEMENT ME
       */
      in_collection.print_playlists_by_added_order(out_port);
      out_port << endl;
      break;

    /*PRINT*/
    case CMD_PRINT_COLLECTION:
      out_port << "**************************" << endl;
      out_port << "* Print Whole Collection *" << endl;
      out_port << "**************************" << endl;
      out_port << in_collection;
      out_port << endl;
      break;

    case CMD_INVALID:
      cout << "ERROR: invalid command - " << input_line << endl << endl;
      break;

    default:
      cout << "ERROR: This should never happen as a proper ID should always be returned" << endl;
      break;
    }
  }
}


