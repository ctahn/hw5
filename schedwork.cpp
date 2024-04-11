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


bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, vector<int>& shifts, size_t r, size_t c);
bool isValid(const size_t maxShifts, vector<int>& shifts);

bool scheduleHelper(
    const AvailabilityMatrix& avail, 
    const size_t dailyNeed, 
    const size_t maxShifts, 
    DailySchedule& sched, 
    vector<int>& shifts,
    size_t r, size_t c)
{
  
  if(r == avail.size()){
    return isValid(maxShifts, shifts);
  }
    for(size_t j=0; j < avail[0].size(); j++){
      if(avail[r][j] == 1 && find(sched[r].begin(), sched[r].end(), j) == sched[r].end()){
        sched[r][c] = Worker_T(j);
        shifts[j] += 1;
        if(isValid(maxShifts, shifts)){
          if(r < avail.size() && c < dailyNeed-1){

            if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, r, ++c)){
              return true;
            }
            c--;
          }
          else if(r < avail.size() && c == dailyNeed-1){
            if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, ++r, 0)){
              return true;
            }
            r--;
          } 
        }
      
      sched[r][c] = INVALID_ID;
      shifts[j] -= 1;
      }
    }
  return false;
}

bool isValid(const size_t maxShifts, 
    vector<int>& shifts)
{
  
  if(find(shifts.begin(), shifts.end(), int(maxShifts+1)) != shifts.end()){
    return false;
  }

  return true;
}




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
    int numWorkers = avail.size();
    sched.clear();
    sched.resize(avail.size());
    for(size_t i=0; i < avail.size(); i++){
      sched[i].resize(dailyNeed);
      for(size_t j=0; j < sched[i].size(); j++){
        sched[i][j] = INVALID_ID;
      }
    }
    vector<int> shifts(numWorkers,0);
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
    
}

