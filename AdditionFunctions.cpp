#include <iostream>
#include "AdditionTypes.h"

using namespace std;

// consistence ws pros tin morfh tou date
bool consistentDate_str(char* date) {

    if (date == NULL)
    return true;
    
    int pavla = 0;

    while(*date) {
        if (*date == '-')
            pavla++;
        if ((*date < '0' || *date > '9') && *date != '-') //  e.g.   1/1/2011
            return false;
        *date++;
    }

    if (pavla != 2)
        return false;

    return true;
}


// consistence ws pros tous arithmous tou date
bool consistentDate(Date* date)
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int day = now->tm_mday;
    int month = now->tm_mon + 1;
    int year = now->tm_year + 1900;
    Date* date_now = new Date(day, month, year);

    if (date) {
        // if (*date > *date_now) {     //anw fragma tin shmerini hmerominia
        //     delete date_now;
        //     return false;
        // }

        if ((date->get_day() > 30) || (date->get_day() <= 0)) {
            delete date_now;
            return false;
        }

        if ((date->get_month() > 12) || (date->get_month() <= 0)) {
            delete date_now;
            return false;
        }

    }

    delete date_now;
    return true;
}


int countWords (char* str)
{
    int count = 0;

    while(*str) {
        if (*str == ' ')
            count++;
        *str++;
    }
    return count + 1;
}


bool consistentName(char* name_lastName)
{
    while (*name_lastName)
    {   
        if (*name_lastName >='0' && *name_lastName <= '9')
            return false;

        *name_lastName++;
    }

    return true;
}


bool consistentNumber (char* id)
{
    while (*id)
    {
        if (*id < '0' || *id > '9')
            return false;
        *id++;
    }

    return true;
}


void printStatistics (Statistics stats)
{
    cout << "\n*********** Statistics ***********\n";
    printf("Application was loaded at: %.2fsec\n", stats.time_for_app);
    printf("%d Buckets was prepared at %.3fsec\n", stats.nBuckets, stats.time_for_buckets);
    cout << "Loaded " << stats.nRecords << " Records\n";
    cout << "Citizens " << stats.nCitizens << endl;
    cout << "Countries " << stats.nCountires << endl;
    cout << "Viruses " << stats.nViruses << endl;
    cout << "BloomFilters " <<stats.nBloomFilters << endl;
    cout << "Vaccinated Skip Lists " << stats.nVacciated_Lists << endl;
    cout << "NO Vaccinated Skip Lists " << stats.nNo_Vacciated_Lists <<"\n";
    cout << "*******************************\n\n";
}