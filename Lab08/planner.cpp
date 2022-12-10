#ifndef PLANNER_CPP
#define PLANNER_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

// Edit version 1: Added COMMENT_START_CHAR to allow reading admin and
// user inputs from file with comments.  The part of a line including
// and after COMMENT_START_CHAR is ignored for interpreting the line.
#define COMMENT_START_CHAR '$'
// End edit version 1

using namespace std;

// Edit version 1: Adding some more color to the welcome message
void Planner::displayWelcomeMessage() {
  cout << BLUE << "*********************************************************" << RESET << endl;
  cout << RED << "Welcome to the CS293 Travel Planner (Autumn 2022 version)" << RESET << endl;
  cout << BLUE << "*********************************************************" << RESET << endl;
  cout << endl;
}
// End edit version 1

bool Planner::displayMenuAndAct() {
  int userCode;

  // Edit version 1: Added "(0 to exit)" to help the user
  cout << "Enter user code (0 to exit): ";
  // End edit version 1
  cin >> userCode;
  int userLevel = getUserLevel(userCode);
  
  if (userLevel == EXIT_LEVEL) {
    cout << "Thank you for using the journey planner." << endl;
    cout << "Bye!" << endl;
    return false;
  }

  if (userLevel == ADMIN_LEVEL) {
    return doAdminJob();
  }
  else if (userLevel == USER_LEVEL) {
    return doUserJob();
  }
  else {
    cout << "Invalid user code" << endl;
    return true;
  }
}

inline int Planner::getUserLevel(int userCode) {
  return ((userCode == MAGIC_CODE) ? ADMIN_LEVEL : \
	  (userCode == EXIT_CODE) ? EXIT_LEVEL : \
	  (userCode > 0) ? USER_LEVEL : INVALID_LEVEL);
}

bool Planner::doAdminJob() {
  bool readFrmFile = false;
  string inpFileName = "";
  fstream inpFile;
  
  do {
    if (!readFrmFile) {
      // Edit version 1: Added some extra couts for clarity
      cout << "****************************" << endl;
      // End edit version 1
      cout << "Please choose an admin job:" << endl;
      cout << "  0. Exit admin user" << endl;
      cout << "  1. Enter/delete station name" << endl;
      cout << "  2. Enter/delete journey code" << endl;
      cout << "  3. Read commands from file" << endl;
      cout << "  4. Exit reading commands from file" << endl;

      // Edit version 1: Added option to print trie of station names"Input: " to the output string
      // Also added printing of the string "Input: " before the
      // user types in an input
      cout << "  5. Print trie of station names" << endl;
      // Lab 7 specific
      cout << "  6. Enter journey information" << endl;
      // End lab 7 specific
      cout << endl << "Input: ";
      // End edit version 1

    }
    
    int option = getInt(readFrmFile, &inpFile);
    
    if (!readFrmFile && (option == ADMIN_READ_FROM_FILE)) {
      logFile << "Executing \"Read commands from file\" " << endl;
      
      cout << "  Input file name: ";
      cin >> inpFileName;

      inpFile.open(inpFileName, ios::in);
      if (!inpFile.is_open()) {
	cout << "Failed to open file " << inpFileName << " for reading" << endl;
	logFile << "Failed" << endl;
	inpFileName = "";
      }
      else {
	logFile << "Success" << endl;
	readFrmFile = true;
      }
      continue;
    }
    else if (readFrmFile && (option == ADMIN_READ_FROM_FILE)) {
      logFile << "Executing \"Read commands from file\" " << endl;
      logFile << "Ignoring ..." << endl;

      // Edit version 1: Made the error message a bit explanatory
      cerr << "\"Read from file\" command encountered while already reading from file. Ignoring ..." << endl;
      // End edit version 1
      continue;
    }
    else if (readFrmFile && (option == ADMIN_EXIT_READ_FROM_FILE)) {
      logFile << "Executing \"Exit reading commands from file\" " << endl;

      // Edit version 1: Made the message a bit more explanatory
      cout << "Finished reading and executing commands from file" << endl;
      // End edit version 1
      inpFile.close();
      if (!inpFile.is_open()) {
	logFile << "Success" << endl;
      }
      else {
	logFile << "Failed." << endl;
      }
      readFrmFile = false;
      inpFileName = "";
      continue;
    }
    else if (!readFrmFile && (option == ADMIN_EXIT_READ_FROM_FILE)) {
      logFile << "Executing \"Exit reading commands from file\" " << endl;
      logFile << "Ignoring ..." << endl;

      cerr << "\"Exit read from file\" command while not reading from file. Ignoring ..." << endl;
      continue;
    }
    else {
      // option is neither ADMIN_READ_FROM_FILE nor ADMIN_EXIT_READ_FROM_FILE

      switch (option) {
      case ADMIN_EXIT:
	logFile << "Executing \"Exit admin user\"" << endl;

	cout << "Thank you for being an admin!" << endl;
	cout << "Bye!!!" << endl;
	if (readFrmFile) {
	  readFrmFile = false;
	  inpFileName = "";
	  if (inpFile.is_open()) {
	    inpFile.close();
	  }
	}
	return true;
      
      case ADMIN_ENTER_DELETE_STN_NAME:
	logFile << "Executing \"Enter/delete station name\"" << endl;
	
	if (!readFrmFile) {
	  // Edit version 1: Added some extra couts for clarity
	  cout << "****************************" << endl;
	  // End edit version 1
	  cout << "Entering/deleting station name. " << endl;
	  cout << " Choose a sub-option:" << endl;
	  cout << "  11. Enter new station name" << endl;
	  cout << "  12. Delete station name" << endl;
	  // Edit version 1: Added "Input: " to the output string
	  cout << endl << "Input: ";
	  // End edit version 1
	}
	
	option = getInt(readFrmFile, &inpFile);
	if ((option != ADMIN_ENTER_STN_NAME) &&
	    (option != ADMIN_DELETE_STN_NAME)) {
	  logFile << "Invalid sub-option" << endl;
	  if (!readFrmFile) {
	    cout << "Invalid sub-option (" << option << ")! Please try again." << endl;
	  }
	  continue;
	}
	else if (option == ADMIN_ENTER_STN_NAME) {
	  logFile << "Executing \"Enter station name\"" << endl;

	  if (!readFrmFile) {
	    cout << "Enter complete station name: ";
	  }
	  string srcStnName = getStringWithSpaces(readFrmFile, &inpFile);
	  if (addStationName(srcStnName)) {
	    logFile << "Success" << endl;
	  }
	  else {
	    logFile << "Failed." << endl;
	  }
	  continue;
	}
	else { // option = ADMIN_DELETE_STN_NAME)
	  logFile << "Executing \"Delete station name\"" << endl;
	  if (!readFrmFile) {
	    cout << "Enter complete station name: ";
	  }
	  string srcStnName = getStringWithSpaces(readFrmFile, &inpFile);
	  if (delStationName(srcStnName)) {
	    logFile << "Success" << endl;
	  }
	  else {
	    logFile << "Failed." << endl;
	  }
	  continue;
	}

      case ADMIN_ENTER_DELETE_JOURNEY_CODE:
	logFile << "Executing \"Enter/delete journey code\"" << endl;

	if (!readFrmFile) {
	  // Edit version 1: Added some extra couts for clarity
	  cout << "****************************" << endl;
	  // End edit version 1
	  cout << endl << "Entering/deleting journey code. ";
	  cout << " Choose a sub-option:" << endl;
	  cout << "  21. Enter a new journey code" << endl;
	  cout << "  22. Delete a journey code" << endl;
	  // Edit version 1: Added "Input: " to the output string
	  cout << endl << "Input: ";
	  // End edit version 1
	}

	option = getInt(readFrmFile, &inpFile);
	if ((option != ADMIN_ENTER_JOURNEY_CODE) &&
	    (option != ADMIN_DELETE_JOURNEY_CODE)) {
	  logFile << "Invalid sub-option" << endl;
	  if (!readFrmFile) {
	    cout << "Invalid sub-option (" << option << ")! Please try again." << endl;
	    continue;
	  }
	  // Edit version 1: Closing an if branch.  This was incorrectly
	  // closed in the original version
	}
	// End edit version 1
	
	else if (option == ADMIN_ENTER_JOURNEY_CODE) {
	  logFile << "Executing \"Enter journey code\"" << endl;
	  
	  if (!readFrmFile) {
	    cout << "Enter journey code: ";
	  }
	  int journeyCode = getInt(readFrmFile, &inpFile);
	  if (!readFrmFile) {
	    cout << "Enter complete source station name: ";
	  }
	  string srcStnName = getStringWithSpaces(readFrmFile, &inpFile);
	  if (!readFrmFile) {
	    cout << "Enter complete destination station name: ";
	  }
	  string destStnName = getStringWithSpaces(readFrmFile, &inpFile);
	  if (addJourneyCode(srcStnName, destStnName, journeyCode)) {
	    logFile << "Success" << endl;
	  }
	  else {
	    logFile << "Failed." << endl;
	  }
	  continue;
	}
	else { // option = ADMIN_DELETE_JOURNEY_CODE)
	  logFile << "Executing \"Delete journey code\"" << endl;
	  if (!readFrmFile) {
	    cout << "Enter journey code: ";
	  }
	  int journeyCode = getInt(readFrmFile, &inpFile);
	  if (!readFrmFile) {
	    cout << "Enter complete source station name: ";
	  }
	  string srcStnName = getStringWithSpaces(readFrmFile, &inpFile);
	  if (!readFrmFile) {
	    cout << "Enter complete destination station name: ";
	  }
	  string destStnName = getStringWithSpaces(readFrmFile, &inpFile);
	    
	  if (delJourneyCode(srcStnName, destStnName, journeyCode)) {
	    logFile << "Success" << endl;
	  }
	  else {
	    logFile << "Failed." << endl;
	  }
	  continue;
	}
     
	break;

      case ADMIN_PRINT_TRIE:
	stnNamesTrie->printTrie();
	continue;

      // Lab 7 specific
      case ADMIN_ENTER_JOURNEY_INFO:
	int stnIndex;
	listOfObjects<TrainInfoPerStation *> *newTrainInfo;
	TrainInfoPerStation *stnTrainInfo;
	int depTime, arrTime, dayCount;
	int len, numStops, journeyCode;
	Entry<int> *stnEntry;
	int daysOfWeek;
	
	if (!readFrmFile) {
	  cout << "Enter journey code (train no.): ";
	}
	journeyCode = getInt(readFrmFile, &inpFile);

	if (!readFrmFile) {
	  cout << "Enter count of stops (including src and dest): ";
	}
	numStops = getInt(readFrmFile, &inpFile);

	if (!readFrmFile) {
	  cout << "Enter binary string of length 7 to denote days of week when train leaves source station: ";
	}
	daysOfWeek = getInt(readFrmFile, &inpFile);
	// len = daysOfWeek.length();
	// if (len != 7) {
	//   logFile << "Incorrect format for specifying days of week when train leaves source station" << endl;
	//   cout << "Incorrect format for specifying days of week when train leaves source station" << endl;
	//   break;
	// }
	
	for (int i=0; i < numStops; i++) {
	  if (!readFrmFile) {
	    cout << "Enter full station name: ";
	  }
	  string stnName = getStringWithSpaces(readFrmFile, &inpFile);
	  stnEntry = stnNameToIndex.get(stnName);
	  if (stnEntry == nullptr) {
	    logFile << "Couldn't find station " << stnName << " in stnNameToIndex dictionary." << endl;
	    cerr << "Couldn't find station " << stnName << " in stnNameToIndex dictionary." << endl;
	    continue;
	  }
	  else {
	    stnIndex = stnEntry->value;
	  }

	  if (!readFrmFile) {
	    cout << "Enter day count, arrival and departure times (-1 if not applicable): ";
	  }
	  dayCount = getInt(readFrmFile, &inpFile);
	  if ((i == 0) && (dayCount != 1)) {
	    cerr << "Source station must have day count 1; setting it to 1" << endl;
	    dayCount = 1;
	  }
	     
	  arrTime = getInt(readFrmFile, &inpFile);
	  if ((i == 0) && (arrTime != -1)) {
	    cerr << "Source station must have arrival time -1; setting it to -1" << endl;
	    arrTime = -1;
	  }
	  
	  depTime = getInt(readFrmFile, &inpFile);
	  if ((i == numStops-1) && (depTime != -1)) {
	    cerr << "Final destination station must have departure time -1; setting it to -1" << endl;
	    depTime = -1;
	  }
	  
	  // Now fill in the train information per station
	  stnTrainInfo = new TrainInfoPerStation(journeyCode, (unsigned short) i, arrTime, depTime);
	  if (stnTrainInfo == nullptr) {
	    logFile << "Memory allocation failure" << endl;
	    cerr << "Memory allocation failure." << endl;
	    continue;
	  }

	  int currDaysOfWeek = daysOfWeek;
	  for (int j = 0; j < 7; j++) {
	    if (currDaysOfWeek % 10 == 1) stnTrainInfo->setDayOfWeek(((6-j)+(dayCount-1))%7);
	    else if (currDaysOfWeek % 10 == 0) stnTrainInfo->resetDayOfWeek(((6-j)+(dayCount-1))%7);
	    else {
	      logFile << "Incorrect days of week input" << endl;
	      cerr << "Incorrect days of week input" << endl;
	      break;
	    }
	    currDaysOfWeek = currDaysOfWeek/10;
	  }
	  newTrainInfo = new listOfObjects<TrainInfoPerStation *> (stnTrainInfo);
	  if (newTrainInfo == nullptr) {
	    logFile << "Memory allocation failure." << endl;
	    cerr << "Memory allocation failure." << endl;
	    continue;
	  }
	  
	  if (stationInfo[stnIndex] == nullptr) {
	    stationInfo[stnIndex] = newTrainInfo;
	  }
	  else {
	    newTrainInfo->next = stationInfo[stnIndex];
	    if (newTrainInfo->next != nullptr) {
	      newTrainInfo->next->prev = newTrainInfo;
	    }
	    stationInfo[stnIndex] = newTrainInfo;
	  }
	}
	continue;
	// End lab 7 specific
      default:
	logFile << "Invalid admin user option (" << option << ")" << endl;
	cerr << "Invalid admin user option (" << option << ")" << endl;
	continue;
      }
    }

  } while (true);
}

bool Planner::doUserJob() {
  int option;
  string srcStnName, destStnName;

  // Edit version 1: Commenting the following declarations
  // They are no longer needed.
  // string srcPrefix, dstPrefix, tempPrefix;
  // End edit version 1
  
  string reviewString, keywordString;
  int journeyCode, reviewId, revRating, rateThresh;
  bool delReviewStatus;
  char filterChoice;
  int *hMatrix;
  listOfObjects<JourneyCodeReview> *listOfJCodeReviews, *currJCodeReview;
  listOfObjects<Review> *currReview;
  int matchStartIndex;
  int maxRevsInARound = 10;
  int numRevsInThisRound;
  Review maxRateRev;
  int contOption, numRevsInHeap;
  bool contFlag;
  
  // Edit version 1: Adding code to enable reading commands from a file
  string filterWord;
  string srcPartWords, destPartWords;
  listOfObjects<string> *listOfWords, *completions;
  bool readFrmFile = false;
  
  string inpFileName = "";
  fstream inpFile;
  // End edit version 1
  
  do {

    // Edit version 1: Added some extra couts for clarity
    // Also added condition to check if reading from file
    if (!readFrmFile) {
      cout << "****************************" << endl;
      // End edit version 1

      cout << "Please choose a user job:" << endl;
      cout << "  100. Exit user" << endl;
      cout << "  110. Enter/delete review" << endl;
      cout << "  120. Find journey reviews" << endl;

      // Edit version 1: Added the following two user commands
      cout << "  130. Read commands from a file" << endl; 
      cout << "  140. Exit reading commands from a file" << endl;
      cout << "  150. Find all journeys from station" << endl;
      // End edit version 1
      
      // Edit version 1: Added "Input: " to the output string
      cout << endl << "Input: ";
      // End edit version 1
    }

    // Edit version 1: Read either from cin or from inpFile
    // Code to read and process commands from inpFile or
    // to stop reading commands from inpFile, and revert to
    // reading commands from cin
    //
    // cin >> option;
    option = getInt(readFrmFile, &inpFile);
    
    if (!readFrmFile && (option == USER_READ_FROM_FILE)) {
      logFile << "Executing \"Read commands from file\" " << endl;
      
      cout << "  Input file name: ";
      cin >> inpFileName;
      
      inpFile.open(inpFileName, ios::in);
      if (!inpFile.is_open()) {
	cout << "Failed to open file " << inpFileName << " for reading" << endl;
	logFile << "Failed" << endl;
	inpFileName = "";
      }
      else {
	logFile << "Success" << endl;
	readFrmFile = true;
      }
      continue;
    }
    else if (readFrmFile && (option == USER_READ_FROM_FILE)) {
      logFile << "Executing \"Read commands from file\" " << endl;
      logFile << "Ignoring ..." << endl;

      cerr << "\"Read from file\" command encountered while reading from file. Ignoring ..." << endl;
      continue;
    }
    else if (readFrmFile && (option == USER_EXIT_READ_FROM_FILE)) {
      logFile << "Executing \"Exit reading commands from file\" " << endl;

      // Edit version 1: Made the message a bit more explanatory
      cout << "Finished reading and executing commands from file" << endl;
      // End edit version 1
      inpFile.close();
      if (!inpFile.is_open()) {
	logFile << "Success" << endl;
      }
      else {
	logFile << "Failed." << endl;
      }
      readFrmFile = false;
      inpFileName = "";
      continue;
    }
    else if (!readFrmFile && (option == USER_EXIT_READ_FROM_FILE)) {
      logFile << "Executing \"Exit reading commands from file\" " << endl;
      logFile << "Ignoring ..." << endl;

      cerr << "\"Exit read from file\" command while not reading from file. Ignoring ..." << endl;
      continue;
    }
    else {
      // End edit version 1
      string sStnName;
      string sPartWords;	

      switch (option) {
      case USER_EXIT:
	logFile << "Executing \"Exit normal user\"" << endl;
	
	cout << "Thank you for being a user!" << endl;
	cout << "Bye!!!" << endl;
	return true;
	
      case USER_ENTER_DELETE_REVIEW:
	logFile << "Executing \"Enter/delete review\"" << endl;
	
	// Edit version 1: Added some extra couts for clarity
	// Also added a check on the flag readFrmFile
	if (!readFrmFile) {
	  cout << "****************************" << endl;
	  // End edit version 1
	  
	  cout << "Entering/deleting station name. " << endl;
	  cout << " Choose a sub-option:" << endl;
	  cout << "  111. Enter new review" << endl;
	  cout << "  112. Delete review" << endl;
	  // Edit version 1: Added "Input: " to the output string
	  cout << endl << "Input: ";
	  // End edit version 1

	  // Edit version 1: Closing the if (!readFrmFile) brace
	}
	// End edit version 1
	
	// Edit version 1: Changing "cin >> option" to a function call
	// that either reads from cin or from an input file, as specified
	// cin >> option;
	option = getInt(readFrmFile, &inpFile);
	// End edit version 1
	
	if ((option != USER_ENTER_REVIEW) && (option != USER_DELETE_REVIEW)) {
	  logFile << "Invalid sub-option" << endl;
	  cout << "Invalid sub-option (" << option << ")! Please try again." << endl;
	  continue;
	}
	else { // option == USER_ENTER_REVIEW or option == USER_DELETE_REVIEW
	  if (option == USER_ENTER_REVIEW) {
	    logFile << "Executing \"Enter review\"" << endl;
	    
	    // Edit version 1: Adding a check on readFrmFile flag
	    if (!readFrmFile) {
	      cout << "Enter prefix of any word in source station name: ";
	    }
	    // End edit version 1

	    // Edit version 1: Changing "cin >> srcPrefix" followed by
	    // "srcStnName = chooseFromCompletions(srcPrefix)" to the following sequence
	    // of statements.  Note that this allows inputs to be read
	    // either from cin or from an input file, as specified.
	    // The following code also lets the user search for a set of completions
	    // from a space separated list of prefixes of individual words that
	    // appear in a station name.  E.g. giving "PU CANT" will return
	    // "PUNE CANTONMENT".

	    srcPartWords = getStringWithSpaces(readFrmFile, &inpFile);
	    listOfWords = findAllWords(srcPartWords);
	    if (listOfWords != nullptr) {
	      completions = stnNamesTrie->completions(listOfWords->object);
	      listOfWords = listOfWords->next;
	      trimByMatchingSubWords(completions, listOfWords);
	      srcStnName = chooseFromCompletions(completions);
	    }
	    // End edit version 1
	    
	    if (srcStnName != "") {
	      logFile << "Chosen source station: " << srcStnName << endl;

	      // Edit version 1: Adding a check on readFrmFile flag
	      if (!readFrmFile) {
		cout << "Chosen source station: " << srcStnName << endl;
	      }
	      // End edit version 1
	    }
	    else {
	      logFile << "Failure in choosing source station." << endl;
	      cout << "Failure in choosing source station." << endl;
	      continue;
	    }
	    
	    // Edit version 1: Adding a check on readFrmFile flag
	    if (!readFrmFile) {
	      cout << "Enter prefix of any word in destination station name: ";
	    }
	    // End edit version 1

	    // Edit version 1: Changing "cin >> dstPrefix" followed by
	    // "destStnName = chooseFromCompletions(destPrefix)" to the following sequence
	    // of statements.  Note that this allows inputs to be read
	    // either from cin or from an input file, as specified.
	    // The following code also lets the user search for a set of completions
	    // from a space separated list of prefixes of individual words that
	    // appear in a station name.  E.g. giving "PU CANT" will return
	    // "PUNE CANTONMENT".

	    destPartWords = getStringWithSpaces(readFrmFile, &inpFile);
	    listOfWords = findAllWords(destPartWords);
	    if (listOfWords != nullptr) {
	      completions = stnNamesTrie->completions(listOfWords->object);
	      listOfWords = listOfWords->next;
	      trimByMatchingSubWords(completions, listOfWords);
	      destStnName = chooseFromCompletions(completions);
	    }
	    // End edit version 1

	    if (destStnName != "") {
	      logFile << "Chosen destination station: " << destStnName << endl;

	      // Edit version 1: Adding a check on readFrmFile flag
	      if (!readFrmFile) {
		cout << "Chosen destination station: " << destStnName << endl;
	      }
	      // End edit version 1
	    }
	    else {
	      logFile << "Failure in choosing destination station." << endl;
	      cout << "Failure in choosing destinatoin station." << endl;
	      continue;
	    }

	    // Edit version 1: Adding a check on readFrmFile flag
	    if (!readFrmFile) {
	      cout << "Enter journey code: ";
	    }
	    // End edit version 1

	    // Edit version 1: Changing "cin >> journeyCode" to a function call
	    // that either reads from cin or from an input file, as specified
	    // cin >> journeyCode;
	    journeyCode = getInt(readFrmFile, &inpFile);
	    // End edit version 1
	
	    if (!checkValidJourneyCode(srcStnName, destStnName, journeyCode)) {
	      logFile << "Journey Code doesn't match source and destination pair" << endl;
	      cout << "Journey code doesn't match source and destination pair" << endl;
	      cout << "Ignoring command" << endl; 
	      continue;
	    }
	    else {
	      logFile << "Journey code matches source and destination pair" << endl;

	      if (!readFrmFile) {
		cout << "Enter review rating: ";
	      }
	      revRating = getInt(readFrmFile, &inpFile);
	      
	      // Edit version 1: Adding a check on readFrmFile flag
	      if (!readFrmFile) {
		cout << "Enter short review without any line break:" << endl;
	      }
	      // End edit version 1

	      // Edit version 1: Changed "cin >> reviewString" to a call to
	      // getStringWithSpaces.  This allows reading from cin as well as
	      // from inpFile, as specified.
	      // cin >> reviewString;
	      // if (getline(cin >> std::ws, reviewString)) {
	      reviewString = getStringWithSpaces(readFrmFile, &inpFile);
	      if (reviewString != "") {
		// End edit version 1
		
		logFile << "Read review: " << reviewString << endl;
	      }
	      else {
		logFile << "Failure in reading reviewString" << endl;
		cout << "Failure in reading reviewString." << endl;
		continue;
	      }
	      
	      reviewId = addReview(journeyCode, srcStnName, destStnName, reviewString, revRating);
	      if (reviewId >= 0) {
		logFile << "Successfully added review " << reviewId << endl;

		// Edit version 1: Adding a check on readFrmFile flag
		if (!readFrmFile) {
		  cout << "Added review with review id " << reviewId << endl;
		}
		// End edit version 1
	      }
	      else {
		logFile << "Failure in adding review" << endl;
		cout << "Failure in adding review" << endl;
	      }
	      continue;
	    }
	  }
	  else { // option = USER_DELETE_REVIEW)
	    logFile << "Executing \"Delete review\"" << endl;
	    
	    // Edit version 1: Adding a check on readFrmFile flag
	    if (!readFrmFile) {
	      cout << "Enter review id: " << endl;
	    }
	    // End edit version 1
	    
	    // Edit version 1: Changing "cin >> reviewId" to a function call
	    // that either reads from cin or from an input file, as specified
	    // cin >> reviewId;
	    reviewId = getInt(readFrmFile, &inpFile);
	    // End edit version 1
	    
	    if (reviewId > 0) {
	      delReviewStatus = delReview(reviewId);
	      if (delReviewStatus) {
		logFile << "Successfully deleted review " << reviewId << endl;

		// Edit version 1: Adding a check on readFrmFile flag
		if (!readFrmFile) {
		  cout << "Successfully deleted review " << reviewId << endl;
		}
		// End edit version 1
	      }
	      else {
		logFile << "Failed to delete review." << endl;
		cout << "Failed to delete review." << endl;
	      }
	    }
	    else {
	      logFile << "Invalid review id " << reviewId << endl;
	      cout << "Invalid review id " << reviewId <<  endl;
	    }
	    continue;
	  }
	}
	break;
      case USER_FIND_JOURNEYS:
	logFile << "Executing \"Find journeys\"" << endl;
	
	// Edit version 1: Adding a check on readFrmFile flag
	if (!readFrmFile) {
	  cout << "Enter prefix of any word in source station name: ";
	}
	// End edit version 1
	
	// Edit version 1: Changing "cin >> srcPrefix" followed by
	// "srcStnName = chooseFromCompletions(srcPrefix)" to the following sequence
	// of statements.  Note that this allows inputs to be read
	// either from cin or from an input file, as specified.
	// The following code also lets the user search for a set of completions
	// from a space separated list of prefixes of individual words that
	// appear in a station name.  E.g. giving "PU CANT" will return
	// "PUNE CANTONMENT".
	
	srcPartWords = getStringWithSpaces(readFrmFile, &inpFile);
	listOfWords = findAllWords(srcPartWords);
	if (listOfWords != nullptr) {
	  completions = stnNamesTrie->completions(listOfWords->object);
	  listOfWords = listOfWords->next;
	  trimByMatchingSubWords(completions, listOfWords);
	  srcStnName = chooseFromCompletions(completions);
	}
	// End edit version 1

	if (srcStnName != "") {
	  logFile << "Chosen source station: " << srcStnName << endl;
	  
	  // Edit version 1: Adding a check on readFrmFile flag
	  if (!readFrmFile) {
	    cout << "Chosen source station: " << srcStnName << endl;
	  }
	  // End edit version 1
	 
	}
	else {
	  logFile << "Failure in choosing source station." << endl;
	  cout << "Failure in choosing source station." << endl;
	  continue;
	}
	
	// Edit version 1: Adding a check on readFrmFile flag
	if (!readFrmFile) {
	  cout << "Enter prefix of any word in destination station name: ";
	}
	// End edit version 1

	// Edit version 1: Changing "cin >> dstPrefix" followed by
	// "destStnName = chooseFromCompletions(destPrefix)" to the following sequence
	// of statements.  Note that this allows inputs to be read
	// either from cin or from an input file, as specified.
	// The following code also lets the user search for a set of completions
	// from a space separated list of prefixes of individual words that
	// appear in a station name.  E.g. giving "PU CANT" will return
	// "PUNE CANTONMENT".
	
	destPartWords = getStringWithSpaces(readFrmFile, &inpFile);
	listOfWords = findAllWords(destPartWords);
	if (listOfWords != nullptr) {
	  completions = stnNamesTrie->completions(listOfWords->object);
	  listOfWords = listOfWords->next;
	  trimByMatchingSubWords(completions, listOfWords);
	  destStnName = chooseFromCompletions(completions);
	}
	// End edit version 1

	if (destStnName != "") {
	  logFile << "Chosen destination station: " << destStnName << endl;
	  
	  // Edit version 1: Adding a check on readFrmFile flag
	  if (!readFrmFile) {
	    cout << "Chosen destination station: " << destStnName << endl;
	  }
	  // End edit version 1
	}
	else {
	  logFile << "Failure in choosing destination station." << endl;
	  cout << "Failure in choosing destinatoin station." << endl;
	  continue;
	}
	
	// Edit version 1: Adding a check on readFrmFile flag
	if (!readFrmFile) {
	  cout << "Enter choice: " << endl;
	  cout << "  [k]. Filter reviews by keyword" << endl;
	  cout << "  [r]. Filter some reviews by rating" << endl;
	  cout << "  [n]. See all reviews (no filtering)" << endl;
	}
	// End edit version 1

	// Edit version 1: Changing "cin >> filterChoice" to a function call
	// that either from cin or from an input file, as specified
	// cin >> filterChoice;
	filterWord = getStringWithoutSpaces(readFrmFile, &inpFile);
	filterChoice = filterWord[0];
	// End edit version 1

	if (filterChoice == 'k') {
	  
	  // Edit version 1: Adding a check on readFrmFile flag
	  if (!readFrmFile) {
	    cout << "Enter keyword (no line breaks): ";
	  }
	  // End edit version 1

	  // Edit version 1: Changing "cin >> keywordString" to a function call
	  // that either from cin or from an input file, as specified
	  // cin >> keywordString;
	  keywordString = getStringWithSpaces(readFrmFile, &inpFile);
	  // End edit version 1
	  
	  logFile << "Filtering reviews by keyword " << keywordString << endl;
	  hMatrix = computeHMatrixForKMP(keywordString);
	}
	else if (filterChoice == 'r') {
	  logFile << "Filtering reviews by rating" << endl;

	  if (!readFrmFile) {
	    cout << "Give min rating threshold: " << endl;
	  }
	  rateThresh = getInt(readFrmFile, &inpFile);
	}
	else if (filterChoice == 'n') {
	  logFile << "Not filtering reviews" << endl;

	  // Edit version 1: Adding a check on readFrmFile flag
	  if (!readFrmFile) {
	    cout << "Not filtering reviews by keyword" << endl;
	  }
	  // End edit version 1
	  keywordString = "";
	}

	listOfJCodeReviews = findJCodeReviews(srcStnName, destStnName);
	if (listOfJCodeReviews == nullptr) {
	  logFile << "Couldn't find list of journey codes and reviews." << endl;
	  cout << "Couldn't find list of journey codes and reviews." << endl;
	  // Edit version 1: Added a newline at the end of the next print statement
	  cout << "Ignoring command" << endl;
	  // End edit version 1
	  continue;
	}
	else {
	  if ((filterChoice == 'k') || (filterChoice == 'n')) {
	    currJCodeReview = listOfJCodeReviews;
	    while (currJCodeReview != nullptr) {
	      currReview = (currJCodeReview->object).reviews;
	      
	      // Edit version 1: Added a condition to print a message if there are no reviews yet
	      if (currReview == nullptr) {
		logFile << "JCode: " << (currJCodeReview->object).jCode << " from " << srcStnName;
		logFile << " to " << destStnName << " has no reviews so far" << endl;
		cout << "JCode: " << (currJCodeReview->object).jCode << " from " << srcStnName;
		cout << " to " << destStnName << " has no reviews so far" << endl;
		currJCodeReview = currJCodeReview->next;
		continue;
	      }
	      
	      // Also added printing of the journey code before the loop for printing reviews
	      cout << endl << "===================" << endl;
	      cout << "Journey Code " << (currJCodeReview->object).jCode << " reviews" << ((keywordString == "") ? "" : " matching keyword ") << GREEN << keywordString << RESET << ":" << endl;
	      cout << "Source: " << srcStnName << ",   Destination: " << destStnName << endl << endl;
	      
	      // End edit version 1
	      
	      while (currReview != nullptr) {
		logFile << "JCode: " << (currJCodeReview->object).jCode << ", Rev: " << (currReview->object).rev << endl;
		
		if (keywordString != "") {
		  matchStartIndex = KMPMatch((currReview->object).rev, hMatrix, keywordString);
		  if (matchStartIndex != -1) {
		    logFile << "Found keyword " << keywordString << endl;
		    // Edit version 1: Commenting the following statements.  They have been
		    // move before the loop iterating over reviews.
		    // cout << "===================" << endl;
		    // cout << "Journey Code: " << (currJCodeReview->object).jCode << endl;
		    // End edit version 1
		    cout << "[Rate " << (currReview->object).rating << "] ";
		    printWithHighlight((currReview->object).rev, matchStartIndex, keywordString.length());
		    // Edit version 1: Commenting the printing of the double line boundary. This has now
		    // bee moved to after the loop finishes iterating over reviews.
		    //cout << endl << "===================" << endl;
		    cout << endl;
		    // End edit version 1
		  }
		  else {
		    logFile << "Didn't find keyword " << keywordString << endl;
		  }
		}
		else {
		  logFile << "No keyword match required. Printing review." << endl;
		  // Edit version 1: Commenting the following statements.  They have been
		  // move before the loop iterating over reviews.
		  // cout << "===================" << endl;
		  // cout << "Journey Code: " << (currJCodeReview->object).jCode << endl;
		  // End edit version 1
		  
		  cout << "[Rate " << (currReview->object).rating << "] ";
		  cout << (currReview->object).rev << endl;
		  cout << currReview->object << endl;
		  // Edit version 1: Commenting the following statement.  It has been moved
		  // after the loop iterating over reviews
		  // cout << "===================" << endl;
		  // End edit version 1
		}
		
		currReview = currReview->next;
	      }
	      // Edit version 1: Moved printing of the separator line after the loop
	      // for printing reviews.
	      cout << "===================" << endl << endl;
	      // End edit version 1
	      
	      currJCodeReview = currJCodeReview->next;
	    }
	  }
	  else if (filterChoice == 'r') {
	    currJCodeReview = listOfJCodeReviews;
	    numRevsInThisRound = 0;
	    numRevsInHeap = 0;
	    contFlag = true;
	    // Edit for Lab 8
	    Heap<Review> revHeap;
	    // End edit for lab 8

	    while ((currJCodeReview != nullptr) && (contFlag)) {
	      currReview = (currJCodeReview->object).reviews;
	      while ((currReview != nullptr) && (contFlag))  {
		numRevsInThisRound++;
		numRevsInHeap++;
		revHeap.insert(currReview->object);
		if ((currReview->next == nullptr) ||
		    (numRevsInThisRound >= maxRevsInARound)) {
		  maxRateRev = revHeap.getMax();

		  while ((maxRateRev.rating >= rateThresh) && (numRevsInHeap > 0)) {
		    cout << "JCode " << (currJCodeReview->object).jCode;
		    cout << " [Rate " << maxRateRev.rating << "]: ";
		    // Edit for Lab8
		    cout << maxRateRev.rev << endl;
		    // End edit for lab 8
		    revHeap.delMax();
		    numRevsInHeap--;
		    if (numRevsInHeap > 0) {
		      maxRateRev = revHeap.getMax();
		    }
		  }
		  cout << "Continue with more reviews? 0/1: ";
		  cin >> contOption;
		  if (contOption == 1) {
		    if (numRevsInThisRound >= maxRevsInARound) {
		      numRevsInThisRound = 0;
		    }
		  }
		  else {
		    contFlag = false;
		    continue;
		  }
		}
		currReview = currReview->next;
	      }
	      if (contFlag) {
		currJCodeReview = currJCodeReview->next;
	      }
	    }

	    if (contFlag) {
	      cout << "No more reviews for given source-destn!" << endl;
	    }
	  }
	}
	break;

      case USER_FIND_ALL_JOURNEYS_INFO:
	
	listOfObjects<string> *listOfWords, *completions;
	Entry<int> *stnEntry;
	int stnIndex;
	
	if (!readFrmFile) {
	  cout << "Enter prefix of any word in station name: ";
	}
	sPartWords = getStringWithSpaces(readFrmFile, &inpFile);
	listOfWords = findAllWords(sPartWords);
	if (listOfWords != nullptr) {
	  completions = stnNamesTrie->completions(listOfWords->object);
	  listOfWords = listOfWords->next;
	  trimByMatchingSubWords(completions, listOfWords);
	  sStnName = chooseFromCompletions(completions);
	}
	    
	if (sStnName != "") {
	  logFile << "Chosen station: " << sStnName << endl;
	  
	  if (!readFrmFile) {
	    cout << "Station: " << sStnName << endl;
	  }
	}
	else {
	  logFile << "Failure in choosing source station." << endl;
	  cout << "Failure in choosing source station." << endl;
	  continue;
	}
	
	stnEntry = stnNameToIndex.get(sStnName);
	if (stnEntry == nullptr) {
	  logFile << "Couldn't find station " << sStnName << " in stnNameToIndex dictionary." << endl;
	  cerr << "Couldn't find station " << sStnName << " in stnNameToIndex dictionary." << endl;
	  continue;
	}
	else {
	  stnIndex = stnEntry->value;
	}

	printStationInfo(stationInfo[stnIndex]);
	
	continue;

      default:
	logFile << "Invalid user option " << option << endl;
	cout << "Invalid user option (" << option << "). Please try again." << endl;
	continue;
      }
      // Edit version 1: Closing the brace for the else branch -- when the command
      // read in has to do nothing with reading or stopping reading commands from
      // an input file
    }
    // End edit version 1
  }  while (true);
}

// Edit version 1:
// The following implementations of getInt and getStringWithSpaces
// allow reading commands/inputs along with comments
// on the same line, and then selecting the command/input for
// processing, while ignoring the comments.
// This is particularly useful when reading commands/inputs from
// a file, where you might want to add a comment after a
// command/input indicating what the command/input was meant for.
//
// Comments start with the character COMMENT_START_CHAR defined at the
// top of this file.
inline int Planner::getInt(bool readFromFile, fstream *file) {
  string line;
  if (!readFromFile) {
    getline(cin >> std::ws, line);
  }
  else {
    getline(*file >> std::ws, line);
  }

  int len = line.length();
  bool doResize = false;
  int newSize = len;
  
  for (int i = 0; i < len; i++) {
    if (line.at(i) == COMMENT_START_CHAR) {
      doResize = true;
      newSize = i;
      // Remove preceding whitespaces
      for (int j = i-1; j >= 0; j--) {
	if (isspace(line.at(j))) {
	  newSize--;
	}
	else break;
      }
      break;
    }
  }

  if (doResize) {
    line.resize(newSize);
  }
    
  istringstream inpStream(line);
  int value;
  inpStream >> value;
  
  return value;
}

inline string Planner::getStringWithSpaces(bool readFromFile, fstream *file) {
  string line;
  if (!readFromFile) {
    getline(cin >> std::ws, line);
  }
  else {
    getline(*file >> std::ws, line);
  }

  int len = line.length();
  bool doResize = false;
  int newSize = len;
  
  for (int i = 0; i < len; i++) {
    if (line.at(i) == COMMENT_START_CHAR) {
      doResize = true;
      newSize = i;
      // Remove preceding whitespaces
      for (int j = i-1; j >= 0; j--) {
	if (isspace(line.at(j))) {
	  newSize--;
	}
	else break;
      }
      break;
    }
  }
    
  if (doResize) {
    line.resize(newSize);
  }

  istringstream inpStream(line);
  string value;
  getline(inpStream >> std::ws, value);
  return value;
}

inline string Planner::getStringWithoutSpaces(bool readFromFile, fstream *file) {
  string line;
  if (!readFromFile) {
    getline(cin >> std::ws, line);
  }
  else {
    getline(*file >> std::ws, line);
  }

  int len = line.length();
  bool doResize = false;
  int newSize = len;
  
  for (int i = 0; i < len; i++) {
    if (line.at(i) == COMMENT_START_CHAR) {
      doResize = true;
      newSize = i;
      // Remove preceding whitespaces
      for (int j = i-1; j >= 0; j--) {
	if (isspace(line.at(j))) {
	  newSize--;
	}
	else break;
      }
      break;
    }
  }
    
  if (doResize) {
    line.resize(newSize);
  }

  istringstream inpStream(line);
  string value;
  inpStream >> value;
  return value;
}
// End edit version 1

listOfObjects<string> * Planner::findAllWords(string text) {
  char *arrayOfChars = new char[text.length() + 1];
  if (arrayOfChars == nullptr) {
    logFile << "Memory allocation failure." << endl;
    cout << "Memory allocation failure. Aborting command." << endl;
    return nullptr;
  }

  strcpy(arrayOfChars, text.c_str());

  listOfObjects<string> *allWords = nullptr;
  const char delim[] = " ";

  char *nextWord = strtok(arrayOfChars, delim);;
  while (nextWord != nullptr) {
    listOfObjects<string> *tempWord = new listOfObjects<string> ("");

    if (tempWord == nullptr) {
      logFile << "Memory allocation error." << endl;
      cout << "Memory allocation error. Aborting" << endl;
      delete[] arrayOfChars;
      while (allWords != nullptr) {
	listOfObjects<string> *toDelete = allWords;
	allWords = allWords->next;
	delete toDelete;
      }
      return nullptr;
    }
    else {
      tempWord->object = nextWord;
      tempWord->next = allWords;
      allWords = tempWord;
    }

    nextWord = strtok(NULL, delim);
  }

  return allWords;
}

void Planner::clearJCRMatrixEntry(int row, int col) {

  listOfObjects<JourneyCodeReview> *currJCR = jCRMatrix[row][col];

  // Can be improved
  while (currJCR != nullptr) {
    listOfObjects<JourneyCodeReview> *toDeleteJCR = currJCR;
    currJCR = currJCR->next;
    listOfObjects<Review> *currReview = (toDeleteJCR->object).reviews;
    while (currReview != nullptr) {
      listOfObjects<Review> *toDeleteReview = currReview;
      currReview = currReview->next;
      delete toDeleteReview;
    }
    delete toDeleteJCR;
  }

  // Edit version 2: As pointed out by a student
  jCRMatrix[row][col] = nullptr;
  
  return;
}

bool Planner::addStationName(string stnName) {
  // First check if station name already exists

  Entry<int> *stnIndexEntry = stnNameToIndex.get(stnName);
  if (stnIndexEntry != nullptr) {
    logFile << "Station name " << stnName << " already exists with index " << stnIndexEntry->value << endl;
    cout << "Station name " << stnName << " already exists." << endl;
    return true;
  }

  // stnName doesn't exist in the system
  // Enter it in stnNameToIndex

  int freeIndex = stnNameToIndex.findFreeIndex(stnName);
  if (freeIndex == -1) {
    logFile << "Failed to find free index in stnNameToIndex dictionary." << endl;
    cout << "Failed to find free index in stnNameToIndex dictionary" << endl;
    return false;
  }
  
  Entry<int> newEntry(-1);
  newEntry.key = stnName;
  newEntry.value = freeIndex;
  if (!stnNameToIndex.put(newEntry)) {
    logFile << "Failed to insert in stnNameToIndex dictionary." << endl;
    cout << "Failed to insert in stnNameToIndex dictionary" << endl;
    return false;
  }
  
  // Now find the words in stnName as separate strings, and
  // insert them in the stnNamesTrie.
  listOfObjects<string> *allWords = findAllWords(stnName);
  if (allWords == nullptr) {
    logFile << "Failed to add station name \"" << stnName << "\"" << endl;
    return false;
  }
  else {
    // Do trie insertion for each word in allWords
    listOfObjects<string> *currWord = allWords;
    bool successFlag = true;
    
    while (currWord != nullptr) {
      if (!stnNamesTrie->insert(currWord->object, freeIndex)) {
	logFile << "Failed to insert \"" << currWord->object << "\" (for station name \"" << stnNameToIndex.getKeyAtIndex(freeIndex) << "\") in trie" << endl;
	cout << "Failed to insert \"" << currWord->object << "\" (for station name \"" << stnNameToIndex.getKeyAtIndex(freeIndex) << "\") in trie" << endl;
	successFlag = false;
	break;
      }
      else {
	logFile << "Successfully inserted \"" << currWord->object << "\" (for station name \"" << stnNameToIndex.getKeyAtIndex(freeIndex) << "\") in trie" << endl;
	// Edit version 1: Commenting the following extraneous output
	// cout << "Successfully inserted " << currWord->object << endl;
	// End edit version 1
	currWord = currWord->next;
      }
    }

    // Now free up the temporary data structures
    // Can be improved
    while (allWords != nullptr) {
      listOfObjects<string> *toDelete = allWords;
      allWords = allWords->next;
      delete toDelete;
    }

    // Finally increment numStations
    numStations ++;
    
    return true;
  }
}

bool Planner::delStationName(string stnName) {
  // First check if station name exists in system

  Entry<int> *stnIndexEntry = stnNameToIndex.get(stnName);
  if (stnIndexEntry == nullptr) {
    logFile << "Station name " << stnName << " doesn't exist" << endl;
    cout << "Station name " << stnName << " doesn't exist." << endl;
    return true;
  }

  int stnIndex = stnIndexEntry->value;
  
  // stnName exists in the system and must be deleted.
  
  // First find the words in stnName as separate strings and remove the
  // corresponding trie entries, as appropriate (read problem statement).
  
  listOfObjects<string> *allWords = findAllWords(stnName);
  if (allWords == nullptr) {
    logFile << "Failed to delete station name" << endl;
    return false;
  }
  else {
    // Do trie deletion for each word in allWords
    listOfObjects<string> *currWord = allWords;
    bool successFlag = true;
    
    while (currWord != nullptr) {
      if (!stnNamesTrie->del(currWord->object, stnName)) {
	logFile << "Failed to delete \"" << currWord->object << "\" (for station name \"" << stnName << "\") in trie" << endl;
	cout << "Failed to delete \"" << currWord->object << "\" (for station name \"" << stnName << "\") in trie" << endl;
	successFlag = false;
	break;
      }
      else {
	logFile << "Successfully deleted \"" << currWord->object << "\" (for station name \"" << stnName << "\") in trie" << endl;
	cout << "Successfully deleted" << endl;
	currWord = currWord->next;
      }
    }

    // Now remove stnName from stnNameToIndex
    if (!stnNameToIndex.remove(stnName)) {
      logFile << "Couldn't remove " << stnName << " from stnNameToIndex dictionary" << endl;
      cout << "Couldn't remove " << stnName << " from stnNameToIndex dictionary" << endl;
      return false;
    }

    // Free up the temporary data structures
    // Can be improved
    while (allWords != nullptr) {
      listOfObjects<string> *toDelete = allWords;
      allWords = allWords->next;
      delete toDelete;
    }

    // Finally free up the corresponding entries in the jCRMatrix;
    for (int i = 0; i < DICT_SIZE; i++) {
      if (i != stnIndex) {
	clearJCRMatrixEntry(stnIndex, i);
      }
      clearJCRMatrixEntry(i, stnIndex);
    }

    // And to end it all, decrement numStations
    numStations --;
    
    return true;
  }
}

bool Planner::checkValidJourneyCode(string srcStnName, string destStnName, int jCode) {

  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);  
  int srcStnIndex, destStnIndex;
  
  if ((srcStnIndexEntry == nullptr) || (srcStnIndexEntry->value == -1)) {
    logFile << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary" << endl;
    cout << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary" << endl;
    return false;
  }

  if ((destStnIndexEntry == nullptr) || (destStnIndexEntry->value == -1)) {
    logFile << "Couldn't find " << destStnName << " in stnNameToIndex dictionary" << endl;
    cout << "Couldn't find " << destStnName << " in stnNameToIndex dictionary" << endl;
    return false;
  }

  srcStnIndex = srcStnIndexEntry->value;
  destStnIndex = destStnIndexEntry->value;
  listOfObjects<JourneyCodeReview> *currJCRev = jCRMatrix[srcStnIndex][destStnIndex];
  while (currJCRev != nullptr) {
    if ((currJCRev->object).jCode == jCode) {
      return true;
    }
    else {
      currJCRev = currJCRev->next;
    }
  }
  return false;
}

bool Planner::addJourneyCode(string srcStnName, string destStnName, int jCode) {

  if (checkValidJourneyCode(srcStnName, destStnName, jCode)) {
    logFile << "Journey code already exists in system for given src, dest" << endl;
    cout << "Journey code already exists in system for given src, dest" << endl;
    return true;
  }

  // Journey code doesn't exist in system and must be added
  
  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);

  int srcStnIndex, destStnIndex;
  
  if ((srcStnIndexEntry == nullptr) || (srcStnIndexEntry->value == -1)) {
    logFile << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary" << endl;
    cout << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary" << endl;
    return false;
  }

  if ((destStnIndexEntry == nullptr) || (destStnIndexEntry->value == -1)) {
    logFile << "Couldn't find " << destStnName << " in stnNameToIndex dictionary" << endl;
    cout << "Couldn't find " << destStnName << " in stnNameToIndex dictionary" << endl;
    return false;
  }

  srcStnIndex = srcStnIndexEntry->value;
  destStnIndex = destStnIndexEntry->value;
  
  JourneyCodeReview newJCRev;
  newJCRev.jCode = jCode;
  newJCRev.reviews = nullptr;

  listOfObjects<JourneyCodeReview> *newJCRevEntry = new listOfObjects<JourneyCodeReview> (newJCRev);
  if (newJCRevEntry == nullptr) {
    logFile << "Memory allocation failure." << endl;
    cout << "Memory allocation failure" << endl;
    return false;
  }
  else {     
    newJCRevEntry->next = jCRMatrix[srcStnIndex][destStnIndex];
    jCRMatrix[srcStnIndex][destStnIndex] = newJCRevEntry;   
    
    // Finally increment numJourneyCodes
    numJCodeSrcDestn ++;
    return true;
  }
}

bool Planner::delJourneyCode(string srcStnName, string destStnName, int jCode) {

  if (!checkValidJourneyCode(srcStnName, destStnName, jCode)) {
    logFile << "Journey code does not exist in system for given src, dest" << endl;
    cout << "Journey code does not exist in system for given src, dest" << endl;
    return true;
  }

  // Journey code exists in system for given src, dest pair and must be deleted
  
  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);

  int srcStnIndex, destStnIndex;
  
  if ((srcStnIndexEntry == nullptr) || (srcStnIndexEntry->value == -1)) {
    logFile << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary" << endl;
    cout << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary" << endl;
    return false;
  }

  if ((destStnIndexEntry == nullptr) || (destStnIndexEntry->value == -1)) {
    logFile << "Couldn't find " << destStnName << " in stnNameToIndex dictionary" << endl;
    cout << "Couldn't find " << destStnName << " in stnNameToIndex dictionary" << endl;
    return false;
  }

  srcStnIndex = srcStnIndexEntry->value;
  destStnIndex = destStnIndexEntry->value;

  listOfObjects<JourneyCodeReview> *currJCRevEntry = jCRMatrix[srcStnIndex][destStnIndex];
  listOfObjects<JourneyCodeReview> *prevJCRevEntry = nullptr;

  while (currJCRevEntry != nullptr) {
    if ((currJCRevEntry->object).jCode == jCode) {
      // Delete all reviews for this src, dest, jCode combination
      // Can be improved
      listOfObjects<Review> *currRev = (currJCRevEntry->object).reviews;
      while (currRev != nullptr) {
	listOfObjects<Review> *toDeleteRev = currRev;
	currRev = currRev->next;
	delete toDeleteRev;
      }

      if (prevJCRevEntry == nullptr) {
	jCRMatrix[srcStnIndex][destStnIndex] = currJCRevEntry->next;
      }
      else {
	prevJCRevEntry->next = currJCRevEntry->next;
      }
      listOfObjects<JourneyCodeReview> *toDeleteJCRevEntry = currJCRevEntry;
      currJCRevEntry = currJCRevEntry->next;
      numJCodeSrcDestn --;
      delete toDeleteJCRevEntry;
    }
    else {
      prevJCRevEntry = currJCRevEntry;
      currJCRevEntry = currJCRevEntry->next;
    }
  }
  return true;
}

int Planner::addReview(int jCode, string srcStnName, string destStnName, string review, int rating=0) {
  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);

  int srcStnIndex, destStnIndex;

  if ((srcStnIndexEntry == nullptr) || (srcStnIndexEntry->value == -1)) {
    logFile << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary" << endl;
    cout << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary" << endl;

    // Edit version 2: returning -1 instead of false
    return -1;
    // End edit version 2
  }

  if ((destStnIndexEntry == nullptr) || (destStnIndexEntry->value == -1)) {
    logFile << "Couldn't find " << destStnName << " in stnNameToIndex dictionary" << endl;
    cout << "Couldn't find " << destStnName << " in stnNameToIndex dictionary" << endl;
    // Edit version 2: returning -1 instead of false
    return -1;
    // End edit version 2
  }

  srcStnIndex = srcStnIndexEntry->value;
  destStnIndex = destStnIndexEntry->value;
  
  listOfObjects<JourneyCodeReview> *currJCRevEntry = jCRMatrix[srcStnIndex][destStnIndex];
  while (currJCRevEntry != nullptr) {
    if ((currJCRevEntry->object).jCode == jCode) {
      listOfObjects<Review> *currRev = (currJCRevEntry->object).reviews;
      lastReviewId++;
      string revWithId = "[" + to_string(lastReviewId) + "]: " +  review;
      Review newRevEntry(rating, lastReviewId, revWithId);
      listOfObjects<Review> *newRev = new listOfObjects<Review> (newRevEntry);
      if (newRev == nullptr) {
	logFile << "Memory allocation failure." << endl;
	cout << "Memory allocation failure" << endl;

	// Edit version 2: returning -1 instead of false
	return -1;
	// End edit version 2
      }
      newRev->next = currRev;
      (currJCRevEntry->object).reviews = newRev;

      // Edit version 2: Returning lastReviewId instead of true
      // return true;
      return lastReviewId;
      // End edit version 2
    }
    else {
      currJCRevEntry = currJCRevEntry->next;
    }
  }

  // Couldn't find the required journey code
  // This is an error condition
  logFile << "Couldn't find journey code " << jCode << " for source " << srcStnName << " and destination " << destStnName << endl;
  cout << "Couldn't find journey code " << jCode << " for source " << srcStnName << " and destination " << destStnName << endl;
  
  // Edit version 2: returning -1 instead of false
  return -1;
  // End edit version 2
}

bool Planner::delReview(int reviewId) {

  return false;
}

listOfObjects<JourneyCodeReview> * Planner::findJCodeReviews(string srcStnName, string destStnName) {
  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);  

  int srcStnIndex, destStnIndex;
  
  if ((srcStnIndexEntry == nullptr) || (srcStnIndexEntry->value == -1)) {
    logFile << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary" << endl;
    cout << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary" << endl;
    return nullptr;
  }
  
  if ((destStnIndexEntry == nullptr) || (destStnIndexEntry->value == -1)) {
    logFile << "Couldn't find " << destStnName << " in stnNameToIndex dictionary" << endl;
    cout << "Couldn't find " << destStnName << " in stnNameToIndex dictionary" << endl;
    return nullptr;
  }

  srcStnIndex = srcStnIndexEntry->value;
  destStnIndex = destStnIndexEntry->value;

  return (jCRMatrix[srcStnIndex][destStnIndex]);
}

inline void Planner::printWithHighlight(string text, int startHLight, int lenHLight) {

  int endHLight = startHLight + lenHLight - 1;
  
  if (!((startHLight >= 0) && (startHLight < text.length()) &&
	(lenHLight > 0) && (endHLight < text.length()))) {
    logFile << "Incorrect arguments for printWithHighlight" << endl;
    cout << "Incorrect arguments for printing with highlighting. Going ahead with normal print" << endl;
    cout << text;
  }
  
  string prefix = (startHLight > 0) ? text.substr(0, startHLight) : "";
  string hLight = text.substr(startHLight, lenHLight);
  string suffix = (endHLight < text.length()-1) ? text.substr(endHLight+1, text.length()-endHLight-1) : "";

  cout << prefix;
  cout << GREEN << hLight << RESET;
  cout << suffix;
}

// Edit version 1: Changed signature of following function.
// Also deleting/commenting the first two statements of the original
// function. These statements are not needed any more.
string Planner::chooseFromCompletions(listOfObjects<string> *completions) {
  // int len = prefix.length();
  // listOfObjects<string> *completions = stnNamesTrie->completions(prefix);
  // End edit version 1
  
  if (completions != nullptr) {
    if (completions->next == nullptr) {
      // Only one completion possible
      // Edit version 1: Commenting the following extraneous output 
	// cout << "Only completion: " << completions->object << endl;
      // End ewdit version 1
      return (completions->object);
    }
    else {
      // Multiple completions possible
      cout << "Enter choice number: " << endl;
      int choiceCount = 0;
      listOfObjects<string> *currCompletion = completions;
      while (currCompletion != nullptr) {
	cout << choiceCount << ": " << currCompletion->object << endl;
	currCompletion = currCompletion->next;
	choiceCount++;
      }
      cout << endl;
      int choice;
      do {
	cin >> choice;
	if (!(choice >= 0) and (choice < choiceCount)) {
	  cout << "Invalid choice.  Please try again." << endl;
	  continue;
	}
	else {
	  break;
	}
      } while (true);
	  
      choiceCount = 0;
      while (completions != nullptr) {
	if (choiceCount == choice) {
	  return completions->object;
	}
	choiceCount++;
	completions = completions->next;
      }

      // Execution should never reach here
      return "";
    }     
  }
  else {
    cout << "No completions possible" << endl;
    return "";
  }
}

// Edit version 1: Adding one more helper function
void Planner::trimByMatchingSubWords(listOfObjects<string> * &completions, listOfObjects<string> *listOfSubWords) {
  listOfObjects<string> *currCompletion, *prevCompletion, *currSubWord;
  listOfObjects<string> *toDeleteCompletion;

  currSubWord = listOfSubWords;
  while (currSubWord != nullptr) {
    currCompletion = completions;
    prevCompletion = nullptr;
    while (currCompletion != nullptr) {
      if ((currCompletion->object).find(currSubWord->object) == std::string::npos) {
	// This completion doesn't match the subword, so remove it
	toDeleteCompletion = currCompletion;
	if (prevCompletion == nullptr) {
	  completions = currCompletion->next;
	}
	else {
	  prevCompletion->next = currCompletion->next;
	}
	currCompletion = currCompletion->next;
	delete toDeleteCompletion;
      }
      else {
	// This completion matches the subword, so retain it for now
	prevCompletion = currCompletion;
	currCompletion = currCompletion->next;
      }
    }
    currSubWord = currSubWord->next;
  }

  // By this time, completions has only the list of completions that match all subwords
}
// End edit version 1

void Planner::printStationInfo(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Expanding information in stnInfoList to get a list of train info
  // in which each element of the list refers to a single day of the
  // week.  This is the list that has to be finally sorted using
  // quicksort.

  currList = stnInfoList;
  expandedList = nullptr;
  int listLength = 0;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
      // Make as many copies of currInfo as the total count of days in the week
      // when this train runs from/to this station
      int jCode = currInfo->journeyCode;
      int stSeq = currInfo->stopSeq;
      int arrTime = currInfo->arrTime;
      int depTime = currInfo->depTime;
    
      for (int i=0; i < 7; i++) {
	if (currInfo->daysOfWeek[i]) {
	  TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
	  if (newExpandedElement == nullptr) {
	    logFile << "Memory allocation failure." << endl;
	    cerr << "Memory allocation failure." << endl;
	    continue;
	  }
	  newExpandedElement->setDayOfWeek(i);

	  listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
	  if (newExpandedListElement == nullptr) {
	    logFile << "Memory allocation failure." << endl;
	    cerr << "Memory allocation failure." << endl;
	    continue;
	  }

	  if (expandedList == nullptr) {
	    expandedList = newExpandedListElement;
	  }
	  else {
	    newExpandedListElement->next = expandedList;
	    expandedList->prev = newExpandedListElement;
	    expandedList = newExpandedListElement;
	  }
	  listLength++;
	}
      }
    }
    currList = currList->next;
  }

  Quicksort(expandedList);
  // QuicksortSimple(expandedList, 0, listLength-1);
  
  currList = expandedList;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
      cout << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) {
	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1) {
	cout << "Starts";
      }
      else {
	cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1) {
	cout << "Ends";
      }
      else {
	cout << currInfo->depTime;
      }
      cout << endl;
    }
    currList = currList->next;
  }
  cout << endl;
}

#endif
