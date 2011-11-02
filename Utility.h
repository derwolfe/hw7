#include <string>
#include <fstream>
#include "Collection.h"

/*
 * Define a set of ID values for the Music DB commands and their
 * argument labels
 *
 * We create defined constants and constant integers for the command
 * values so we can use the integers as return values, and the defined
 * constants as labels in a switch statement.
 */
enum Command 
{
  CMD_ADD_TRACK,       
  CMD_ADD_PLAYLIST,    
  CMD_DELETE_TRACK,    
  CMD_PLAY_ADDED_ORDER,   
  CMD_PLAY_RANDOMIZED,   
  CMD_PRINT_TRACK,   
  CMD_PRINT_PLAYLIST,  
  CMD_PRINT_TRACKS_BY_TITLE,    
  CMD_PRINT_TRACKS_BY_ARTIST,    
  CMD_PRINT_PLAYLISTS,
  CMD_PRINT_COLLECTION,

  CMD_INVALID
};

Command     identify_next_command(std::string cmd_line);
void        parse_cmd_line(const char *cmd_label, char input_line[], std::string &target);
Track*      process_add_track(std::ifstream &in_port);
Playlist*   process_add_playlist(std::ifstream &in_port, Collection &collection);

Collection* process_db_definition_file(std::ifstream &in_port);
void        process_db_cmd_file(std::ifstream &in_port, Collection in_collection, 
                         ostream &out_port);
