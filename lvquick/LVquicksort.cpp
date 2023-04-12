#include <cstdlib>
#include <iostream>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;

int n_confronti=0;



void change(vector < int >&v, int i, int j)
{
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}

int quickSort (vector < int >&v, int start, int end)
{
  int pivotIndex = start + rand () % (end - start + 1);
  change (v, pivotIndex, start);
  int i = start + 1;
  for (int j = start + 1; j <= end; ++j)
    {
      n_confronti++;
      if (v[j] < v[start])
	{
	  change(v, i, j);
	  ++i;
	}
    }
  change (v, start, i - 1);
  return i - 1;
}


void qs (vector < int >&v, int start, int end)
{
  if (start < end)
    {
      int pivot = quickSort (v, start, end);
      qs (v, start, pivot - 1);
      qs (v, pivot + 1, end);
    }
}


void printArray(vector<int> arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
  int count=10000;//num rep
  vector<int> a_num_conf (count);
  int N=10000;//dim array
  vector<int> arr(N) ;
  srand(time(NULL));
  for (int i=0; i<N; i++){
     arr[i]=rand()%10000;
  }
  for (int i = 0; i < count; i++){
    vector<int> temp(arr.begin(),arr.end());
    qs(temp, 0, temp.size()-1);
    a_num_conf[i]=n_confronti;
    n_confronti=0;
    std::cout << "." << '\n';
  }

  double valore_medio=0;
  double valore=0;
 
    for (int i = 0; i < count; i++){
     valore+=a_num_conf[i];
   }
   ofstream f("dati.txt",ios::app);
   if(!f){
     cout << "errore nella scrittura del file" << '\n';
     return 1;
   }
   for (int i = 0; i < count; i++){
    f<<a_num_conf[i]<<endl;
  }
  f.close();
  
  //cout << endl;
   double varianza=0;
   //(sommatoria su tutti i |n_confronti meno il valore medio| )/ n_confronti
   for (int i = 0; i <count; i++) {
        varianza+=fabs((a_num_conf[i] - valore_medio));
   }
   varianza/=count;
   
	cout << "scrittura completata" << '\n';
	cout <<"valore medio: " << '\n';
	valore_medio=valore/count;
	cout << valore_medio << '\n';
	cout << endl << "varianza: " << '\n';
	cout << varianza << '\n';
   return 0;
}
