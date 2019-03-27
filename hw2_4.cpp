/*
   This code can be compiled and run ok.

   ��J�ɮ׫�N�i�H�ݨ��ؤ�k���̤p����

   usage (how to run):
     hw2_4  (then input a file)

   input file:
     data2.txt

   output file:
     none

   compile (how to compile):
     g++ -o hw2_4 hw2_4.cpp

   pseudocode:
   �C�@�زզX����������X�A��s���զX�p���̤p�����A�h��s�̤p����


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
        stdev=0; //�зǮt

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

    int ss[13],  //�A�q���I
        QQ[11],  //�g�٭q�ʧ�q
        VV[3],  //��l�i�f��
        RR[8],  //�q�ʶg��
        SS[8],  //�w������w�s�q
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

	//---begin--- PART 2: ��@(s_T,Q_T)�q�ʵ���-----------
	//�p��C�Ѫ��i�P�s
	for(int j=0;j<13;j++){
        s = ss[j];
        for(int k=0;k<11;k++){
            Q = QQ[k];
            IC=0,BC=0,OC=0,PC=0,TC=0;  //�����n�k�s�A���M�|�[��W�@�ӲզX������
            for(int i=1;i<32;i++){  //�D�@�}�l���w�����n�k�s�A���M�|�֥[��W�@�ӲզX����
                I[i]=0;
                L[i]=0;
                Y[i-1]=0;
                O[i]=0;
            }
            for (int i=0;i<T;i++){
                if(I[i]<=s){    //�i�f�W�h
                    O[i+1]=Q;
                    Y[i+1]=1;
                }
                I[i+1] = I[i]+O[i+1]-D[i+1];
                L[i+1] = D[i+1]-I[i]-O[i+1];
                if (I[i+1]>0 ){L[i+1]=0;}
                if (L[i+1]>0){I[i+1]=0;}
            }
            //�p�⦨��
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
	//---end--- PART 2: ��@(s_T,Q_T)�q�ʵ���-------------

	//---begin--- PART 3: ��@(R, S)�q�ʵ���-----------
	//�p��C�Ѫ��i�P�s
	minIC = 99999999,minBC = 99999999,minOC = 99999999,minPC = 99999999,minTC = 99999999;
    for(int j=0;j<3;j++){
        V=VV[j];
        for(int k=0;k<8;k++){
            R=RR[k];
            S=SS[k];
            IC=0,BC=0,OC=0,PC=0,TC=0;  //�����n�k�s�A���M�|�[��W�@�ӲզX������
            for(int i=1;i<32;i++){  //�D�@�}�l���w�����n�k�s�A���M�|�֥[��W�@�ӲզX����
                I[i]=0;
                L[i]=0;
                Y[i-1]=0;
                O[i]=0;
            }
            for(int i=1;i<=T;i++){
                if((i-V)%R==0 && I[i-1]<S){  //�i�f�W�h
                    O[i]=S-I[i-1];
                    Y[i]=1;
                }
                I[i]=I[i-1]+O[i]-D[i];
                L[i]= D[i]-I[i-1]-O[i];
                if (I[i]>0){L[i]=0;}
                if (L[i]>0){I[i]=0;}
            }
            //�p�⦨��
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
	//---end--- PART 3: ��@(R, S)�q�ʵ���-------------
	return 0;
}
