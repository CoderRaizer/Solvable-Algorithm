#include <iostream>

using namespace std;

int *tapgiaiduoc;
int sizeTapGiaiDuoc;
string *operators;

struct Node{
	string R;
	int U;
	int *V;
	int size;
	Node *pNext;
};typedef struct Node NODE;

NODE* initNode(string r, int u){
	
	NODE *p = new NODE;
	if (p == NULL){
		cout << "\n Khong du bo nho de cap phat !";
		return NULL;
	}
	p->R = r;
	p->U = u;
	cout << " u co bao nhieu dinh ke (v) ; "; int num ; cin >> num;
	p->size = num;
	p->V = new int [p->size];
	for (int i = 0 ; i < num ; i++){
		int x;
		cout <<" Nhap dinh ke u thu "<<i+1<<" : ";cin >>x;
		p->V[i] = x;
	}
	p->pNext = NULL;
	return p;
}


struct List{
	NODE *pHead;
	NODE *pTail;
};typedef struct List LIST;

void initList(LIST &l){
	l.pHead = NULL;
	l.pTail = NULL;
}

void ThemVaoCuoi(LIST &l, NODE *p){
	if (l.pHead == NULL){
		l.pHead = l.pTail = p;
	}
	else{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

void themNodeChoDanhSach(LIST &l){
	cout << " --- Khoi Tao Tap R --- " << endl;
	int soluongtapR;
	cout << " So Luong Tap R : ";cin >> soluongtapR;
	for (int i = 0 ; i < soluongtapR ; i++){
		cout << "---------------------"<<endl;
		NODE *p = new NODE;
		string r = "";
		int u;
		cout << "Nhap R: "; cin >> r;
		cout << "Nhap dinh u : "; cin >> u;
		p = initNode(r,u);
		ThemVaoCuoi(l,p);
	}
}

void xuatDanhSach(LIST l){
	for (NODE *k = l.pHead; k != NULL; k = k->pNext){
		cout <<k->R << " : "<<k->U<<" -> ";
		for (int i = 0 ; i < k->size ; i++){
			cout << k->V[i] << " ";
		}
		cout <<endl;
	}
	cout<<endl;
}

/* ------------------------------------------------------------- */
void khoiTaoTapGiaiDuoc(int n){
	for (int i = 0 ; i < n ; i++){
		int x;
		cout <<"Input : ";cin >> x;
		tapgiaiduoc[i] = x;
	}
}// Correctly
bool laDinhTrongTapGiaiDuoc(int u){
	for (int i = 0 ; i < sizeTapGiaiDuoc ; i++)
		if(u == tapgiaiduoc[i])
		return true;
	return false;
}// Correctly
bool coDinhKe(int u , LIST l){
	for (NODE *k = l.pHead ; k != NULL ; k = k->pNext){
		if(k->U == u){
			return true;
		}
	}
	return false;
}// Correctly
void xuatTapGiaiDuoc(){
	cout << " T : ";
	for (int i = 0 ; i < sizeTapGiaiDuoc ; i++ ){
		cout << tapgiaiduoc[i] << " ";
	}
	cout << endl;
}// Correctly
/* ------------------------------------------------------------- */

bool Solvable(int u , LIST l){
	if(laDinhTrongTapGiaiDuoc(u) == true) return true;
	if(laDinhTrongTapGiaiDuoc(u) == false && coDinhKe(u,l) == false) return false;
	for (NODE *k = l.pHead ; k != NULL ; k = k->pNext){
		if(k->U == u){// -> At R is applied for u
			bool ok = true;
			for(int i = 0 ; i < k->size ; i++){
				if(Solvable(k->V[i],l) == false){ok = false ; break;}
			}
			if(ok == true){ // u giai duoc theo R
				operators[u] = k->R;
				return true;
			}
		}
	}
	return false;
}



int main(){
	
	int continues = 1;
	while(continues != 0){
		system("cls");
			int soluongphantu;
			cout << "Nhap so luong phan tu : "; cin >> soluongphantu;
			cout<<"Tap giai duoc co bao nhieu phan tu : ";cin >> sizeTapGiaiDuoc; tapgiaiduoc = new int[sizeTapGiaiDuoc];
			khoiTaoTapGiaiDuoc(sizeTapGiaiDuoc);
			xuatTapGiaiDuoc();
			operators = new string[soluongphantu];
			for(int i = 0 ; i < soluongphantu ; i++){
				operators[i] = "";
			}
			/* ---------------------------------------------------------- */
			LIST l;
			initList(l);
			themNodeChoDanhSach(l);
			xuatDanhSach(l);
			
			int u;
			cout << "Nhap dinh can giai : "; cin>>u;
			bool result = Solvable(u,l);
			
			cout << endl << "------------------------------------------" <<endl;
			if( result == true ){
				cout << u << " Giai Duoc !"<<endl;
				cout << "Process : "<<endl;
				for (int i = 0 ; i < soluongphantu ; i++){
					if(operators[i] != ""){
						cout << i << "Giai Duoc Tu " <<operators[i]<<endl;
					}
				}
			}
			if(result == false) {
				cout << u << " Khong Giai Duoc! "<<endl << endl;
			}
			
			cout << " Ban Co Muon Tiep Tuc (0: exit  other: continues) : ";cin >> continues;
			
	}
	

	

	
	system("pause");
	return 0;
}
