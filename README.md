# SysPro1-VaccineMonitor

<p><h3>Compile</h3></p>
make

<h3><p>Usage</h3></p>
./vaccineMonitor -c citizenRecordsFile –b bloomSize

 
<h3><p>Commands</h3></p>

<p>/vaccineStatusBloom citizenID virusName <br/>
print No/Yes</p>

/vaccineStatus citizenID  </br>
print all vaccinations for the citizen with citizenID

/populationStatus country virusName date1 date2 </br>
print the percentages  of citizens who have been vaccinated on [date1, date2] for the country
Ι distinguish the following age groups for every country: </br>
20-40 years old </br>
40-60 years old </br>
60+ years old </br>


/populationStatus virusName date1 date2 </br>
print the percentages of citizens who have been vaccinated on [date1,date2] for every country in our dataset (in the same format as the previous command)

/insertCitizenRecord citizenID firstName lastName country age virusName YES/NO [date]
insert a record. 
note: if the citizen has been vaccinated, you must insert the date of vaccination.

/vaccinateNow citizenID firstName lastName country age virusName
insert a vaccine on the current date

/list-nonVaccinated-Persons virusName
print out all citizens who have not been vaccinated against the virus

/exit
Exit from application </br>
free memory
