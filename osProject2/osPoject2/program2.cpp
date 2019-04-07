#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;


int const cylinder_number_const = 40;
int starting_point1, starting_point2, starting_point3;

/**
 * @brief The Request struct representing the request for the cylinder number
 *
 *
 */
struct Request {

    string name="";
    int cylinderNumber=0;
    /**
     * @brief Request default constructor
     * @param inputName representing the number of request
     * @param inputCylinderNumber represeting cylinder number
     */
    Request(string inputName, int inputCylinderNumber)
        :name(inputName),cylinderNumber(inputCylinderNumber){
    }
    /**
     * @brief operator <, overload compare operator
     * @param other, the Request other and compare with self
     * @return ture/false
     */
    bool operator<(Request other) const
    {
        return cylinderNumber < other.cylinderNumber;
    }

};



/**
 * @brief readFile: reading the file to get the Request from the file
 * @param fileName, string: the name of the file
 * @return
 */

vector<Request> readFile(string fileName, int &start_cylinder){
    vector<Request> returnList;
    string line;
    ifstream myfile(fileName);
    string name;
    int number;
    int counter = 0;
    bool doThis = false;
    if(myfile.is_open()){
        while(getline(myfile, line)){
            if(line!="Initial Cylinder #" && doThis==false){
                if(counter%2==0)
                    name = line;
                else {
                    stringstream geek(line);
                    geek>>number;
                    returnList.push_back(Request(name, number));
                }
            }
            else if (doThis==true) {
                stringstream geek(line);
                geek>>start_cylinder;
            }
            else{
                doThis = true;
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
 * @brief set_starting_cylinder, return a integer – represent a starting cylinder position.
 * The logic is to use the data structure set and put all requests in a trail into the set;
 * then the function will randomly draw a number between 1 to 40, but this number cannot be inside the set.
 * @param list, vector<Request>
 * @return int, the staring cylinder position
 */
int set_starting_cylinder(vector<Request> list){
    unordered_set<int> set;
    for(auto item: list){
        //cout<<item.name<<endl;
        //cout<<item.cylinderNumber<<endl;
        set.insert(item.cylinderNumber);

    }
    int starting_point=INT_MAX;
    int index = 1;
    do{
        starting_point = rand() % cylinder_number_const + 1;
        //cout<<index<<": "<<starting_point<<endl;
        index++;
    }while(set.count(starting_point)==1);

    //cout<<"starting_pointing: "<<starting_point<<endl;
    return starting_point;
}

/**
 * @brief writeFile: write the Request list to the file.
 * @param list: vector of Request struct
 * @param fileName, string:
 */
void writeFile(vector<Request> list, string fileName){
    ofstream myfile (fileName);
      if (myfile.is_open())
      {
          for(size_t i = 0; i<list.size(); i++){
              Request item = list[i];
              myfile <<item.name+ "\n";
              myfile <<to_string(item.cylinderNumber) + "\n";
          }
          int starting_cylinder = set_starting_cylinder(list);
          myfile<<"Initial Cylinder #\n";
          myfile<<to_string(starting_cylinder) + "\n";
          myfile.close();
      }
      else cout << "Unable to open file";

}

/**
 * @brief first_come_first_serverd
 * @param starting_cylinder, starting cylinder posistion
 * @param requests, a vector contained all the requests
 * @return vector<int>
 */
vector<int> first_come_first_serverd(int starting_cylinder, vector<Request> requests){
    int sum_of_cylinders = 0, temp;
    vector<int> ans;
    for(size_t i = 0; i<requests.size(); i++){
        temp = abs(starting_cylinder - requests[i].cylinderNumber);
        ans.push_back(temp);
        sum_of_cylinders+=temp;
        starting_cylinder=requests[i].cylinderNumber;
    }
    return ans;
}

/**
 * @brief shortest_seek_first
 * @param starting_cylinder, starting cylinder posistion
 * @param requests, a vector contained all the requests
 * @return vector<int>
 */

vector<int> shortest_seek_first(int starting_cylinder, vector<Request> requests){
    int sum_of_cylinders = 0, temp, index, smallest, find=0;
    vector<int> ans;
    while(!requests.empty()){
        smallest = INT_MAX;
        index = 0;

        for(size_t i = 0; i<requests.size(); i++){
            temp = abs(starting_cylinder - requests[i].cylinderNumber);
            if(temp<smallest){
                smallest = temp;
                find = requests[i].cylinderNumber;
                index = static_cast<int>(i);
            }
        }
        starting_cylinder=find;
        requests.erase(requests.begin()+index);
        ans.push_back(smallest);
        sum_of_cylinders+=smallest;
    }
    return ans;
}

/**
 * @brief elevator_moving_upward
 * @param starting_cylinder, starting cylinder posistion
 * @param requests, a vector contained all the requests
 * @return vector<int>
 */

vector<int> elevator_moving_upward(int starting_cylinder, vector<Request> requests){
    int sum_of_cylinders = 0, temp, index=0;
    vector<int> ans;
    //sort based on the request's cylinder number
    sort(requests.begin(), requests.end());
    //find where to elevate
    for(size_t i = 0; i<requests.size(); i++){
        if(starting_cylinder<requests[i].cylinderNumber){
            index = static_cast<int>(i);
            break;
        }
    }
    //loop forward to process the calcuation
    for(size_t i = static_cast<size_t>(index); i<requests.size(); i++){
        temp = abs(starting_cylinder - requests[i].cylinderNumber);
        ans.push_back(temp);
        sum_of_cylinders+=temp;
        starting_cylinder=requests[i].cylinderNumber;
    }
    //loop backward to process the calcuation
    for(int i = index-1; i>=0; i--){
        temp = abs(starting_cylinder - requests[static_cast<size_t>(i)].cylinderNumber);
        ans.push_back(temp);
        sum_of_cylinders+=temp;
        starting_cylinder=requests[static_cast<size_t>(i)].cylinderNumber;
    }
    return ans;
}

/**
 * @brief createTestCase:
 * Random generate number between 1 to 40 (since the setting is to have maximum 40 cylinders on a disk);
 * there will be no repeated numbers and store the requests inside the a vector
 * @param starting_number
 * @param number_of_request, default value is 30 representing maximum 30 request
 * @param cylinder_number, default value is 40 representing maximum of cylinder
 * @return vector<Request>
 */
vector<Request> createTestCase(int starting_number, int number_of_request=30, int cylinder_number=40){
    vector<Request> jobList;
    unordered_set<int> set;
    while(static_cast<int>(set.size()) != number_of_request){
        int guess = rand() % cylinder_number + 1;
        if(set.count(guess)==1)
            continue;
        else{
            set.insert(guess);
            string name = "Request" + to_string(starting_number++);
            jobList.push_back(Request(name, guess));
        }
    }
    return jobList;
}

/**
 * @brief randomGenerateCase_Test
 * @param number_of_case, int: generate number of case for testing
 * @return starting_point, int;
 */
int randomGenerateCase_Test(int number_of_case, string fileName, int case_number){

   vector<Request> list = createTestCase(case_number, number_of_case);
   unordered_set<int> set;
   for(auto item: list){
       set.insert(item.cylinderNumber);
   }
   int starting_point=INT_MAX;
   int index = 1;
   do{
       starting_point = rand() % cylinder_number_const + 1;
       index++;
   }while(set.count(starting_point)==1);
   writeFile(list, fileName);
   return starting_point;
}

/**
 * @brief driveTest_elevator_moving_upward
 *
 */
void driveTest_elevator_moving_upward(){
    cout<<"Elevator algorithm, initially moving upward (E-U)"<<endl;
    vector<Request> case1 = readFile("testCase1.txt", starting_point1);
    cout<<"starting cylinder: "<<starting_point1<<endl;
    vector<Request> ans = elevator_moving_upward(starting_point1, case1);
    cout<<"Head movement chart: "<<endl;
    for(auto i: ans){
        cout<<i.cylinderNumber<<"->";
    }
    cout<<endl;
    cout<<"Total cylinder move: "<<endl;
    int sum_cylinders = 0;
    for(size_t j=1; j<ans.size(); j++){
        Request i = ans[j];
        cout<<i.length<<"+";
        sum_cylinders+=i.length;
    }
    cout<<"="<<sum_cylinders<<endl;
    cout<<endl<<endl<<endl;
}

/**
 * @brief driveTest_first_come_first_serverd
 *
 */

void driveTest_first_come_first_serverd(){

    cout<<"first come first served: "<<endl;
    vector<Request> case1 = readFile("testCase1.txt", starting_point1);
    cout<<"starting cylinder: "<<starting_point1<<endl;
    vector<Request> ans = first_come_first_serverd(starting_point1, case1);

    cout<<"Head movement chart: "<<endl;
    for(auto i: ans){
        cout<<i.cylinderNumber<<"->";
    }
    cout<<endl;
    cout<<"Total cylinder move: "<<endl;
    int sum_cylinders = 0;
    for(size_t j=1; j<ans.size(); j++){
        Request i = ans[j];
        cout<<i.length<<"+";
        sum_cylinders+=i.length;
    }
    cout<<"="<<sum_cylinders<<endl;
    cout<<endl<<endl<<endl;
}

/**
 * @brief driveTest_shortest_seek_first
 *
 */

void driveTest_shortest_seek_first(){
    cout<<"shortest seek first: "<<endl;
    vector<Request> case1 = readFile("testCase1.txt", starting_point1);
    cout<<"starting cylinder: "<<starting_point1<<endl;
    vector<Request> ans = shortest_seek_first(starting_point1, case1);
    cout<<"Head movement chart: "<<endl;
    for(auto i: ans){
        cout<<i.cylinderNumber<<"->";
    }
    cout<<endl;
    cout<<"Total cylinder move: "<<endl;
    int sum_cylinders = 0;
    for(size_t j=1; j<ans.size(); j++){
        Request i = ans[j];
        cout<<i.length<<"+";
        sum_cylinders+=i.length;
    }
    cout<<"="<<sum_cylinders<<endl;
    cout<<endl<<endl<<endl;
}




/**
 * @brief genrateCase_driver
 */
void genrateCase_driver(){
    starting_point1 = randomGenerateCase_Test(5, "testCase1.txt", 101);
    starting_point2 = randomGenerateCase_Test(10, "testCase2.txt", 201);
    starting_point3 = randomGenerateCase_Test(15, "testCase3.txt", 301);
}

/**
 * @brief three_test_case_driver_for_table
 */
void three_test_case_driver_for_table(){
    vector<Request> case1 = readFile("testCase1.txt", starting_point1);
    vector<Request> case2 = readFile("testCase2.txt", starting_point2);
    vector<Request> case3 = readFile("testCase3.txt", starting_point3);

    cout<<"1: "<<starting_point1<<endl;
    cout<<"2: "<<starting_point2<<endl;
    cout<<"3 "<<starting_point3<<endl;


    for(auto item: case1){
        cout<<item.name<<endl;
        cout<<item.cylinderNumber<<endl;
    }
    cout<<endl<<endl;
    for(auto item: case2){
        cout<<item.name<<endl;
        cout<<item.cylinderNumber<<endl;
    }
    cout<<endl<<endl;
    for(auto item: case3){
        cout<<item.name<<endl;
        cout<<item.cylinderNumber<<endl;
    }
    cout<<endl<<endl;
    cout<<"Result of FCFS"<<endl;
    vector<int> result1 = first_come_first_serverd(starting_point1, case1);
    int sum_cylinders1 = 0;
    for(auto i: result1){
        cout<<i<<"+";
        sum_cylinders1+=i;
    }
    cout<<"="<<sum_cylinders1<<endl;
    cout<<"Result of shortest_seek_first"<<endl;
    vector<int> result2 = shortest_seek_first(starting_point1, case1);
    int sum_cylinders2 = 0;
    for(auto i: result2){
        cout<<i<<"+";
        sum_cylinders2+=i;
    }
    cout<<"="<<sum_cylinders2<<endl;
    cout<<"Result of M-U"<<endl;
    vector<int> result3 =elevator_moving_upward(starting_point1, case1);
    int sum_cylinders3 = 0;
    for(auto i: result3){
        cout<<i<<"+";
        sum_cylinders3+=i;
    }
    cout<<"="<<sum_cylinders3<<endl;

    cout<<"Result of FCFS"<<endl;
    vector<int> result4 = first_come_first_serverd(starting_point2, case2);
    int sum_cylinders4 = 0;
    for(auto i: result4){
        cout<<i<<"+";
        sum_cylinders4+=i;
    }
    cout<<"="<<sum_cylinders4<<endl;
    cout<<"Result of shortest_seek_first"<<endl;
    vector<int> result5 = shortest_seek_first(starting_point2, case2);
    int sum_cylinders5 = 0;
    for(auto i: result5){
        cout<<i<<"+";
        sum_cylinders5+=i;
    }
    cout<<"="<<sum_cylinders5<<endl;
    cout<<"Result of M-U"<<endl;
    vector<int> result6 =elevator_moving_upward(starting_point2, case2);
    int sum_cylinders6 = 0;
    for(auto i: result6){
        cout<<i<<"+";
        sum_cylinders6+=i;
    }
    cout<<"="<<sum_cylinders6<<endl;
    cout<<"Result of FCFS"<<endl;
    vector<int> result7 = first_come_first_serverd(starting_point3, case3);
    int sum_cylinders7 = 0;
    for(auto i: result7){
        cout<<i<<"+";
        sum_cylinders7+=i;
    }
    cout<<"="<<sum_cylinders7<<endl;
    cout<<"Result of shortest_seek_first"<<endl;
    vector<int> result8 = shortest_seek_first(starting_point3, case3);
    int sum_cylinders8 = 0;
    for(auto i: result8){
        cout<<i<<"+";
        sum_cylinders8+=i;
    }
    cout<<"="<<sum_cylinders8<<endl;
    cout<<"Result of M-U"<<endl;
    vector<int> result9 =elevator_moving_upward(starting_point3, case3);
    int sum_cylinders9 = 0;
    for(auto i: result9){
        cout<<i<<"+";
        sum_cylinders9+=i;
    }
    cout<<"="<<sum_cylinders9<<endl;
}

/**
 * @brief case_trail_driver
 * @param number_of_case, number request size
 * @param trail, number of trail conduct -- default 10 trials
 */
void case_trail_driver(int number_of_case, int trail=10){
    vector<vector<Request>> list_of_request;
    vector<int> starting_point_vector;

    for(int i =0; i<trail; i++){
        vector<Request> temp = createTestCase(101, number_of_case);
        list_of_request.push_back(temp);
        int start_point =  set_starting_cylinder(temp);
        starting_point_vector.push_back(start_point);
    }

    double sum_of_first_come_first_served=0;
    for(int i =0; i<trail; i++){
        vector<int> temp = first_come_first_serverd(starting_point_vector[i], list_of_request[i]);
        int sum_cylinders = 0;
        for(auto i: temp){
            sum_cylinders+=i;
        }
        sum_of_first_come_first_served+=sum_cylinders;
    }
    cout<<"Result of FCFS: "<<static_cast<double>(sum_of_first_come_first_served)/static_cast<double>(trail)<<endl;

    double sum_of_shortest_seek_first=0;
    for(int i =0; i<trail; i++){
        vector<int> temp = shortest_seek_first(starting_point_vector[i], list_of_request[i]);
        int sum_cylinders = 0;
        for(auto i: temp){
            sum_cylinders+=i;
        }
        sum_of_shortest_seek_first+=sum_cylinders;
    }
    cout<<"Result of shortest_seek_first: "<<static_cast<double>(sum_of_shortest_seek_first)/static_cast<double>(trail)<<endl;

    double sum_of_elevator_moving_upward=0;
    for(int i =0; i<trail; i++){
        vector<int> temp = elevator_moving_upward(starting_point_vector[i], list_of_request[i]);
        int sum_cylinders = 0;
        for(auto i: temp){
            sum_cylinders+=i;
        }
        sum_of_elevator_moving_upward+=sum_cylinders;
    }
    cout<<"Result of elevator_moving_upward: "<<static_cast<double>(sum_of_elevator_moving_upward)/static_cast<double>(trail)<<endl;
}

/**
 * @brief part3_driver
 */
void part3_driver(){
    for(int i = 5; i<=30; i+=5){
        cout<<"Number of request: "<<i<<endl;
        case_trail_driver(i);
    }
}

int main()
{
    srand (time(NULL));
    /**
     * @brief driveTest_first_come_first_serverd
     */

    driveTest_first_come_first_serverd();



    return 0;
}
