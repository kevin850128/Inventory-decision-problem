/*
   This code can be compiled and run ok.

   輸入檔案後就可以看到兩種方法的最小成本

   usage (how to run):
     hw2_4  (then input a file)

   input file:
     data2.txt

   output file:
     none

   compile (how to compile):
     g++ -o hw2_4 hw2_4.cpp

   pseudocode:
   每一種組合的成本都算出，當新的組合小於原最小成本，則更新最小成本


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
        stdev=0; //標準差

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

    int ss[13],  //再訂購點
        QQ[11],  //經濟訂購批量
        VV[3],  //初始進貨日
        RR[8],  //訂購週期
        SS[8],  //預期期初庫存量
        minIC = 99999999,
        minBC = 99999999,
        minOC = 99999999,
        minPC = 99999999,
        minTC = 99999999,
        mins,
        minQ,
        minV,
        minR,
        minS;

    fstream file;
    char filename[50];
    cout << "Enter filename: ";
    cin >> filename;
    file.open(filename,ios::in);

    int read;

	if(!file) {
		cout << "file cannot open";
	} else {
		file >> T;
		for (int i=1; i<=T; i++){
            file >> D[i];
		}
		file>>H>>B>>A>>C>>V>>R>>I[0]>>L[0];
		for (int i=1; i<=T; i++){
            Dsum = Dsum + D[i];
		}
		Dbar = Dsum/T;
		for (int i=1; i<=T; i++){
            DD = DD + pow((D[i]-Dbar),2);
		}
		stdev = sqrt(DD/(T-1));
		s = Dbar + stdev;
		Q = sqrt(2*A*Dsum/H);
		R = 7;
		S = R*Dbar;
	}
    file.close();

    for(int i=0;i<13;i++){
        ss[i]=s-(2*stdev)+(2*i);
    }
    for(int i=0;i<11;i++){
        QQ[i]=Q-50+(10*i);
    }

    for(int i=0;i<3;i++){
        VV[i]=2*(i+1);
    }
    for(int i=0;i<8;i++){
        RR[i]=2*i+1;
        SS[i]=RR[i]*Dbar;
    }
    //--- end --- PART 1: Declaration and read file-----------

	//---begin--- PART 2: 實作(s_T,Q_T)訂購策略-----------
	//計算每天的進銷存
	for(int j=0;j<13;j++){
        s = ss[j];
        for(int k=0;k<11;k++){
            Q = QQ[k];
            IC=0,BC=0,OC=0,PC=0,TC=0;  //成本要歸零，不然會加到上一個組合的成本
            for(int i=1;i<32;i++){  //非一開始給定的都要歸零，不然會累加到上一個組合的值
                I[i]=0;
                L[i]=0;
                Y[i-1]=0;
                O[i]=0;
            }
            for (int i=0;i<T;i++){
                if(I[i]<=s){    //進貨規則
                    O[i+1]=Q;
                    Y[i+1]=1;
                }
                I[i+1] = I[i]+O[i+1]-D[i+1];
                L[i+1] = D[i+1]-I[i]-O[i+1];
                if (I[i+1]>0 ){L[i+1]=0;}
                if (L[i+1]>0){I[i+1]=0;}
            }
            //計算成本
            for (int i=1;i<=T;i++){
                IC = IC+(H*I[i]);
                BC = BC+(B*L[i]);
                OC = OC+(A*Y[i-1]);
                PC = PC+(C*O[i]);
            }
            TC=IC+BC+OC+PC;
            if(TC<minTC){
                minIC = IC;
                minBC = BC;
                minOC = OC;
                minPC = PC;
                minTC = TC;
                mins = s;
                minQ = Q;
            }
        }
	}
	cout<<"When (s=" << mins << ",Q=" << minQ << ") we can get the"<<endl;
	cout<<"Minimum total cost: "<<minTC<<" = "<<minIC<<"(IC) + "<<minBC<<"(BC) + "<<minOC<<"(OC) + "<<minPC<<"(PC)"<<endl;
    cout<<endl;
	//---end--- PART 2: 實作(s_T,Q_T)訂購策略-------------

	//---begin--- PART 3: 實作(R, S)訂購策略-----------
	//計算每天的進銷存
	minIC = 99999999,minBC = 99999999,minOC = 99999999,minPC = 99999999,minTC = 99999999;
    for(int j=0;j<3;j++){
        V=VV[j];
        for(int k=0;k<8;k++){
            R=RR[k];
            S=SS[k];
            IC=0,BC=0,OC=0,PC=0,TC=0;  //成本要歸零，不然會加到上一個組合的成本
            for(int i=1;i<32;i++){  //非一開始給定的都要歸零，不然會累加到上一個組合的值
                I[i]=0;
                L[i]=0;
                Y[i-1]=0;
                O[i]=0;
            }
            for(int i=1;i<=T;i++){
                if((i-V)%R==0 && I[i-1]<S){  //進貨規則
                    O[i]=S-I[i-1];
                    Y[i]=1;
                }
                I[i]=I[i-1]+O[i]-D[i];
                L[i]= D[i]-I[i-1]-O[i];
                if (I[i]>0){L[i]=0;}
                if (L[i]>0){I[i]=0;}
            }
            //計算成本
            for (int i=1;i<=T;i++){
                IC = IC+(H*I[i]);
                BC = BC+(B*L[i]);
                OC = OC+(A*Y[i-1]);
                PC = PC+(C*O[i]);
            }
            TC=IC+BC+OC+PC;
            if(TC<minTC){
                minIC = IC;
                minBC = BC;
                minOC = OC;
                minPC = PC;
                minTC = TC;
                minV = V;
                minR = R;
                minS = S;
            }
        }
    }
    cout<<"When (V=" << minV << ",R=" << minR <<",S="<< minS <<") we can get the"<<endl;
	cout<<"Minimum total cost: "<<minTC<<" = "<<minIC<<"(IC) + "<<minBC<<"(BC) + "<<minOC<<"(OC) + "<<minPC<<"(PC)"<<endl;
    cout<<endl;
	//---end--- PART 3: 實作(R, S)訂購策略-------------
	return 0;
}
