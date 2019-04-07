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
#include <algorthm.h>
#include <driver1.h>
using namespace std;



//static vector<Job> jobListTest = {
//      Job("Job101", 6, 0),
//      Job("Job102", 8, 0),
//      Job("Job103", 7, 0),
//      Job("Job104", 3, 0),
//};

//static vector<Job> jobList;


int main(int argc, char *argv[]){

    srand (time(NULL));
    //void driver1(int number_of_jobs, int trails){
    cout<<"10 trials"<<endl;
    driver1(30, 10);
    cout<<"20 trials"<<endl;
    driver1(30, 20);
    cout<<"30 trials"<<endl;
    driver1(30, 30);


    return 0;
}
