#include <cstdlib>
#include <iostream>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

const int t=1; //numero generali traditori
const int n=4; //numero generali totale
const int l=n-t; //numero generali leali
const int r=10000;

void stampa(int m [l] [n]){
		for (int i = 0; i < l; i++) {
			for(int j=0;j<n;j++){
				cout<<	m[i][j]<<"  ";
			}
			cout<<endl;
		}

} 
void traditore(int m [l] [n]){
		for(int j=0;j<3;j++){
			for (int i = 0; i < 3; i++) {
				if(i==j)m[i][3]=1-m[i][j];
			}
		}
}
int set_maj(int m [l] [n],int l){
	int zero=0;
	int uno=0;
	for(int j=0; j<4; j++){// calcolo maj
		if(m[l][j]==0) zero++;
		else uno++;
		}
					//ritorno  maj
	if(zero>uno) return 0;
	return 1;
				
}

int set_tally (int m [l] [n],int l){
	int zero=0;
	int uno=0;
	for(int j=0; j<4; j++){// 
		if(m[l][j]==0) zero++;
		else uno++;
		}
	if(zero>uno)return zero;
	return uno;

}

int probacc (int a[r]){
	// Determino il numero di round dopo il quale la probabilità che l'accordo è raggiunto è più grande del 99.9%
	int ripetizioni [r];
	int somma = 0;
	for (int i = 0; i<r; i++){	//inizializzo vettore a 0
    	ripetizioni[i]=0;
  	}
  		for (int i = 0; i<r; i++){			// riempo un vettore con tutti i possibili numeri di round dopo i quali si raggiunge un accordo e conto quate volte escono
    	ripetizioni[a[i]]++;
  	}
  		for (int i = 0; i<r; i++){	
  	}
  	
  	for (int i = 0; i<44; i++){		// sommo le volte in cui si raggiunge un accordo in tali round e se questo supera il 99.9% delle volte lo ritorno
    	somma+=ripetizioni[i];
    	if (somma>=r-(r*0.001))	return i++;
	}
	return -1;
}

float media(int a[r]){
	float med=0;
	for(int i=0;i<r;i++){
		med+=a[i];
	}
	return med=med/r;
}
float varianza(int a[r]){
		float somma = 0;
		for (int i = 0; i < r; i++)
		somma += pow(a[i], 2);
		float mediaPow = (float)somma/r;
  		float var;
  		return var = mediaPow-pow(media(a), 2);
}

int main()
{
	
    srand((unsigned)time(NULL));
	int a [l][n];
	int num_round=0;
	int med_round[r];
	bool loop=true;
	int zero=0;
	int uno=0;
	int maj;
	int tally;
	for(int l=0;l<r;l++){
		int a2 [l];
		num_round=0; //azzero i numeri di round
		// inizializzo il generatore di numeri pseudo-casuali
	 	int val= rand()%2;
		for(int j=0;j<3;j++){ // ciclo 10k
			for (int i = 0; i < 3; i++) {
					a[i][j]=val;
			}
			 val= rand()%2;
		}
		cout<<endl<<"                    MATRICE INIZIALE              :"<<endl;
		traditore(a);		
		stampa(a);
		int flag=0;	
		int moneta;
		bool loop =true;
			while(loop!=false){
			// itero con una variabile i sulle righe della matrice
				for(int i=0; i<3 ;i++){
							//precondizione
						if(a[0][0]==a[0][1] && a[0][1]==a[0][2]){
							med_round[l]=num_round;
							loop=false;
							cout<<endl<<"NUMERO DI ROUND:    "<<num_round<<endl;
							break;
						}
					num_round++;
					moneta=rand()%2;					
					// Calcolo maj e tally tra i 4 valori di quella riga di quel determinato round i
					maj=set_maj(a,i); 
					tally=set_tally(a,i);
					cout<<endl<<endl<<"MAJ:       "<<maj<<"    tally:         "<<tally<<"          MONETA:           "<<moneta<<endl<<endl;
						 // Se tally > 2t+1
					if(tally>=3){
							a2[i]=maj;
							// Nel prossimo round il processo i avrà valore = maj, quindi tutta l'i-esima colonna della matrice avrà solo il valore maj
					}
					else{// altrimenti
						a2[i]=moneta;
						// Nel prossimo round il processo i avrà valore = moneta, quindi tutta l'i-esima colonna della matrice avrà solo il valore moneta	
					}
							//ridefinire la matrice a attraverso i valori in a2
					for (int j = 0; j < 3; j++) {
							a[j][i]=a2[i];
					}
					traditore(a);
					stampa(a);	
				}
		    }
		}
		cout << "Numero di round per avere probabilita' di raggiungere un accordo > del 99.9% e': " << probacc(med_round)<<endl;
		cout<<endl<<"MEDIA ROUND:"<<media(med_round)<<endl;
  		cout << "Mentre la varianza: " << varianza(med_round) << endl;
}