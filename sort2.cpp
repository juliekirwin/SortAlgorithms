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

boost::posix_time::time_duration TimeRoutine(string name, boost::function < void (vector<int>&)> fun, 
                   vector<int>);
boost::posix_time::time_duration TimeRoutine2(string name, boost::function < void (vector<int>&, int, int)> fun, 
                   vector<int> A);
void Swap(vector<int>& A, int i, int j);
bool ErrorCheck(vector<int> sort);
void Test(string name, boost::function < void (vector<int>&)> fun);
void Test2(string name, boost::function < void (vector<int>&, int, int)> fun);
void Summary(string name, boost::posix_time::time_duration time, int n);
void SummaryFile(string name, boost::posix_time::time_duration time, int n);
vector<int> FillArray(int n);
void Quicksort(vector<int>&A, int left, int right);
int Partition(vector<int>&A, int left, int right);
void MergeSort(vector<int>&A);
void MergeSortI(vector<int>&A);
void Merge(vector<int>&B, vector<int>&C, vector<int>&A);
void Copy(vector<int>& partial,vector<int>& master, int p, int m);
void Print(vector<int> A);
void InsertionSort(vector<int>&A);

//************************************************************************************************/

int main() {
    Test2("Quicksort", Quicksort);
    Test("MergeSort", MergeSort);
    Test("MergeSortI", MergeSortI);
    Test("InsertionSort", InsertionSort);

    return 0;
}

//************************************************************************************************
void Quicksort(vector<int>&A, int left, int right){
  int p; 
  if (left < right){
     p = Partition(A, left, right);
     Quicksort(A, left, p);
     Quicksort(A, (p+1), right);
  }
 
}


//************************************************************************************************
int Partition(vector<int>&A, int left, int right){
  int pivot= A[left];
  int split= left;
  
  for (int i= left+1; i < right; i++){
     if (A[i] < pivot){
        split+= 1;
	Swap(A, split, i);
     }
  }
  Swap(A, left, split);
  return split;
}

//************************************************************************************************
void MergeSort(vector<int>&A){
  vector<int> B;
  vector<int> C;
  if (A.size()> 1){
    for(int i = 0; i < (A.size()/2); i++){
       B.push_back(A[i]);  
    }
    for(int j = ((A.size()/2)); j < A.size(); j++){
       C.push_back(A[j]);  
    }
    MergeSort(B);
    MergeSort(C);
    Merge(B,C,A);
  }
}

//************************************************************************************************
void MergeSortI(vector<int>&A){
  vector<int> B;
  vector<int> C;
  if (A.size()> 500){
    for(int i = 0; i < (A.size()/2); i++){
       B.push_back(A[i]);  
    }
    for(int j = ((A.size()/2)); j < A.size(); j++){
       C.push_back(A[j]);  
    }
    MergeSort(B);
    MergeSort(C);
    Merge(B,C,A);
  }else{
    InsertionSort(A); 
  }
}

//************************************************************************************************
void Merge(vector<int>&B, vector<int>&C, vector<int>&A){
  int i,j,k;
  i=j=k=0;
  
  while(i < B.size() && j < C.size()){
    if(B[i] <= C[j]){
      A[k] = B[i];
      i++;
    }
    else{
      A[k]= C[j];
      j++;
    }
    k++;
  }
  if (i == B.size())
      Copy(C,A,j,k);
  else
      Copy(B,A,i,k);
}

//************************************************************************************************
void InsertionSort(vector<int>&A){
  int temp= A.size();
  for(int i=0; i < temp; i++){
    int v= A[i];
    int j= i-1;
    while((j >= 0) && (A[j] > v)){
      A[j+1]= A[j];
      j--;  
    }
    A[j+1]= v;
  }
}

//************************************************************************************************
void Copy(vector<int>& partial,vector<int>& master, int p, int m){
  int temp= p;
  for (int i =0; i < partial.size()-temp; i++){
     master[m+i]= partial[p];
     p++;
  }
}

//************************************************************************************************
void Swap(vector<int>& A, int i, int j){
  int temp= 0;
  temp= A[i];
  A[i]= A[j];
  A[j]= temp;
}

//************************************************************************************************

boost::posix_time::time_duration TimeRoutine(string name, boost::function < void (vector<int>&)> fun, 
                   vector<int> A){

    boost::posix_time::ptime startTime, endTime;
    boost::posix_time::time_duration totalTime;
    
    startTime = boost::posix_time::microsec_clock::local_time();
    endTime = boost::posix_time::microsec_clock::local_time();

    startTime = boost::posix_time::microsec_clock::local_time();
    fun(A);
    
    endTime = boost::posix_time::microsec_clock::local_time();
    cout <<"\t" << name << ": ";
    totalTime = endTime-startTime;
    cout << "\tTime: " << totalTime;
    cout << endl;
    if (!ErrorCheck(A) ){
        cout << endl;
        cout << "ERROR ERROR ERROR ERROR ERROR ERROR " << endl;
        cout << endl << endl << endl;
    }
    return totalTime;
}

//************************************************************************************************

boost::posix_time::time_duration TimeRoutine2(string name, boost::function < void (vector<int>&, int, int)> fun, 
                   vector<int> A){

    boost::posix_time::ptime startTime, endTime;
    boost::posix_time::time_duration totalTime;
    
    startTime = boost::posix_time::microsec_clock::local_time();
    endTime = boost::posix_time::microsec_clock::local_time();

    startTime = boost::posix_time::microsec_clock::local_time();
      fun(A, 0, A.size());

    endTime = boost::posix_time::microsec_clock::local_time();
    cout <<"\t" << name << ": ";
    totalTime = endTime-startTime;
    cout << "\tTime: " << totalTime;

    cout << endl;
    if (!ErrorCheck(A) ){
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

void Test(string name, boost::function < void (vector<int>&)> fun){ 
  int n= 2000;
  if(name == "InsertionSort"){
    n= 100; 
  }
  for(int i= 0; i < 10; i++)
  { 
     boost::posix_time::time_duration stime;
     for ( int j= 0; j < 10; j++)
     {
       stime += TimeRoutine(name, fun, FillArray(n));
     }
     
     Summary(name, stime, n);
     n*=2;
  }
}

//************************************************************************************************

void Test2(string name, boost::function < void (vector<int>&, int, int)> fun){ 

  int n= 2000;
  for(int i= 0; i < 10; i++)
  { 
     boost::posix_time::time_duration stime;
     for ( int j= 0; j < 10; j++)
     {
       stime += TimeRoutine2(name, fun, FillArray(n));
     }
     Summary(name, stime, n);
     n*= 2;
  }
}

//**********************************************************************************
void Summary(string name, boost::posix_time::time_duration time, int n){
    boost::posix_time::time_duration avg= time/10;
    cout << endl <<  "*********************************************************" << endl;
    cout << "        Summary for " << name << " with array size "<< n << endl;
    cout << "                                               " << endl;
    cout << "        Total Time:   " << time << endl <<endl;
    cout << "        Average Time: " << avg << endl << endl;
    cout << "*********************************************************" << endl;
}

//**********************************************************************************
void SummaryFile(string name, boost::posix_time::time_duration time, int n){
    boost::posix_time::time_duration avg= time/10;
    cout << "\t" << name << "\t"<< n << endl;
    cout << "\t" << "TOTAL\t" <<time << endl;
    cout << "\t" << "AVG\t" << avg << endl;
}

//**********************************************************************************
vector<int> FillArray(int n){
   static bool seeded = false; 
   static boost::mt19937 rng;
   static boost::uniform_int<> dist(2,1<<28);
   static boost::variate_generator<boost::mt19937&, boost::uniform_int<> >
   bigDie(rng,dist);

   if (!seeded){
    rng.seed(static_cast<unsigned int>(std::time(0)));
    seeded = true;
  }
   vector<int> a;
   
   for (int i= 0; i < n; i++)
     a.push_back(bigDie());
   return a;
}

//**********************************************************************************
void Print(vector<int> A){
  cout << endl << " LIST A: " << endl << "*********************" << endl;
  for (int i= 0; i < A.size(); i++){
      cout << A[i] << endl;
  } 
}
    
    