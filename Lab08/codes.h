#ifndef CODES_H
#define CODES_H

#define MAGIC_CODE 1879
#define EXIT_CODE  0
#define ADMIN_LEVEL -1
#define USER_LEVEL -2
#define EXIT_LEVEL -3
#define INVALID_LEVEL -4

#define ADMIN_EXIT 0
#define ADMIN_ENTER_DELETE_STN_NAME 1
#define ADMIN_ENTER_STN_NAME 11
#define ADMIN_DELETE_STN_NAME 12
#define ADMIN_ENTER_DELETE_JOURNEY_CODE 2
#define ADMIN_ENTER_JOURNEY_CODE 21
#define ADMIN_DELETE_JOURNEY_CODE 22
#define ADMIN_READ_FROM_FILE 3
#define ADMIN_EXIT_READ_FROM_FILE 4
// Edit version 1: Added the following code
#define ADMIN_PRINT_TRIE 5
// End edit version 1
// Lab 7 specific
#define ADMIN_ENTER_JOURNEY_INFO 6
// End lab 7 specific

#define USER_EXIT 100
#define USER_ENTER_DELETE_REVIEW 110
#define USER_ENTER_REVIEW 111
#define USER_DELETE_REVIEW 112
#define USER_FIND_JOURNEYS 120
// Edit version 1: Added the following two codes
#define USER_READ_FROM_FILE 130
#define USER_EXIT_READ_FROM_FILE 140
// End edit version 1
#define USER_FIND_ALL_JOURNEYS_INFO 150



#define RESET "\033[0m"
#define GREEN "\033[32m"
// Edit version 1: Added the code for printing ASCII text in red and blue
#define RED "\033[31m"
#define BLUE "\033[34m"
// End edit version 1
#endif
