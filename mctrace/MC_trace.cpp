#include <cstdlib>
#include <iostream>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

const int size=300;

void riempi(vector<vector<float> > &x){
	for (int i = 0; i < size ; i++){
		for(int j = 0; j < size; j++){
			x[i][j] = static_cast <float> (rand() ) / static_cast <float> (RAND_MAX);
		}
	}
}

void stampa(vector<vector<float> > x){//stampa la matrice
	for (int i = 0; i < size ; i++){
		for(int j = 0; j < size; j++){
			cout << x[i][j] << " ";
		}
	}
}
void stampavett(vector <float> x){
	for(int i = 0; i < x.size(); i++){
			cout << x[i] << " ";
		}
}

vector<vector<float> > trasposta(vector<vector<float> > x){//matrice trasposta
	vector <float> t(size);
	vector<vector<float> > y(size,t);
	for (int i = 0; i < size ; i++){
		for(int j = 0; j < size; j++){
			y[j][i]=(x[i][j]);
		}
	}
	return y;
}

vector<vector<float> > prodottoMatrix(vector<vector<float> > x,vector<vector<float> > y){//prodotto tra matrici
	vector <float> t(size);
	vector<vector<float> > z(size,t);
	for (int i = 0; i < y.size(); i++)
		for(int j = 0; j < x.size() ; j++) {
			z[i][j]=0;
			for(int l = 0; l < x.size() ; l++)
				z[i][j]=z[i][j]+x[i][l]*y[l][j];
		}
	return z;
}

float traccia(vector<vector<float> > x){
	float sum=0;
	for (int i = 0; i < size ; i++){
		sum+=(x[i][i]);//somma degli elementi in diagonale
	}
	return sum;
}

float normaF(vector<vector<float> > x){
	float frobenius=0;
	for (int i = 0; i < size ; i++){
		for (int r = 0; r < size ; r++){
			frobenius += pow(x[i][r], 2);
		}
	}
	return frobenius;
}

float varianza(vector<float > x,vector<float> y,int m){
	float val=0;
		for (int i = 1; i <= m; i++){
			val+=(pow((x[i]-y[m]), 2)/(m-1));//calcolo la varianza
		}
	return val;
}

vector<float> prodottoMv(vector<vector<float> >x, vector<float>y){//matrice x Vettore
	vector <float> vett;
	float val = 0;
	for(int i = 0; i < x.size(); i++) {
		val = 0;
		for (int j = 0; j < y.size(); j++)
			val+= y[j]*x[i][j];
		vett.push_back(val);
	}
	return vett; // ritorna un vettore
}

float prodottovv(vector<float>x, vector<float>y){//vettore X vettore
	float val = 0;
	for (int i = 0; i < x.size(); i++)
		val += x[i]*y[i];
	return val; // ritorna un valore
}

int main(){
	ofstream fout("datimctrace.txt");
	srand((unsigned int)time(NULL));
	int m[4]={5, 10, 25, 100};//array contenente in numero di iterazioni da effettuare
	vector <float> t(size);
	vector<vector<float> > matrixB(size,t);
	riempi(matrixB);
	vector<vector<float> > matrixBt=trasposta(matrixB);
	vector<vector<float> >a=prodottoMatrix(matrixBt, matrixB);		//A=BtB
	float tr=traccia(a);
	cout<<"Traccia:   "<<tr<<endl;
	float norma=normaF(a);
	cout<<"Norma di Frobenius al quadrato: "<<norma<<endl;
	vector <float> xm;	
	vector <float> xmmedia(100);		
	float var=0;
	float tracciamed=0;
	float varianzamed;
	float traccia=0;
	for (int i = 0; i < 4; i++){
		int count = m[i];
		for (int cento = 0; cento < 100; cento++){
			for (int m = 1; m <= count; m++){
				vector<float> u;//inizializzazione vettore di rademacher
				for(int j=0;j<size;j++){
					if(rand()%2 == 0)
						u.push_back(1);
					else
						u.push_back(-1);
				}
				//fine rademacher
				//calcolo stima della traccia
				vector<float> au=prodottoMv(a, u);
				float x=prodottovv(au, u);		//ottengo Xm
				xm.push_back(x);
				xmmedia[m]=xmmedia[m-1]+((x-xmmedia[m-1])/m);
				//fine calcolo stima traccia
			}
			fout << (int)xmmedia[count] << endl;//scrivo sul file la stima della traccia
			var+=varianza(xm,xmmedia,count);//calcolo varianza
			traccia+=xmmedia[count];//calcolo traccia
		}
		tracciamed=traccia/100;//calcolo traccia media
		varianzamed=var/100;//calcolo varianza media
		cout<<endl;
		cout<<"M= "<<count<<endl;
		cout << "Traccia stimata media ----> " << tracciamed << endl;
		cout << "Quadrato della norma di Frobenius ----> " << normaF(a) << endl;
		cout << "Varianza campionaria media della stima ----> " << varianzamed<< endl;
		cout << "Due volte il quadrato della norma di Frobenius fratto M equivale a: " << 2*normaF(a)/count << endl;
		cout<<endl;
		traccia=0;
		var=0;
	}
}