#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <string.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>


using namespace std;

bool DEBUG = 0;

boost::posix_time::time_duration TimeRoutine(string name, boost::function < vector<int> (vector<int>)> fun, 
                   vector<int>);
vector<int> SelectionSort(vector<int> A);
vector<int> BubbleSort(vector<int> A);
vector<int> BubbleSortFlagged(vector<int> A);
void Swap(vector<int>& A, int i, int j);
bool ErrorCheck(vector<int> sort);
void Test(string name, boost::function < vector<int> (vector<int>)> fun);
void Summary(string name, boost::posix_time::time_duration time, int n);
vector<int> FillArray(int n);

//************************************************************************************************/

int main() {

    Test("SelectionSort", SelectionSort);
    Test("BubbleSort", BubbleSort);
    Test("BubbleSortFlagged", BubbleSortFlagged);

    return 0;
}

//************************************************************************************************

vector<int> SelectionSort(vector<int> A) {
  int length= A.size();
  int min= 0;
  
  for (int i=0; i < (length-1); i++)
  {
    min= i;
    for (int j= i+1; j < (length); j++)
    {
      if(A[j] < A[min])
	min= j;
    }
    Swap(A, i, min);
  }
    
   return A;
}

//************************************************************************************************
vector<int> BubbleSort(vector<int> A) {
  int length= A.size();
  
  for(int i= 0; i < (length-1); i++)
  {
    for(int j= 0; j < (length-1-i); j++)
    {
      if(A[j+1] < A[j])
      {
	Swap(A, j, (j+1));
      }
    }
  }
   /*cout << endl;
      for( int k= 0; k < length; k++)
    {
      cout << A[k] << endl;
    }*/
    
    return A;
}

//************************************************************************************************
vector<int> BubbleSortFlagged(vector<int> A) {
  bool flag= true;
  int length= A.size();
  int c= 0;
  for(int i= 0; i < (length-1) && flag == true; i++)
  {
    flag= false;
    for(int j= 0; j < (length-1-i); j++)
    {
      if(A[j+1] < A[j])
      {
	Swap(A, j, (j+1));
	flag= true;
      }
    }
  }
    /*cout << endl;
      for( int k= 0; k < length; k++)
    {
      cout << A[k] << endl;
    }*/
    
  return A;
}

//************************************************************************************************
void Swap(vector<int>& A, int i, int j){
  int temp= 0;
  temp= A[i];
  A[i]= A[j];
  A[j]= temp;
}

//************************************************************************************************

boost::posix_time::time_duration TimeRoutine(string name, boost::function < vector<int> (vector<int>)> fun, 
                   vector<int> A){

    
    boost::posix_time::ptime startTime, endTime;
    boost::posix_time::time_duration totalTime;
    
    startTime = boost::posix_time::microsec_clock::local_time();
    endTime = boost::posix_time::microsec_clock::local_time();

    startTime = boost::posix_time::microsec_clock::local_time();
    vector<int> sort= fun(A);
    endTime = boost::posix_time::microsec_clock::local_time();
    cout <<"\t" << name << ": ";
    totalTime = endTime-startTime;

    cout << "\tTime: " << totalTime;

    cout << endl;
    if (!ErrorCheck(sort) ){
        cout << endl;
        cout << "ERROR ERROR ERROR ERROR ERROR ERROR " << endl;
        cout << endl << endl << endl;
    }
    return totalTime;
}

//************************************************************************************************
bool ErrorCheck(vector<int> sort){
   int length= sort.size();
   
   for(int i=0; i < (length-1); i++){
      if (sort[i] > sort[i+1])
	return false;
   }
   
   return true;
}


//************************************************************************************************

void Test(string name, boost::function < vector<int> (vector<int>)> fun){ 
  boost::posix_time::time_duration stime;
  boost::posix_time::time_duration btime;
  boost::posix_time::time_duration bftime;

  int n= 10;
  for(int i= 0; i < 10; i++)
  { 
     for ( int j= 0; j < 10; j++)
     {
       stime += TimeRoutine(name, fun, FillArray(n));
     }
     Summary(name, stime, n);
     n*= 2;
  }
}

//**********************************************************************************
void Summary(string name, boost::posix_time::time_duration time, int n){
    boost::posix_time::time_duration avg= time/n;
    cout << endl <<  "*********************************************************" << endl;
    cout << "        Summary for " << name << " with array size "<< n << endl;
    cout << "                                               " << endl;
    cout << "        Total Time:   " << time << endl <<endl;
    cout << "        Average Time: " << avg << endl << endl;
    cout << "*********************************************************" << endl;
}

//**********************************************************************************
vector<int> FillArray(int n){
   boost::mt19937 rng;
   boost::uniform_int<> dist(2,1<<20);
   boost::variate_generator<boost::mt19937&, boost::uniform_int<> >
   bigDie(rng,dist);

   rng.seed(static_cast<unsigned int>(std::time(0)));
  
   vector<int> a;
   
   for (int i= 0; i < n; i++)
     a.push_back(bigDie());
   
   return a;
}
    
    
    