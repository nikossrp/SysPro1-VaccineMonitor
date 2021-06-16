#ifndef Types_H_
#define Types_H_
#include <string.h>
#include "Date.h"
#define NUMBER_OF_COUNTRIES 195

// max number of buckets (its depends from lines in citizenRecordsFile)
#define MAXSIZE 10000      
  

// info about the viruse
typedef struct {    
    char* virusName;
    bool vaccinated;
    Date* date;

}Info;


typedef struct {
    int nBuckets;
    int nRecords;
    int nCitizens;
    int nCountires;
    int nViruses;
    int nVacciated_Lists;
    int nNo_Vacciated_Lists;
    int nBloomFilters;
    double time_for_app;
    double time_for_buckets;

}Statistics;

// consistence of the date format
bool consistentDate_str (char* date);

// consistence of the numbers in date
bool consistentDate (Date* date);

// count the words in a string based on spaces
int countWords (char* str);

// Check if the name of firstname/lastName/country is consistent
bool consistentName (char* name_lastName);

//check citizenID/day,month,year/age
bool consistentNumber (char* id);

void printStatistics (Statistics stats);

#endif
