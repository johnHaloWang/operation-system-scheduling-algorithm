#ifndef ALGORTHM_H
#define ALGORTHM_H
#include <iostream>
#include <queue>
#include <vector>

#include <algorithm>
#include <job.h>
#include <schedule.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <utility.h>


using namespace std;
struct scheduleAlg{
    vector<Job> jobList;
    scheduleAlg(vector<Job> jobListInput):jobList(jobListInput){}
    Schedule FirstComeFirstServe(vector<Job> jobList){
        int currentMarker = 0;
        queue<Job> result_queue;
        double ave = 0.0;
        for(auto item: jobList){
            item.proccessed = item.length;
            item.length += currentMarker;
            currentMarker = item.length;
            item.remain = 0;
            ave+=static_cast<double>(currentMarker);
            result_queue.push(item);
        }

        Schedule s = Schedule(ave/static_cast<double>(jobList.size()), result_queue);
        return s;
    }

    //b.	Shortest-Job-First (SJF)
    Schedule SJF(vector<Job> jobList){
        int currentMarker = 0;

        queue<Job> result_queue;
        sort(jobList.begin(), jobList.end());
        double ave = 0.0;
        for(auto item: jobList){
            item.proccessed = item.length;
            item.length += currentMarker;
            currentMarker = item.length;
            item.remain = 0;
            ave+=static_cast<double>(currentMarker);
            result_queue.push(item);
        }
        Schedule s = Schedule(ave/static_cast<double>(jobList.size()), result_queue);
        return s;
    }

    //c.	Round-Robin with Time Slice = 2 (RR-2)
    //d.	Round-Robin with Time Slice = 5 (PR-5)
    Schedule RR(vector<Job> jobList, int slice){
        int currentMarker = 0;
        queue<Job> result_queue;
        double ave = 0.0;
        bool cont = true;
        int zeroCase = 0;
        do{
            for(size_t i = 0; i<jobList.size(); i++){
                Job item = jobList[i];
                int proccessed = 0;
                if(item.length!=0){
                    if(item.length>slice){
                        currentMarker+=slice;
                        item.length-=slice;
                        proccessed = slice;
                        item.remain -= slice;
                    }else{
                        proccessed = item.length;
                        currentMarker+=item.length;
                        item.remain-=item.length;
                        ave+=static_cast<double>(currentMarker);
                        item.length = 0;
                        zeroCase++;
                    }

                    jobList[i] = item;
                    Job temp = Job(item.name, currentMarker,proccessed);
                    temp.remain = item.remain;
                    result_queue.push(temp);
                }
            }
            if(zeroCase == static_cast<int>(jobList.size())) cont = false;
        }while(cont);
        Schedule s = Schedule(ave/static_cast<int>(jobList.size()), result_queue);
        return s;
    }

};

#endif // ALGORTHM_H
