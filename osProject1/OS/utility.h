#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <algorithm>
#include <job.h>
#include <unordered_set>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

vector<Job> createTestCase(int number_of_case, int starting_number){
    vector<Job> jobList;
    unordered_set<int> set;
    while(static_cast<int>(set.size()) != number_of_case){

        int guess = rand() % (number_of_case) + 20;
        if(set.count(guess)==1)
            continue;
        else{
            set.insert(guess);
            string name = "Job" + to_string(starting_number++);
            jobList.push_back(Job(name, guess, 0));
        }
    }
    return jobList;
}

vector<Job> readFile(string fileName){
    vector<Job> returnList;
    string line;
    ifstream myfile(fileName);
    string name;
    int number;
    int counter = 0;
    if(myfile.is_open()){
        while(getline(myfile, line)){
            if(counter%2==0)
                name = line;
            else {
                stringstream geek(line);
                geek>>number;
                returnList.push_back(Job(name, number, 0));
            }
            counter++;
        }

        myfile.close();
    }
    else {
        cout<<"Unable to open file"<<endl;
    }
    return returnList;
}

#endif // UTILITY_H
