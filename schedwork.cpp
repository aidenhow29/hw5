#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool schedHelp(
    const AvailabilityMatrix& avail,
    size_t dailyNeed, 
    size_t maxShifts, 
    DailySchedule& sched, 
    vector<size_t>& shifts, 
    size_t day,
    size_t slot
){
    if(day == avail.size()){
        return true;
    }
    if(slot == dailyNeed){
        return schedHelp(avail, dailyNeed, maxShifts, sched, shifts, day + 1, 0);
    }

    for(Worker_T w = 0; w < avail[0].size(); ++w){
        if(avail[day][w] && shifts[w] < maxShifts && 
        find(sched[day].begin(), sched[day].end(), w) == sched[day].end()){
            sched[day].push_back(w);
            shifts[w]++;


            if(schedHelp(avail, dailyNeed, maxShifts, sched, shifts, day, slot + 1)){
                return true;
            }

            sched[day].pop_back();
            shifts[w]--;
        
        }
    }
    return false;
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    //add prints to trace / debug
    //keep in mind where you put it, think of it as going down levels of the tree

    sched.assign(avail.size(), vector<Worker_T>());
    vector<size_t> shiftsWorked(avail[0].size(), 0);
    return schedHelp(avail, dailyNeed, maxShifts, sched, shiftsWorked, 0, 0);


}

