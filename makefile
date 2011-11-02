KUID = CHANGE_ME_TO_YOUR_KUID
LAB_NAME = tree

CPP_FLAGS = -DF_SOLUTION

all: music_db

music_db: main.o Collection.o Playlist.o Track.o Utility.o 
	g++ -g main.o Collection.o Playlist.o Track.o Utility.o -o music_db 

Track.o: Track.cpp Track.h
	g++ $(CPP_FLAGS) -c -g Track.cpp

Playlist.o: Playlist.cpp Playlist.h Track.h Bst_template.h Linked_List_template.h 
	g++ $(CPP_FLAGS) -c -g Playlist.cpp

Collection.o: Collection.cpp Collection.h Playlist.h Bst_template.h Linked_List_template.h
	g++ $(CPP_FLAGS) -c -g Collection.cpp

main.o: main.cpp Collection.h Utility.h 
	g++ $(CPP_FLAGS) -c -g main.cpp

Utility.o: Utility.cpp Utility.h Collection.h
	g++ $(CPP_FLAGS) -c -g Utility.cpp

all_tests: test1 test2 test3

test1: music_db
	@echo "  "
	@echo "Do not be confused by an \"error\" output from make"
	@echo "when the diff command finds a difference between the files."
	@echo "This is a programming convention. Make will not complain "
	@echo "of an error when there is no difference. "
	@echo "  "
	./music_db db_create1 db_cmd1 >output1
	-diff -b -B output1 output1.correct

test2: music_db
	./music_db db_create1 db_cmd2 >output2
	-diff -b -B output2 output2.correct

test3: music_db
	./music_db db_create1 db_cmd3 > output3

tar-file: clean
	@if test -d ../$(KUID)_$(LAB_NAME) ; then \
		( cd .. ; \
		  tar cz $(KUID)_$(LAB_NAME) >$(KUID)_$(LAB_NAME).tar.gz ; \
	  	  echo ""; \
		  echo "**************************************************************"; \
		  echo "The TAR file for you to test and hand in "; \
		  echo "   has been made in the directory above:"; \
		  echo "     " $(KUID)_$(LAB_NAME).tar.gz ; \
		  echo "**************************************************************"; \
		) ; \
	else \
		( echo "*** ERROR ** ERROR ** ERROR ** ERROR ** ERROR ** ERROR ***"; \
		  echo "The <your KUID>_<lab-name> directory was not found. "; \
		  echo "Remember that you should rename the "; \
		  echo "\"starter-code\" directory created by the "; \
		  echo "starter TAR file and set the KUID " ; \
		  echo "variable in the Makefile"; \
		) ; \
	fi

clean:
	rm -f *.o music_db output1 output2 output3
