#include<iomanip>
#include<fstream>
#include<conio.h>
#include<iostream>
using namespace std;
int n,i,j;
fstream f;
char fn[30];
struct student{
	char code[10],name[30],gender[4];
	int day,month,year;
	double point;
};
void inp(student ds[]){
	i=0;
	cout<<"nhap danh sach sinh vien - ket thuc khi nhap ma sinh vien = 0";
	do{
		fflush(stdin);
		cout<<"\n------"<<endl;
		cout<<"ma sinh vien: ";gets(ds[i].code);	
		if(strcmp(ds[i].code,"0") != 0)
		{
			fflush(stdin);
			cout<<"ho ten: ";gets(ds[i].name);
			cout<<"gioi tinh: ";gets(ds[i].gender);
			do{
			cout<<"ngay sinh: ";cin>>ds[i].day;
			cout<<"thang sinh: ";cin>>ds[i].month;
			cout<<"nam sinh: ";cin>>ds[i].year;
			if (ds[i].day<0 || ds[i].day > 31) cout<<"nhap lai\n";
			else if(ds[i].month<0 || ds[i].month>12) cout<<"nhap lai\n";
			else if(ds[i].year<1900 || ds[i].year > 2022) cout<<"nhap lai\n";
		    } while(ds[i].day>31||ds[i].month>12||ds[i].year<1900||ds[i].year>2022);
		    cout<<"diem trung binh: ";cin>>ds[i].point;
		    i++;
		}
	}while (strcmp(ds[i].code,"0") != 0);
	n=i;
}
void chuanhoa(char s[100])//s la tham bien 
{
	//xoa trang dau xau
	i=0;
	while (s[i]==' ' && i<strlen(s)) i=i+1;
	strcpy(&s[0],&s[i]);
	//xoa trang cuoi xau
	while (s[strlen(s)-1]==' ') s[strlen(s)-1]='\0';
	//xoa cac ky tu trang giua xau
	i=0;
	while (i<strlen(s)-1)
	{
		if (s[i]==' '&& s[i+1]==' ')
			strcpy(&s[i],&s[i+1]);
		else
			i=i+1;	
	}	
}
void outp(student ds[],bool bro){
	if(bro==0){
		for(i=0;i<n;i++){
			chuanhoa(ds[i].name);
		}
	}
	cout<<"STT"<<setw(9)<<"MA SV"<<setw(14)<<"HO TEN"<<setw(17);
	cout<<"GIOI TINH"<<setw(14)<<"NGAY SINH"<<setw(15);
	cout<<"DIEM TB"<<endl;
	for(i=0;i<n;i++){
		cout<<i+1<<setw(10)<<ds[i].code<<setw(20)<<ds[i].name<<setw(10);
		cout<<ds[i].gender<<setw(8)<<ds[i].day<<"/"<<ds[i].month<<"/";
		cout<<ds[i].year<<setw(15)<<fixed<<setprecision(2)<<ds[i].point;
		cout<<endl;
	}
	cout<<endl;
}
void savefile(student ds[]){
	cout<<"nhap ten file can luu: ";
	fflush(stdin);gets(fn);
	f.open(fn,ios::out | ios::binary);
	for(i=0;i<n;i++){
		f.write((char*)&ds[i],sizeof(ds[i]));
	}
	f.close();
}
void readfile(student ds[]){
	n=0;
	cout<<"nhap ten file can doc: ";
	fflush(stdin);gets(fn);
	f.open(fn,ios::in | ios::binary);
	while(! f.eof()){
		f.read((char *)&ds[n],sizeof(ds[n]));
		n=n+1;
	}
	n=n-1;
	f.close();
}
void luachon(student ds[]){	
	int chon;
		cout<<"nhap so 1 la co,nhap so bat ki la chon khong luu file,ban chon: ";
		cin>>chon;
		if(chon == 1){
			cout<<"ban chon luu file\n";
			savefile(ds);
		} else cout<<"ban chon khong luu file\n";
}
void pressAnyKey() {
    cout << "\nBam phim bat ky de tiep tuc...\n";
    getch();
}
void alphabetlly(student ds[], string a[]){
	int max, vt;
	string demkt;
	student count;	
	for (i = 0; i < n; i++){
		max = strlen(ds[i].name);
		demkt = "";
		for (j = max-1; j >= 0; j--){
			if (ds[i].name[j] == ' ')
				break;
			else demkt = ds[i].name[j] + demkt;
		}
		a[i] = demkt;
	}	
	for (i = 0; i < n; i++){
		vt = i;
		for (j = i; j < n; j++){
			if (a[vt] > a[j])
				vt = j;
		}
		demkt = a[vt];
		a[vt] = a[i];
		a[i] = demkt;
		count = ds[vt];
		ds[vt] = ds[i];
		ds[i] = count;
	}
}
void min(student ds[]){
	int min=0;
	for( i=0;i<n;i++){
		if(ds[i].point<ds[min].point && strcmp(ds[i].gender,"nu") == 0){
			min=i;
		}
	}
	for(i=0;i<n;i++){
		if(ds[i].point==ds[min].point && strcmp(ds[i].gender,"nu") == 0){
			cout<<"\nMA SV: "<<ds[i].code;
			cout<<"\nHO TEN: "<<ds[i].name;
			cout<<"\nNGAY SINH: "<<ds[i].day<<"/"<<ds[i].month<<"/"<<ds[i].year;
			cout<<"\nDIEM TB: "<<ds[i].point<<fixed<<setprecision(2);
		}
	}
	cout<<endl;
}
int male(student ds[]){
	int c=0;
	for( i=0;i<n;i++){
		if(strcmp(ds[i].gender,"nam") == 0){
			c++;
		}
	}
	return c;
}
int main(){
	student ds[1000];
	string a[100];
	int choise;
	cout<<"\n===============MENU===============\n";
	cout<<" 1: nhap,xuat va luu 1 file moi\n";
	cout<<" 2: hien file da luu\n";
	cout<<" 3: xap sep ten sinh vien theo alphabet\n";
	cout<<" 4: tim sinh vien nu co diem trung binh thap nhat\n";
	cout<<" 5: dem so sinh vien nam\n";
	cout<<" 6: ten cac file da duoc luu san truoc khi bam lua chon 1 tao them file moi\n";
	while(true){
		cout<<"\n nhap lua chon cua ban: ";cin>>choise;
		switch(choise)
	{
		case 1:
			cout << "ban chon tao file nhap xuat moi." << endl;
			inp(ds);
			outp(ds,0);
			savefile(ds);
			break;
   		case 2:
			cout<<"Ban chon hien file da luu."<<endl;
			readfile(ds);
			outp(ds,0);
			break;
		case 4:
			cout<<"Ban chon tim sinh vien nu co diem trung binh thap nhat."<<endl;
			readfile(ds);
			cout<<"sinh vien nu co diem trung binh thap nhat !";
			min(ds);
			luachon(ds);
			break;
		case 3:
			cout<<"Ban chon sap xep ten sinh vien theo thu tu alphabet."<<endl;
			readfile(ds);
			alphabetlly(ds,a);
			outp(ds,0);
			luachon(ds);
			break;
		case 5:
			cout<<"Ban chon dem so sinh vien nam."<<endl;
			readfile(ds);
			cout<<"so sinh vien nam la: "<<male(ds)<<endl;
			luachon(ds);
			break;
		case 0:
			cout<<"Ban chon thoat khoi menu"<<endl;
			return 0;
		default:
			cout<<"\nKhong co chuc nang nay !";
			cout << "\nHay chon chuc nang trong hop menu.";
            pressAnyKey();
            break;
        }
    }
}