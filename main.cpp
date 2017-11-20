#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
using namespace std;


int getNumFromLine(string& line);
void loadFromFile(ifstream& fin, const char* fileName,vector<int>& values,vector<int>& weights,int& numItems,int& weightBound);
bool openFile(ifstream& fin,const char* fileName);
int max(int num1,int num2);
void knapSack(int numItems,int weightBound,vector<int>& values,vector<int>& weights);

int main()
{
vector<int> values;
vector<int> weights;
ifstream fin;  
const char* fileName = "knapsack.txt";
int numItems;
int weightBound;
loadFromFile(fin,fileName,values,weights,numItems,weightBound);
knapSack(numItems,weightBound,values,weights);

return 0;
}

void knapSack(int numItems,int weightBound,vector<int>& values,vector<int>& weights)
{
vector<int> itemsInKnapsack;
int knapSack[numItems+1][weightBound+1];
int row = numItems;
int column = weightBound;
//extra row/col to allow for 0th row/column

for(int i = 0; i <= numItems;i++)
{
  for(int j = 0; j<=weightBound;j++)
  {
    if(i == 0 || j == 0)
    {
      //init 0th row and column.
      knapSack[i][j] = 0;
    }
    
    else if(j >=  weights[i-1])
    {
      //if item can't even fit yet...carry value from previous row up.
      knapSack[i][j] = max(values[i-1] + knapSack[i-1][j-weights[i-1]],knapSack[i-1][j]);
    }
    else 
    {
      //else item can fit...choose the max..
     knapSack[i][j] = knapSack[i-1][j];

    }
  }
}

while(row > 0)
{
   if(knapSack[row][column] > knapSack[row-1][column] && knapSack[row][column] > knapSack[row][column-1])
   {
     cout << knapSack[row][column]<< endl;
      itemsInKnapsack.push_back(row);
      row--;
      column = column - weights[row];
   }else
   {
      row--;
   }

}

cout << "Optimal Solution " << knapSack[numItems][weightBound] << " And involves items {";

for(int i = 0; i < itemsInKnapsack.size();i++)
{
  if(i == itemsInKnapsack.size()-1)
  {
    cout << itemsInKnapsack[i] << "}"<< endl;
  }else
  {
    cout << itemsInKnapsack[i] << ",";
  }
}

}//END knapSack


int max(int num1,int num2)
{
  return (num1 > num2) ? num1 : num2;
}//END max


void loadFromFile(ifstream& fin,const char* fileName,vector<int>& values,vector<int>& weights,int& numItems,int& weightBound)
{

string line;
if(!openFile(fin,fileName))
{
  cerr << "Error: Unable to open file." << endl;
  exit(1);

}


getline(fin,line);
numItems = getNumFromLine(line);
weightBound = getNumFromLine(line);

while(getline(fin,line))
{
  weights.push_back(getNumFromLine(line));
  values.push_back(getNumFromLine(line));

}

}//END loadFromFile


bool openFile(ifstream& fin, const char* FileName)
{

fin.open(FileName);
return fin.is_open();

}

int getNumFromLine(string& line)
{
 int num = stoi(line.substr(0));
 
 if(line.size() != 1){
 line = line.substr(2,line.size()-1);
 }
 
 return num;
}
