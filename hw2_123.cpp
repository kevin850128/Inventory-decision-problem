/*
   This code can be compiled and run ok.

   輸入檔案後就可以看到兩種方法的庫存狀況

   usage (how to run):
     hw2_123  (then input a file)

   input file:
     data1.txt or data2.txt

   output file:
     none

   compile (how to compile):
     g++ -o hw2_123 hw2_123.cpp

   pseudocode:
   只要照著老師pdf檔內的規則輸入即可


   coded by 江冠駒, ID: H24031354, email: kevin040208@gmail.com
   date: 2018.03.28
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>


using namespace std;

int main() {
    //---begin--- PART 1: Declaration and read file -----------
    int T,  //規劃期間為 T 天
        H,  //單位持有成本
        B,  //單位缺貨成本
        A,  //單次訂購成本
        C,  //單位進貨成本
        s,  //再訂購點
        Q,  //經濟訂購批量
        V,  //初始進貨日
        R,  //訂購週期
        S,  //預期期初庫存量
        Dsum=0, //T天預測需求量加總
        Dbar=0, //T天平均需求量
        DD=0, //標準差根號內的分子，也就是離差平方
        stdev=0;  //標準差

    int IC=0,
        BC=0,
        OC=0,
        PC=0,
        TC=0;

    int D[32]={0}, //儲存第 i(=1,…,31)天的預測需求量，先初始化為 0
        I[32]={0}, //儲存第 i(=0,…,31)天的期末存貨量，先初始化為 0
        L[32]={0}, //儲存第 i(=0,…,31)天的期末缺貨量，先初始化為 0
        Y[32]={0}, //儲存第 i(=0,…,30)天的訂購決定，先初始化為 0
        O[32]={0}; //儲存第 i(=1,…,31)天的期初進貨量，先初始化為 0

    fstream file;
    char filename[50];
    cout << "Enter filename: ";
    cin >> filename;
    file.open(filename,ios::in);

	if(!file) {
		cout << "file cannot open";
	} else {
		file >> T;
		cout << "T=" << T << ", ";
		cout << "D= ";
		for (int i=1; i<=T; i++){
            file >> D[i];
            cout << D[i] <<" ";
		}
		cout << endl;

		file>>H>>B>>A>>C>>V>>R>>I[0]>>L[0];
		cout << "H=" << H << ", ";
		cout << "B=" << B << ", ";
		cout << "A=" << A << ", ";
		cout << "C=" << C << ", ";
		cout << "V=" << V << ", ";
		cout << "R=" << R << ", ";
		cout << "I[0]=" << I[0] << ", ";
		cout << "L[0]=" << L[0] << endl;
		for (int i=1; i<=T; i++){
            Dsum = Dsum + D[i];
		}
		cout << "D=" << Dsum << ", ";
		Dbar = Dsum/T;
		cout << "D_bar=" << Dbar << ", ";
		for (int i=1; i<=T; i++){
            DD = DD + pow((D[i]-Dbar),2);
		}
		stdev = sqrt(DD/(T-1));
		cout << "stdev=" << stdev << "; ";
		s = Dbar + stdev;
		Q = sqrt(2*A*Dsum/H);
		cout << "(s,Q)=(" << s << "," << Q << "); ";
		R = 7;
		S = R*Dbar;
		cout << "(R,S)=(" << R << "," << S << ")"<<endl;
	}
    file.close();
    cout<<endl;
    //--- end --- PART 1: Declaration and read file-----------

	//---begin--- PART 2: 實作(s_T,Q_T)訂購策略-----------
	cout << "(s=" << s << ",Q=" << Q << ") model:"<<endl;
	cout<< setw(5)<< "t"<< setw(5)<< "D"<< setw(5)<< "O"<< setw(5)<< "I"<< setw(5)<< "L"<< endl;
	cout<<"-----------------------------"<<endl;
	//計算每天的進銷存
	for (int i=0;i<T;i++){
        if(I[i]<=s){    //進貨規則
            O[i+1]=Q;
            Y[i]=1;
        }
        I[i+1] = I[i]+O[i+1]-D[i+1];
        L[i+1] = D[i+1]-I[i]-O[i+1];
        if (I[i+1]>0){L[i+1]=0;}
        if (L[i+1]>0){I[i+1]=0;}
	}
    //印表內容
    for (int i=0;i<=T;i++){
        cout<< setw(5)<< i<< setw(5)<< D[i]<< setw(5)<< O[i]<< setw(5)<< I[i]<< setw(5)<< L[i]<< endl;
    }
    cout<<"============================="<<endl;
    //計算成本
    for (int i=1;i<=T;i++){
        IC = IC+(H*I[i]);
        BC = BC+(B*L[i]);
        OC = OC+(A*Y[i-1]);
        PC = PC+(C*O[i]);
    }
    TC=IC+BC+OC+PC;
    cout<<"Total cost: "<<TC<< " = "<<IC<<"(IC) + "<<BC<<"(BC) + "<<OC<<"(OC) + "<<PC<<"(PC)"<<endl;
    cout<<endl;
	//---end--- PART 2: 實作(s_T,Q_T)訂購策略-------------

	//---begin--- PART 3: 實作(R, S)訂購策略-----------
	cout << "(R=" << R << ",S=" << S << ") model:"<<endl;
	cout<< setw(5)<< "t"<< setw(5)<< "D"<< setw(5)<< "O"<< setw(5)<< "I"<< setw(5)<< "L"<< endl;
	cout<<"-----------------------------"<<endl;
	for(int i=1;i<32;i++){  //每天的進銷存歸零，不然會加到上一個方法的
                I[i]=0;
                L[i]=0;
                Y[i-1]=0;
                O[i]=0;
    }
	//計算每天的進銷存
    for(int i=1;i<=T;i++){
        if((i-V)%R==0 && I[i-1]<S){  //進貨規則
            O[i]=S-I[i-1];
            Y[i-1]=1;
        }
        I[i]=I[i-1]+O[i]-D[i];
        L[i]= D[i]-I[i-1]-O[i];
        if (I[i]>0){L[i]=0;}
        if (L[i]>0){I[i]=0;}
    }
    //印表內容
    for (int i=0;i<=T;i++){
        cout<< setw(5)<< i<< setw(5)<< D[i]<< setw(5)<< O[i]<< setw(5)<< I[i]<< setw(5)<< L[i]<< endl;
    }
    cout<<"============================="<<endl;
    //計算成本
    IC=0,BC=0,OC=0,PC=0,TC=0;  //成本要歸零，不然會加到上一個方法的成本
    for (int i=1;i<=T;i++){
        IC = IC+(H*I[i]);
        BC = BC+(B*L[i]);
        OC = OC+(A*Y[i-1]);
        PC = PC+(C*O[i]);
    }
    TC=IC+BC+OC+PC;
    cout<<"Total cost: "<<TC<< " = "<<IC<<"(IC) + "<<BC<<"(BC) + "<<OC<<"(OC) + "<<PC<<"(PC)"<<endl;
    cout<<endl;
	//---end--- PART 3: 實作(R, S)訂購策略-------------
	return 0;
}
