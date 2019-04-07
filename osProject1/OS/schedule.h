#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <queue>
#include <Job.h>
#include <iostream>
#include <iomanip>

struct Schedule{
    double average_turnaround_time=0.0;
    queue<Job> result_queue;
    Schedule(double input_average_turnaround_time, queue<Job> input_result_queue):
        average_turnaround_time(input_average_turnaround_time),result_queue(input_result_queue){}
    void printScheduleTable(){
        cout<<"Schedule Table"<<endl;
        queue<Job> result_queue_copy(result_queue);
        int counter = 1, marker = 0;
        cout<<setw(3)<<"Count"<<setw(2)<<" "<<"Job #"<<setw(3)<<" "<<"Start"<<setw(5)<<"End"<<setw(5)<<" "<<setw(5)<<"complete time"<<endl;
        while(!result_queue_copy.empty()){
            Job temp = result_queue_copy.front();
            int now = marker + temp.proccessed;
            cout<<setw(3)<<counter++<<setw(3)<<" "<<temp.name<<" "<<setw(6)
                <<marker<<setw(5)<<now<<setw(5)<<" "<<setw(5)<<((temp.remain==0)?to_string(now):"N/A")<<endl;
            marker = now;
            result_queue_copy.pop();

        }
        cout<<"average turnaround time: "<<average_turnaround_time<<endl;
    }
    void printGanttChart(){
        cout<<"GanttChart"<<endl;
        queue<Job> result_queue_copy(result_queue);
        int counter = 1;
        while(!result_queue_copy.empty()){
            Job temp = result_queue_copy.front();
            cout<<counter++<<": "<<temp.name<<", "<<temp.length<<endl;
            result_queue_copy.pop();
        }
        cout<<"average turnaround time: "<<average_turnaround_time<<endl;
    }
};

#endif // SCHEDULE_H
