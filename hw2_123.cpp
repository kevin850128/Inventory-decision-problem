/*
   This code can be compiled and run ok.

   ��J�ɮ׫�N�i�H�ݨ��ؤ�k���w�s���p

   usage (how to run):
     hw2_123  (then input a file)

   input file:
     data1.txt or data2.txt

   output file:
     none

   compile (how to compile):
     g++ -o hw2_123 hw2_123.cpp

   pseudocode:
   �u�n�ӵۦѮvpdf�ɤ����W�h��J�Y�i


   coded by ���a�s, ID: H24031354, email: kevin040208@gmail.com
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
    int T,  //�W�������� T ��
        H,  //����������
        B,  //���ʳf����
        A,  //�榸�q�ʦ���
        C,  //���i�f����
        s,  //�A�q���I
        Q,  //�g�٭q�ʧ�q
        V,  //��l�i�f��
        R,  //�q�ʶg��
        S,  //�w������w�s�q
        Dsum=0, //T�ѹw���ݨD�q�[�`
        Dbar=0, //T�ѥ����ݨD�q
        DD=0, //�зǮt�ڸ��������l�A�]�N�O���t����
        stdev=0;  //�зǮt

    int IC=0,
        BC=0,
        OC=0,
        PC=0,
        TC=0;

    int D[32]={0}, //�x�s�� i(=1,�K,31)�Ѫ��w���ݨD�q�A����l�Ƭ� 0
        I[32]={0}, //�x�s�� i(=0,�K,31)�Ѫ������s�f�q�A����l�Ƭ� 0
        L[32]={0}, //�x�s�� i(=0,�K,31)�Ѫ������ʳf�q�A����l�Ƭ� 0
        Y[32]={0}, //�x�s�� i(=0,�K,30)�Ѫ��q�ʨM�w�A����l�Ƭ� 0
        O[32]={0}; //�x�s�� i(=1,�K,31)�Ѫ�����i�f�q�A����l�Ƭ� 0

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

	//---begin--- PART 2: ��@(s_T,Q_T)�q�ʵ���-----------
	cout << "(s=" << s << ",Q=" << Q << ") model:"<<endl;
	cout<< setw(5)<< "t"<< setw(5)<< "D"<< setw(5)<< "O"<< setw(5)<< "I"<< setw(5)<< "L"<< endl;
	cout<<"-----------------------------"<<endl;
	//�p��C�Ѫ��i�P�s
	for (int i=0;i<T;i++){
        if(I[i]<=s){    //�i�f�W�h
            O[i+1]=Q;
            Y[i]=1;
        }
        I[i+1] = I[i]+O[i+1]-D[i+1];
        L[i+1] = D[i+1]-I[i]-O[i+1];
        if (I[i+1]>0){L[i+1]=0;}
        if (L[i+1]>0){I[i+1]=0;}
	}
    //�L���e
    for (int i=0;i<=T;i++){
        cout<< setw(5)<< i<< setw(5)<< D[i]<< setw(5)<< O[i]<< setw(5)<< I[i]<< setw(5)<< L[i]<< endl;
    }
    cout<<"============================="<<endl;
    //�p�⦨��
    for (int i=1;i<=T;i++){
        IC = IC+(H*I[i]);
        BC = BC+(B*L[i]);
        OC = OC+(A*Y[i-1]);
        PC = PC+(C*O[i]);
    }
    TC=IC+BC+OC+PC;
    cout<<"Total cost: "<<TC<< " = "<<IC<<"(IC) + "<<BC<<"(BC) + "<<OC<<"(OC) + "<<PC<<"(PC)"<<endl;
    cout<<endl;
	//---end--- PART 2: ��@(s_T,Q_T)�q�ʵ���-------------

	//---begin--- PART 3: ��@(R, S)�q�ʵ���-----------
	cout << "(R=" << R << ",S=" << S << ") model:"<<endl;
	cout<< setw(5)<< "t"<< setw(5)<< "D"<< setw(5)<< "O"<< setw(5)<< "I"<< setw(5)<< "L"<< endl;
	cout<<"-----------------------------"<<endl;
	for(int i=1;i<32;i++){  //�C�Ѫ��i�P�s�k�s�A���M�|�[��W�@�Ӥ�k��
                I[i]=0;
                L[i]=0;
                Y[i-1]=0;
                O[i]=0;
    }
	//�p��C�Ѫ��i�P�s
    for(int i=1;i<=T;i++){
        if((i-V)%R==0 && I[i-1]<S){  //�i�f�W�h
            O[i]=S-I[i-1];
            Y[i-1]=1;
        }
        I[i]=I[i-1]+O[i]-D[i];
        L[i]= D[i]-I[i-1]-O[i];
        if (I[i]>0){L[i]=0;}
        if (L[i]>0){I[i]=0;}
    }
    //�L���e
    for (int i=0;i<=T;i++){
        cout<< setw(5)<< i<< setw(5)<< D[i]<< setw(5)<< O[i]<< setw(5)<< I[i]<< setw(5)<< L[i]<< endl;
    }
    cout<<"============================="<<endl;
    //�p�⦨��
    IC=0,BC=0,OC=0,PC=0,TC=0;  //�����n�k�s�A���M�|�[��W�@�Ӥ�k������
    for (int i=1;i<=T;i++){
        IC = IC+(H*I[i]);
        BC = BC+(B*L[i]);
        OC = OC+(A*Y[i-1]);
        PC = PC+(C*O[i]);
    }
    TC=IC+BC+OC+PC;
    cout<<"Total cost: "<<TC<< " = "<<IC<<"(IC) + "<<BC<<"(BC) + "<<OC<<"(OC) + "<<PC<<"(PC)"<<endl;
    cout<<endl;
	//---end--- PART 3: ��@(R, S)�q�ʵ���-------------
	return 0;
}
