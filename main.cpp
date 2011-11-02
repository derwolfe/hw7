#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Utility.h"

using namespace std;

int main(const int argc, char *argv[])
{
  ifstream  input_port;
  int       retval;

  Collection *collection_p;

  /*PRINT*/
  if ( argc < 3 ) {
    cout << "Useage: ./music_db <db-defn-file-name> <db-cmd-file-name>" << endl;
    exit(1);
  }

  /*
   * Open the DB definition file and create the collection DS
   */
  /*PRINT*/
  input_port.open(argv[1]);
  if ( !input_port.good() ) {
    /*
     * Something is wrong. Complain and die.
     */
    cout << "Error: could not open input file:" << argv[1] << endl;
    exit(1);
  }

  /*
   * This subroutine reads a DB definition file and builds the data
   * structures indicated by the commands for the tracks and playlists
   */
  collection_p = process_db_definition_file(input_port);

  input_port.close();

  /*
   * Open the set of DB commands and process them
   */
  /*PRINT*/
  input_port.open(argv[2]);
  if ( !input_port.good() ) {
    /*
     * Something is wrong. Complain and die.
     */
    cout << "Error: could not open input file:" << argv[2] << endl;
    exit(1);
  }

  /*
   * This subroutine reads a file of DB commands and takes the
   * corresponding actions
   */
  process_db_cmd_file(input_port, *collection_p, cout);

  /**********************************************************/
  /**********************************************************/

  exit(0);
}

