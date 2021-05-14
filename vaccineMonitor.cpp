#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <time.h>
#include "Application.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 5 || argc > 5) {
        cout << "Failure usage:./vaccineMonitor -c citizenRecordsFile -b <bloomSize: number>" << endl;
        exit(EXIT_FAILURE);
    }


    string bloomSize_str = "";
    int bloomSize = 0;
    char* c_fileName;
    bool running = true;

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-b")) {
            bloomSize_str = argv[++i];
            bloomSize = stoi(bloomSize_str);
            if (bloomSize <= 0 ) {
                cout << "Error at bloomSize, it shouldn't be negative or zero\n";
                exit(EXIT_FAILURE);
            }
        }

        if (!strcmp(argv[i], "-c")) {
            c_fileName = strdup(argv[++i]);
        }
    }


    char* c_line = NULL;
    string path = "Records/";
    string fileName(c_fileName, strlen(c_fileName) + 1);
    free (c_fileName);
    fileName = path + fileName;
    string line_str;
    int nWords = 0;
    string id = "-1";
    int count_Record = 0;
    ifstream file_temp(fileName);
    int buckets = 0;
    int failed = 0;
    Statistics stats = { 
        .nBuckets = 0,  .nRecords = 0, .nCitizens = 0,
        .nCountires = 0, .nViruses = 0, .nVacciated_Lists = 0,
        .nNo_Vacciated_Lists = 0, .nBloomFilters = 0,
        .time_for_app = 0, .time_for_buckets = 0 
    };

    clock_t tStart = clock();

    //get the number of buckets for hash tables
    if (file_temp) {     

        while (getline(file_temp, line_str) && (buckets != MAXSIZE)) {
            buckets++;
        }
    }
    else {
        cout << "File failed to open\n";
        failed = 1;
    }

    file_temp.close();
    stats.time_for_buckets = (double (clock() - tStart) / CLOCKS_PER_SEC);

    ifstream file(fileName);

    App* app = new App (bloomSize, buckets);

    /* Take the records from the file */
    if(file) {

        while(getline(file, line_str))
        {
            c_line = strdup(line_str.c_str());
            id = app->Insert_Record(c_line);  
            if (id.compare("-1")) {
                count_Record++;
            }
            // cout << "Inserted record: " << id << endl;
        }
    }
    else {
        if (failed == 0)
            cout << "File failed to open\n";
    }


    file.close();
    stats.time_for_app =  (double (clock() - tStart) / CLOCKS_PER_SEC);
    stats.nBuckets = buckets;
    stats.nRecords = count_Record;
    stats.nCitizens = app->get_nCitizens();
    stats.nViruses = app->get_nViruses();
    stats.nCountires = app->get_nCountries();
    stats.nVacciated_Lists = app->get_nVaccSkipList();
    stats.nNo_Vacciated_Lists = app->get_nNoVaccSkipList();
    stats.nBloomFilters = app->get_nBloomFilters();
    // printStatistics(stats);
    
    

    cout << "\nEnter commands:\n";

    //input
    while (running) {
        cout << endl;
        getline(cin, line_str);
        c_line = strdup (line_str.c_str());
        nWords = countWords(c_line);

        if (line_str.empty()) {      // note: getline not read '\n'
            free(c_line);
            continue;
        }

        char* command = strtok(c_line, " ");

        // if (!strcmp(command, "/print")) {
        //     app->print_Records();
        //     free(c_line);
        //     continue;
        // }

        if(!strcmp(command, "/exit")) { 
            free(c_line);
            cout << endl;
            break;
        }


        if ((strcmp(command, "/exit") && strcmp(command, "/vaccineStatusBloom") &&
            strcmp(command, "/vaccineStatus") && strcmp(command, "/populationStatus") &&
            strcmp(command, "/popStatusByAge") && strcmp(command, "/insertCitizenRecord") &&
            strcmp(command, "/vaccinateNow") && strcmp(command, "/list-nonVaccinated-Persons")) || nWords == 1) {
            cout << "ERROR COMMAND...type one of the following command:\n";
            cout << "/vaccineStatusBloom citizenID virusName\n";
            cout << "/vaccineStatus citizenID [virusName]\n";
            cout << "/populationStatus [country] virusName date1 date2\n";
            cout << "/popStatusByAge [country] virusName date1 date2\n";
            cout << "/insertCitizenRecord citizenID firstName lastName country age virusName NO/YES date\n";
            cout << "/vaccinateNow citizenID firstName lastName country age virusName\n";
            cout << "/list-nonVaccinated-Persons virusName\n";
            cout << "/exit" << endl;
            free(c_line);
            continue;
        }

        if(!strcmp(command, "/vaccineStatusBloom")) {
            if (nWords != 3) {
                free(c_line);
                cout << "ERROR COMMAND\n";
                cout << "Try: /vaccineStatusBloom citizenID virusName\n";
                continue;
            }

            char* citizenID = strtok(NULL, " ");
            char* virusName = strtok(NULL, "");
            app->vaccinatedStatusBloom(citizenID, virusName);
        }

        if (!strcmp(command, "/vaccineStatus")) 
        {
            if (nWords != 3 && nWords != 2) {
                free(c_line);
                cout << "ERROR COMMAND\n";
                continue;
            }

            char* citizenID = strtok(NULL, " ");

            if (!consistentNumber(citizenID)) {
                free(c_line);
                cout << "ERROR COMMAND\n";
                cout << "Try: /vaccineStatus citizenID [virusName]\n";

                continue;
            }

            if (nWords == 3) {
                char* virusName = strtok(NULL, "");
                app->vaccineStatus(citizenID, virusName);
            }
            else if (nWords == 2) {
                app->vaccineStatus(citizenID);
            }
        }

        if (!strcmp(command, "/populationStatus")) {
            if (nWords > 5 || nWords < 4) {
                free(c_line);
                cout << "ERROR COMMAND\n";
                cout << "Try: /populationStatus [country] virusName date1 date2\n";
                continue;
            }

            Date* date1 = new Date;
            Date* date2 = new Date;
            char* test = strtok(NULL, " ");
            int month, day, year;
            char* c_month, *c_day, *c_year;
            char* virusName, *c_date1, *c_date2;
            char* country = app->get_country(test);

            
            if(country && nWords == 5) {

                virusName = strtok(NULL, " ");
                c_date1 = strtok(NULL, " ");
                c_date2 = strtok(NULL, "");

                if (!consistentDate_str(c_date1) || !consistentDate_str(c_date2)) {
                    cout << "ERROR COMMAND (invalid date format)\n";
                    free(c_line);
                    delete date1;
                    delete date2;
                    continue;
                }

                // Day 1
                c_day = strtok(c_date1, "-");
                sscanf(c_day, "%d", &day);
                date1->set_day(day);

                // Month 1
                c_month = strtok(NULL, "-");
                sscanf(c_month, "%d", &month);
                date1->set_month(month);

                //Year 1
                c_year = strtok(NULL, "-");
                int year;
                sscanf(c_year, "%d", &year);
                date1->set_year(year);

                // Day 2
                c_day = strtok(c_date2, "-");
                sscanf(c_day, "%d", &day);
                date2->set_day(day);

                // Month 2
                c_month = strtok(NULL, "-");
                sscanf(c_month, "%d", &month);
                date2->set_month(month);

                // Year 2
                c_year = strtok(NULL, "-");
                sscanf(c_year, "%d", &year);
                date2->set_year(year);

                if (*date2 < *date1) {
                    cout << "ERROR COMMAND: " << *date1 << " > " << *date2 << endl;
                    free(c_line);
                    delete date1;
                    delete date2;
                    continue;
                }

                app->populationStatus(country, virusName, date1, date2);
            }
            else if ( nWords == 4 ) {

                virusName = strdup(test);
                c_date1 = strtok(NULL, " ");
                c_date2 = strtok(NULL, "");

                if (!consistentDate_str(c_date1) || !consistentDate_str(c_date2)) {
                    cout << "ERROR COMMAND (invalid date format)\n";
                    free(c_line);
                    delete date1;
                    delete date2;
                    free(virusName);
                    continue;
                }

                // Day 1
                c_day = strtok(c_date1, "-");
                sscanf(c_day, "%d", &day);
                date1->set_day(day);

                //  Month 1
                c_month = strtok(NULL, "-");
                sscanf(c_month, "%d", &month);
                date1->set_month(month);

                // Year 1
                c_year = strtok(NULL, "-");
                sscanf(c_year, "%d", &year);
                date1->set_year(year);

                // Day 2
                c_day = strtok(c_date2, "-");
                sscanf(c_day, "%d", &day);
                date2->set_day(day);

                // Month 2
                c_month = strtok(NULL, "-");
                sscanf(c_month, "%d", &month);
                date2->set_month(month);

                // Year 2
                c_year = strtok(NULL, "-");
                sscanf(c_year, "%d", &year);
                date2->set_year(year);

                if (*date2 < *date1) {
                    cout << "ERROR COMMAND: " << *date1 << " > " << *date2 << endl;
                    free(c_line);
                    free(virusName);
                    delete date1;
                    delete date2;
                    continue;
                }

                app->populationStatus(NULL, virusName, date1, date2);

                free(virusName);
                
            }
            else {
                cout << "No records for country "<< test << "\n";
            }

            delete date1;
            delete date2;
        }

        if (!strcmp(command, "/popStatusByAge")) {

            if (nWords > 5 || nWords < 4) {
                free(c_line);
                cout << "ERROR COMMAND\n";
                cout << "Try: /popStatusByAge [country] virusName date1 date2\n";
                continue;
            }

            Date* date1 = new Date;
            Date* date2 = new Date;
            char* test = strtok(NULL, " "); //get country if exist at command
            int month, day, year;
            char* c_month, *c_day, *c_year;
            char* virusName, *c_date1, *c_date2;
            char* country = app->get_country(test);
            
            if(country && nWords == 5) {

                virusName = strtok(NULL, " ");
                c_date1 = strtok(NULL, " ");
                c_date2 = strtok(NULL, "");

                if (!consistentDate_str(c_date1) || !consistentDate_str(c_date2)) {
                    cout << "ERROR COMMAND: (invalid date format)\n";
                    free(c_line);
                    delete date1;
                    delete date2;
                    continue;
                }

                // Day 1
                c_day = strtok(c_date1, "-");
                sscanf(c_day, "%d", &day);
                date1->set_day(day);

                // Month 1
                c_month = strtok(NULL, "-");
                sscanf(c_month, "%d", &month);
                date1->set_month(month);

                // Year 1
                c_year = strtok(NULL, "-");
                int year;
                sscanf(c_year, "%d", &year);
                date1->set_year(year);

                // Day 2
                c_day = strtok(c_date2, "-");
                sscanf(c_day, "%d", &day);
                date2->set_day(day);

                // Month 2
                c_month = strtok(NULL, "-");
                sscanf(c_month, "%d", &month);
                date2->set_month(month);

                // Year 2
                c_year = strtok(NULL, "-");
                sscanf(c_year, "%d", &year);
                date2->set_year(year);

                if (*date2 < *date1) {
                    cout << "ERROR COMMAND: " << *date1 << " > " << *date2 << endl;
                    free(c_line);
                    delete date1;
                    delete date2;
                    continue;
                }

                app->popStatusByAge(country, virusName, date1, date2);

            }
            else if ( nWords == 4 ) {

                virusName = strdup(test);
                c_date1 = strtok(NULL, " ");
                c_date2 = strtok(NULL, "");

                if (!consistentDate_str(c_date1) || !consistentDate_str(c_date2)) {
                    cout << "ERROR COMMAND (invalid date format)\n";
                    free(c_line);
                    delete date1;
                    delete date2;
                    free(virusName);
                    continue;
                }

                // Day 1
                c_day = strtok(c_date1, "-");
                sscanf(c_day, "%d", &day);
                date1->set_day(day);

                // Month 1
                c_month = strtok(NULL, "-");
                sscanf(c_month, "%d", &month);
                date1->set_month(month);

                // Year 1
                c_year = strtok(NULL, "-");
                sscanf(c_year, "%d", &year);
                date1->set_year(year);

                // Day 2
                c_day = strtok(c_date2, "-");
                sscanf(c_day, "%d", &day);
                date2->set_day(day);

                // Month 2
                c_month = strtok(NULL, "-");
                sscanf(c_month, "%d", &month);
                date2->set_month(month);

                // Year 2
                c_year = strtok(NULL, "-");
                sscanf(c_year, "%d", &year);
                date2->set_year(year);

                if (*date2 < *date1) {
                    cout << "ERROR COMMAND: " << *date1 << " > " << *date2 << endl;
                    free(c_line);
                    delete date1;
                    delete date2;
                    continue;
                }

                app->popStatusByAge(NULL, virusName, date1, date2);

                free(virusName);
            }
            else {
                cout << "No records for country "<< test << "\n";
            }

            delete date1;
            delete date2;
        }

        if (!strcmp(command, "/insertCitizenRecord")) {
            if (nWords > 9 || nWords < 8) {
                free(c_line);
                cout << "ERROR COMMAND\n";
                cout << "Try: /insertCitizenRecord citizenID firstName lastName country age virusName NO/YES date\n";
                continue;
            }
            string id;
            char* rec = strdup(strtok(NULL, ""));
            id = app->insertCitizenRecord(rec);

            if (id.compare("-1")) {
                cout << "Record "  << id <<" inserted successfully\n";
            }

        }

        if (!strcmp(command, "/vaccinateNow")) {
            if (nWords != 7) {
                free(c_line);
                cout << "ERROR COMMAND\n";
                cout << "Try: /vaccinateNow citizenID firstName lastName country age virusName\n";
                continue;
            }

            char* rec = strdup(strtok(NULL, ""));
            string id = app->vaccinateNow(rec);
            if (id.compare("-1")) {
                cout << "Record "  << id <<" inserted successfully\n";
            }
        }  

        if (!strcmp(command, "/list-nonVaccinated-Persons") ) {
            if (nWords != 2) {
                free(c_line);
                cout << "ERROR COMMAND\n";
                cout << "Try: /list-nonVaccinated-Persons virusName\n";
                continue;
            }
            char* virusName = strtok(NULL, "");
            app->list_nonVaccinated_Persons(virusName);
        }  

        cout << endl;
        free(c_line);
    }



    delete app;
}



