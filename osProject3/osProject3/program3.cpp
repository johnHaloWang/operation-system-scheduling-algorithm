#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>

using namespace std;

/**
 * @brief optimal_algorithm
 * @param input, string -- repersts the input
 * @param numberOfPageFrame, int -- represents the number of page frame
 * @param page_faults, int pass by reference -- recording number of page faults
 * @return vector<string>, string vecotr for display later
 */

vector<string> optimal_algorithm(string input, int numberOfPageFrame, int &page_faults){
    vector<string> ans;
    string frame;
    size_t limit = static_cast<size_t>(numberOfPageFrame);
    for(size_t i= 0; i<limit; i++){
         frame += ' ';
    }
    string formateString = frame;
    //place first number of page frame into ans for later display
    for(size_t i = 0, j = limit-1; i<limit; i++, j--){
        frame[j] = input[i];
        ans.push_back(frame);
        page_faults++;
    }

    //starting looking
    for(size_t i = limit, j = 0; i<input.size(); i++){
        //counting the page frame index, over limit set to zero
        if((++j) == limit){
            j = 0;
        }
        //current item is not in the frame
        if(frame.find(input[i])==string::npos){
           //since it is not in the frame, construct foresee
            string foresee = input.substr(i, input.size()-i);
            int find_least_use = -1 * std::numeric_limits<int>::infinity();
            size_t find=0;
            for(size_t k = 0; k < frame.size(); k++){
                //it was never use, since it can't find in the forsee
                if(foresee.find_first_of(frame[k])==string::npos){
                    find_least_use = static_cast<int>(i);
                    find = k;
                    break;
                }
                //find it, try to get the least used -- it means that the index is geater
                else{
                    //find the least used item
                    int temp = static_cast<int>(foresee.find_first_of(frame[k]));
                    if(temp>find_least_use){
                        find_least_use = temp;
                        find = k;
                    }
                }
            }
            //update the result in the frame
            frame[find] = input[i];
            //place the frame into the string vector for later display
            ans.push_back(frame);
            page_faults++;
        }else{
            ans.push_back(formateString);
        }
    }
    return ans;
}

/**
 * @brief first_in_first_out_algorithm
 * @param input, string -- repersts the input
 * @param numberOfPageFrame, int -- represents the number of page frame
 * @param page_faults, int pass by reference -- recording number of page faults
 * @return vector<string>, string vecotr for display later
 */
vector<string> first_in_first_out_algorithm(string input, int numberOfPageFrame, int &page_faults){
    vector<string> ans;
    string frame;
    size_t limit = static_cast<size_t>(numberOfPageFrame);

    queue<char> priorty;
    for(size_t i= 0; i<limit; i++){
         frame += ' ';
    }
    string formateString = frame;
    //place first number of page frame into ans for later display
    for(size_t i = 0, j = limit-1; i<limit; i++, j--){
        frame[j] = input[i];
        priorty.push(input[i]);
        ans.push_back(frame);
        page_faults++;
    }

    ///starting looking
    for(size_t i = limit; i<input.size(); i++){
        //current item is not in the frame
        if(frame.find(input[i])==string::npos){
            frame[frame.find(priorty.front())]=input[i];
            priorty.pop();
            priorty.push(input[i]);
            //place the frame into the string vector for later display
            ans.push_back(frame);
            page_faults++;
        }
        //ans.push_back(frame);
        else{
            ans.push_back(formateString);
        }

    }
    return ans;
}

/**
 * @brief least_eecently_used_algorithm
 * @param input, string -- repersts the input
 * @param numberOfPageFrame, int -- represents the number of page frame
 * @param page_faults, int pass by reference -- recording number of page faults
 * @return vector<string>, string vecotr for display later
 */
vector<string> least_recently_used_algorithm(string input, int numberOfPageFrame, int &page_faults){
    vector<string> ans;
    string frame;
    size_t limit = static_cast<size_t>(numberOfPageFrame);

    string priorty = "";
    for(size_t i= 0; i<limit; i++){
         frame += ' ';
    }
    string formateString = frame;
    //place first number of page frame into ans for later display
    for(size_t i = 0, j = limit-1; i<limit; i++, j--){
        frame[j] = input[i];
        //priorty.push(input[i]);
        priorty+=input[i];
        ans.push_back(frame);
        page_faults++;
    }

    ///starting looking
    for(size_t i = limit; i<input.size(); i++){
        //current item is not in the frame
        if(frame.find(input[i])==string::npos){
            frame[frame.find(priorty.front())]=input[i];
            priorty.erase(0, 1);
            priorty+=input[i];
            //place the frame into the string vector for later display
            ans.push_back(frame);
            page_faults++;
        }
        //ans.push_back(frame);
        else{
            priorty.erase(priorty.find(input[i]), 1);
            priorty+=input[i];
            ans.push_back(formateString);
        }

    }
    return ans;
}




/**
 * @brief display -- formate the vector into better display
 * @param input, vecotr<string>
 */

void display(vector<string> input){
    vector<string> ans;
    ans.assign(input[0].size(), "");
    for(size_t i=0; i<input.size(); i++){
        for(size_t j = 0; j<input[i].size();j++){
            ans[j]+=input[i][j];
        }
    }
    int limit = static_cast<int>(ans.size())-1;
    for(int i = limit; i>-1; i--){
        cout<<"{"<<ans[static_cast<size_t>(i)]<<"}"<<endl;
    }
}

/**
 * @brief optimal_algorithm_test
 * @param input
 * @param numberOfPageFrame
 */
void optimal_algorithm_test(string input = "70120304230321201701", int numberOfPageFrame = 3){
    int page_faults = 0;

    vector<string> ans = optimal_algorithm(input, numberOfPageFrame, page_faults);
    cout<<"optimal_algorithm"<<endl;
    cout<<"{"<<input<<"}"<<endl;
    display(ans);
    cout<<"page faults: "<<page_faults<<endl;
}


/**
 * @brief first_in_first_out_algorithm_test
 * @param input
 * @param numberOfPageFrame
 */
void first_in_first_out_algorithm_test(string input = "70120304230321201701", int numberOfPageFrame = 3){
    int page_faults = 0;
    cout<<"first_in_first_out_algorithm"<<endl;
    vector<string> ans = first_in_first_out_algorithm(input, numberOfPageFrame, page_faults);
    cout<<"{"<<input<<"}"<<endl;
    display(ans);
    cout<<"page faults: "<<page_faults<<endl;
}

/**
 * @brief least_recently_used_algorithm_test
 * @param input
 * @param numberOfPageFrame
 */
void least_recently_used_algorithm_test(string input = "70120304230321201701", int numberOfPageFrame = 3){
    int page_faults = 0;

    vector<string> ans = least_recently_used_algorithm(input, numberOfPageFrame, page_faults);
    //cout<<"least_recently_used_algorithm"<<endl;
    //cout<<"{"<<input<<"}"<<endl;
    //display(ans);
    //cout<<"page faults: "<<page_faults<<endl;
}

/**
 * @brief createTestCase
 * @param pageFrameSize
 * @param length
 * @param page
 * @return
 */
string createTestCase(int pageFrameSize, size_t length=30, int page = 7){
    string ans="";
    unordered_set<int> set;
    while(static_cast<int>(set.size()) != pageFrameSize){
        int guess = rand() % page;
        if(set.count(guess)==1)
                    continue;
         else{
            ans+=to_string(guess);
            set.insert(guess);
         }
    }
    while(ans.length() != length){
        int guess = rand() % page;
            ans+=to_string(guess);
    }
    return ans;
}

vector<string> createListOfTestCase(int pageFrameSize, size_t numberOfTestCase = 50){
    vector<string> ans;
    unordered_set<string> set;
    while(ans.size() != numberOfTestCase){
        string guess = createTestCase(pageFrameSize);
        if(set.count(guess)==1)
            continue;
        else{
            set.insert(guess);
            ans.push_back(guess);
        }
    }
    return ans;
}

/**
 * @brief writeFile
 * @param list
 * @param fileName
 * @param pageFrameSize
 */
void writeFile(vector<string> list, string fileName, int pageFrameSize){
    ofstream myfile (fileName);
      if (myfile.is_open())
      {
          myfile<<"NumberOfPageFrame value: \n";
          myfile<<to_string(pageFrameSize) + '\n';
          myfile<<"Reference String: \n";

          for(size_t i = 0; i<list.size(); i++){
             string item = list[i];
              myfile <<item+ "\n";
          }
          myfile.close();
      }
      else cout << "Unable to open file";
}

/**
 * @brief readFile
 * @param fileName
 * @param pageFrameSize
 * @return
 */
vector<string> readFile(string fileName, int &pageFrameSize){
    vector<string> returnList;
    string line;
    ifstream myfile(fileName);
    string name;
    int counter = 0;
    if(myfile.is_open()){
        while(getline(myfile, line)){
            if(counter>2){
                returnList.push_back(line);
            }else if(counter==1){
                stringstream geek(line);
                geek>>pageFrameSize;
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

/**
 * @brief testCaseWith3_4_5_6
 */
void testCaseWith3_4_5_6(){
    for(size_t pageFrameSize=3; pageFrameSize<7;pageFrameSize++){
       string input = createTestCase(static_cast<int>(pageFrameSize));
       cout<<"Teast Cas of page frame: "<<pageFrameSize<<endl;
       cout<<"Input: "<<input<<endl;
       first_in_first_out_algorithm_test(input, pageFrameSize);
       least_recently_used_algorithm_test(input, pageFrameSize);
       optimal_algorithm_test(input, pageFrameSize);
    }
}

/**
 * @brief write_test -- loop from 3 to 6 and generate test case and write to file;
 */
void write_test(){
    int index = 1;
    for(size_t pageFrameSize=3;pageFrameSize<7;pageFrameSize++){
            int size = static_cast<int>(pageFrameSize);
            string fileName = "testCase" + to_string(index) + ".txt";
            writeFile(createListOfTestCase(size), fileName, size);
        index++;
    }
}
/**
 * @brief conductTrail
 */
void conductTrail(){
    int index = 1;
    for(size_t i=0;i<4;i++){

        int pageFrameSize;
        int page_faults;
        string fileName = "testCase" + to_string(index) + ".txt";
        cout<<"testing: "<<fileName<<endl;
        vector<string> list = readFile(fileName, pageFrameSize);
        int sum_page_falut_FIFO = 0;
        int sum_page_fault_LRU = 0;
        int sum_page_fault_OP = 0;

        cout<<"size: "<<pageFrameSize<<endl;
        for(size_t i = 0; i<list.size(); i++){
            first_in_first_out_algorithm(list[i], pageFrameSize, page_faults=0);
            sum_page_falut_FIFO += page_faults;
            page_faults = 0;
            least_recently_used_algorithm(list[i], pageFrameSize, page_faults=0);
            sum_page_fault_LRU += page_faults;
            optimal_algorithm(list[i], pageFrameSize, page_faults=0);
            sum_page_fault_OP += page_faults;
        }

        cout<<list.size()<<", "<<static_cast<double>(sum_page_falut_FIFO)/static_cast<double>(list.size())<<endl;
        cout<<list.size()<<", "<<static_cast<double>(sum_page_fault_LRU)/static_cast<double>(list.size())<<endl;
        cout<<list.size()<<", "<<static_cast<double>(sum_page_fault_OP)/static_cast<double>(list.size())<<endl;

        index++;
    }

}


int main()
{
    srand (time(NULL));
    least_recently_used_algorithm_test();
    return 0;
}
