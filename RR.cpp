#include <iostream>
#include<iostream>
#include<fstream>
#include<vector>
#include<string.h>
#include<string>
#include<cstdlib>
using namespace std;

static int ind = 0;
struct statesaver{
	int id;
	int cycle;
	statesaver(){
		id = -2;
		cycle = -2;
	}

};
struct process{

	int PID;
	int Burst_time;
	int Arrival_time;

	int status;
	process(){
		PID = 0;
		Burst_time = 0;
		Arrival_time = 0;
		status = 0;
	}
	process(int id, int t1, int t2){
		PID = id;
		Arrival_time = t1;
		Burst_time = t1;

	}

};

bool burst_time_exist(process * & p, int n){

	for (int i = 0; i < n; i++){

		if (p[i].Burst_time>0){
			return true;
		}

	}
	return false;
}

bool is(process H,process * Q2,int size2){
	bool p = false;
	for (int i = 0; i < size2; i++){
		
		//cout << H.PID<<"   "<<H.status;
		if (Q2[i].PID==H.PID){
			p= true;
		
		}
	}
	return p;

}
void print(process H){
	cout << endl;
	cout << H.PID << "  " << H.Arrival_time << "  " << H.Burst_time << "  " << H.status << "  ";
	

}
void executable(int, process * &, process * &, int &, process *&, int &, int &, int, statesaver * & );
void manipulation(process * & , process * & , int &, int &, int);
void manipulation2(process * & P, process  H,int n ){
	for (int i = 0; i < n; i++){

		if (P[i].PID ==  H.PID){
			P[i].status = 1;

		}


	}

}
void  check(process * & P, process * & Q1, int size1, process * & Q2, int size2, int n, int T, int qt, statesaver * & S){
	for (int i = 0; i<n; i++){

		if (P[i].Arrival_time<=T && P[i].Burst_time>0 ){

			if (!is(P[i], Q2, size2)){
				Q1[size1] = P[i];
				Q1[size1].status = 1;
				size1++;
				P[i].status = 1;
			}
		}
	}


	if (Q1[0].PID <= 0 && Q2[0].PID >0 ){
		for (int i = 0; i <size2; i++){
			cout << size2<<"    ";
			Q1[i] = Q2[i];
			Q1[i].status = 1;
			manipulation2(P, Q1[i], n);

			Q2[i].Arrival_time = 0;
			Q2[i].Burst_time = 0;

			Q2[i].PID = -2;
			Q2[i].status = -1;
			
		}
		size1 = size2;
		
		size2 = 0;
		executable(n, P, Q1, size1, Q2, size2, T, qt,S);
		return;
	
	
	}
	else{
		if (Q1[0].PID > 0 && Q2[0].PID> 0){
			for (int i = 0; i <size2; i++){
				Q1[size1] = Q2[i];
			
				
				
				Q2[i].Arrival_time = 0;
				Q2[i].Burst_time = 0;

				Q2[i].PID = -2;
				Q2[i].status = -1;
				size1++;
			}
			for (int t = 0; t < size1;t++)
			manipulation2(P, Q1[t], n);

			size2 = 0;
			executable(n, P, Q1, size1, Q2, size2, T, qt,S);

			return;


		}
		else{
			if (Q1[0].PID <= 0 && Q2[0].PID <= 0)
			{
			
				bool p=burst_time_exist(P, n);
			
				if (p == true){
				//move idle prcessor;
				
					size1++;
					executable(n,P, Q1, size1, Q2, size2, T, qt,S);
					return;


				}
				else{
					return;
					exit(0);
				}

			}
		
		
		}

	
	
	
	}

}
void manipulation(process * & P, process * & Q1, int & size1,int & n,int index){


	for (int i = 0; i < n; i++)
	{
		/*if (P[i].status == 1){
			P[i].Burst_time = Q1[index].Burst_time;
			P[i].status == 0;

		}*/


	}

}

void manipulate(process * & P, process * Q1, int Qid1, int & n, int index){


	for (int i = 0; i < n; i++)
	{
		if (P[i].PID == Qid1){
		P[i].Burst_time = Q1[index].Burst_time;
		P[i].status == 0;
		Q1[index].status = 0;
		}


	}

}
void executable(int n, process * & P, process * & Q1, int & size1, process * & Q2, int & size2, int & T, int qt,statesaver * & S)
{
	for (int i = 0; i<size1; i++){
		
		if (Q1[i].PID >= 0){
			S[ind].id = Q1[i].PID;
			S[ind].cycle = (T + qt) / qt;
			ind++;
		}
		Q1[i].Burst_time = Q1[i].Burst_time - qt;
		T = T + qt;
		if (Q1[i].Burst_time > 0){

			Q2[size2++] = Q1[i];
		}
	manipulate(P, Q1,Q1[i].PID,n,i);
	}
	cout << endl;

	for (int i = 0; i<size1; i++){
		Q1[i].status = -1;
		Q1[i].PID = -2;
		Q1[i].Burst_time = 0;
		Q1[i].Arrival_time = 0;
		
	}
	size1 = 0;
	
	check(P,Q1,size1,Q2,size2,n,T,qt,S);



}
void sswitch(int n, process * P, process * Q1, process * Q2, int & T, int qt, statesaver * & S){
	int size1 = 0;
	int size2 = 0;
	for (int i = 0; i<n; i++){
		if (P[i].Arrival_time <= T)
		{

			Q1[size1] = P[i];
			Q1[size1].status = 1;
			P[i].status = 1;

			size1++;
			
		}
		int s = 1, j = 0;
		executable(n, P, Q1, s, Q2, j, T, qt,S);

	}

}

void handle_Input(ifstream & fin, process * & P, int & n){

	fin.open("Assign-1.ip", std::ios_base::in);
	if (!fin){
		cout << "fucking file";
	}
	char storage[100][5];

	int i = 0;
	int i1 = 0, i2 = 0;
	bool p1 = false;
	while (!fin.eof()){
		char ch = fin.get();
		cout << ch;
		if (ch == '\n'){
			p1 = true;

		}

		if (p1 == true && ch >= '0' && ch <= '9'){

			storage[i1][i2] = ch;
			i2++;


		}
		if (p1 == true && (ch == ',' || ch == '\n')){

			storage[i1][i2] = '\0';
			i1++;
			i2 = 0;
		}


	}


	int k = 0;

	for (int j = 1; j < i1; j = j + 3){


		int x = atoi(storage[j]);
		P[k].PID = x;

		int x2 = atoi(storage[j + 1]);

		P[k].Arrival_time = x2;
		int x3 = atoi(storage[j + 2]);

		P[k].Burst_time = x3;
		k++;
	}
	n = k - 1;
	cout << endl;
	for (int o = 0; o < k; o++){
		cout << P[o].PID<<"  ";

		cout << P[o].Burst_time << "  ";

		cout << P[o].Arrival_time << "  ";

		cout << endl;
	}


	cout <<"size ="<< n;
}

int main()
{
	ifstream fin;
	int x = 100;
	int qt;
	process * P = new process[x];
	statesaver * S = new statesaver[x];
	int n;

	handle_Input(fin, P, n);
	int T=0;
	for (int i = 0; i < n; i++){
		cout << P[i].PID;

	}
	cout << "Enter:: ";
	cin >> qt;

	process * Q1 = new process[100];
	process * Q2 = new process[100];
	for (int i = 0; i < 100; i++){
		Q1[i].status = -1;
		Q2[i].status = -1;
		Q1[i].PID = -2;
		Q2[i].PID = -2;
		Q1[i].Arrival_time = -2;
		Q2[i].Arrival_time = -2;

	}
	sswitch(n, P, Q1, Q2, T, qt,S);
	fin.close();
	fstream fout;
	fout.open("Assign-1.op");
	for (int i = 0; i < ind; i++)
	{
		if (S[i].id>=0){
			fout << "PID " << S[i].id << ",Cycle " << S[i].cycle << ",\n";
		}

	}

	system("pause");
	return 0;

}

