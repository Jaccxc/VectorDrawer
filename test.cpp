#include <iostream>
using namespace std;
#include <cmath>
#include <vector>
#include <fstream>

//將文字檔案中得資料讀入vector中，並返回一個vector。
vector<int> *InputData_To_Vector()
{
    vector<int> *p = new vector<int>;
    ifstream infile("/Users/……/inputdata.txt");
    int number;
    while(! infile.eof())
    {
        infile >> number;
        p->push_back(number);
    }
    p->pop_back();  //此處要將最後一個數字彈出，是因為上述迴圈將最後一個數字讀取了兩次
    return p;
}

inline int Num_Square(int n)
{
    return n*n;
}

int Sum_Of_Num_Square(vector<int> *p)
{
    int Sum2 = 0;
    vector<int>::iterator it;
    for(it=p->begin(); it!=p->end(); it++)
    {
        Sum2 += Num_Square(*it);
    }
    return Sum2;
}

//呼叫傳入的vector
int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> *file_to_vector = InputData_To_Vector();
    cout<<"sum2="<<Sum_Of_Num_Square(file_to_vector)<<endl;
    return 0;
}
