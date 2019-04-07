#ifndef DRIVER1_H
#define DRIVER1_H
#include <algorithm>
#include <job.h>
#include <schedule.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <utility.h>
#include <algorthm.h>

void driver1(int number_of_jobs, int trails){
    vector<vector<Job>> jobMaster;
    double awsFCFS = 0.0;
    double awsSFJ = 0.0;
    double awsRR2 = 0.0;
    double awsRR5 = 0.0;

    for(int i = 0; i<trails; i++){
       vector<Job> temp = createTestCase(number_of_jobs, 101);
       jobMaster.push_back(temp);
    }
    for(int i = 0; i<trails; i++){
        scheduleAlg alg(jobMaster[static_cast<size_t>(i)]);
        Schedule temp = alg.FirstComeFirstServe(jobMaster[static_cast<size_t>(i)]);
        awsFCFS+=temp.average_turnaround_time;
    }
    cout<<"FCSF: "<<awsFCFS/static_cast<double>(trails)<<endl;
    for(int i = 0; i<trails; i++){
        scheduleAlg alg(jobMaster[static_cast<size_t>(i)]);
        Schedule temp = alg.SJF(jobMaster[static_cast<size_t>(i)]);
        awsSFJ+=temp.average_turnaround_time;
    }
    cout<<"SJF: "<<awsSFJ/static_cast<double>(trails)<<endl;
    for(int i = 0; i<trails; i++){scheduleAlg alg(jobMaster[static_cast<size_t>(i)]);
        Schedule temp = alg. RR(jobMaster[static_cast<size_t>(i)], 2);
        awsRR2+=temp.average_turnaround_time;
    }
    cout<<"RR2: "<<awsRR2/static_cast<double>(trails)<<endl;
    for(int i = 0; i<trails; i++){
        scheduleAlg alg(jobMaster[static_cast<size_t>(i)]);
        Schedule temp = alg.RR(jobMaster[static_cast<size_t>(i)], 5);
        awsRR5+=temp.average_turnaround_time;
    }
    cout<<"RR5: "<<awsRR5/static_cast<double>(trails)<<endl;
}

void driver2(int jobNumbers){

    vector<Job> jobMaster = createTestCase(jobNumbers, 101);
    for(auto item: jobMaster){
        cout<<item.name<<", "<<item.length<<endl;
    }
    cout<<"FCSF"<<endl;
    scheduleAlg alg(jobMaster);
    Schedule fcfs = alg.FirstComeFirstServe(jobMaster);
    fcfs.printScheduleTable();

    cout<<"SFJ"<<endl;
    Schedule sfj = alg.SJF(jobMaster);
    sfj.printScheduleTable();
    cout<<"RR2"<<endl;
    Schedule rr2 = alg.RR(jobMaster, 2);
    rr2.printScheduleTable();
    cout<<"RR5"<<endl;
    Schedule rr5 = alg.RR(jobMaster, 5);
    rr5.printScheduleTable();
}

#endif // DRIVER1_H
