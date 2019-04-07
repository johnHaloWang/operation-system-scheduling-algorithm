#ifndef JOB_H
#define JOB_H
#include <string>

using namespace std;

struct Job {
    string name="";
    int length=0;
    int proccessed=0;
    int remain = 0;
    Job(string inputName, int inputLength, int inputProccessed)
        :name(inputName),length(inputLength),proccessed(inputProccessed){
        remain = length;
    }
    bool operator<(Job other) const
    {
        return length < other.length;
    }

};

#endif // JOB_H
