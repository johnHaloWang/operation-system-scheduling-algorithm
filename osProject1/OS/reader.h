#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>

void readFile(string fileName, vector<Job> &jobList){
      string line = "";
      ifstream myfile (fileName);

      if (myfile.is_open())
      {
        int counter = 0, length = 0;
        string name;

        while ( getline (myfile,line) )
        {
         cout <<"{"<<line<<"}"<<endl;
          if(counter%2==0){
              cout<<"happend first"<<endl;
              name = line;
          }else{
              istringstream buffer(line);
              buffer>>length;

              cout<<"<"<<name<<">"<<":::"<<length<<endl;
              Job temp = Job(name, length, 0);
              //cout<<"check: "<<temp.name<<", "<<temp.length<<endl;
              jobList.push_back(temp);
          }
          counter++;
        }
        myfile.close();
      }

      else cout << "Unable to open file";

      //return 0;
}


#endif // READER_H
