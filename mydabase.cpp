#include "mydatabase.h"
#include <fstream>
#include <bits/stdc++.h>

std::ostream& operator << (std::ostream& out, const student& st) {
    out << st.surname << " " << st.name << " " << st.phone << " " << st.mail << " " << st.brthd << " ";
    return out;
}

std::istream& operator >> (std::istream& in, student& st) {
    std::cout << "Surname: "; in.getline(st.surname, 32);
    std::cout << "Name: ";    in.getline(st.name, 16);
    std::cout << "Phone: ";    in.getline(st.phone, 16);
    std::cout << "Mail: ";    in.getline(st.mail, 32);
    std::cout << "Date of birth(DD.MM.YYYY): ";    in.getline(st.brthd,12);
    return in;
}

bool operator < (const student& left, const student& right) {
    return strcmp(left.surname, right.surname) < 0;
}

bool compByBirth(const student& left, const student& right) {
    int ld=0,lm=0,ly=0,rd=0,rm=0,ry=0;
    ld=(left.brthd[0]-48)*10+(left.brthd[1]-48);
    lm=(left.brthd[3]-48)*10+(left.brthd[4]-48);
    ly=(left.brthd[6]-48)*1000+(left.brthd[7]-48)*100+(left.brthd[8]-48)*10+(left.brthd[9]-48);
    
    rd=(right.brthd[0]-48)*10+(right.brthd[1]-48);
    rm=(right.brthd[3]-48)*10+(right.brthd[4]-48);
    ry=(right.brthd[6]-48)*1000+(right.brthd[7]-48)*100+(right.brthd[8]-48)*10+(right.brthd[9]-48);
    
    if(ly<ry) return true;
    if(ly==ry && lm<rm) return true;
    if(ly==ry && lm==rm && ld<rd) return true;
    return false;
}

bool compByDayMon(const student& left, const student& right) {
    int ld=0,lm=0,rd=0,rm=0;
    ld=(left.brthd[0]-48)*10+(left.brthd[1]-48);
    lm=(left.brthd[3]-48)*10+(left.brthd[4]-48);
    
    rd=(right.brthd[0]-48)*10+(right.brthd[1]-48);
    rm=(right.brthd[3]-48)*10+(right.brthd[4]-48);
    
    if(lm<rm) return true;
    if(lm==rm && ld<rd) return true;
    return false;
}

bool compBySurname(const student& left, const student& right) {
    int result = strcmp(left.surname, right.surname);
    if (result < 0)
        return true;
    if (result == 0) // Одинаковые фамилии
        return strcmp(left.name, right.name) < 0;
    return false;
}

int addRecord(DataBase& DB) {
    student* tmp = new student[DB.count + 1];
    for (int i = 0; i < DB.count; ++i) {
        tmp[i] = DB.data[i];
    }
    if (DB.data)
        delete[] DB.data;
    DB.data = tmp;

    std::cin >> DB.data[DB.count];
    ++DB.count;
    std::cout << "Contact succesfully added!"<<std::endl;
    return DB.count;
}

int findbs(const DataBase& DB) {
    std::cout << "Contact surname: ";
    char tmp[32];
    std::cin >> tmp; std::cin.ignore();
    int index;
    for (index = 0; index < DB.count; ++index) {
    	int result = strcmp(tmp, DB.data[index].surname);
        if (result == 0)
    	{
        	std::cout << DB.data[index] << std::endl;
    		return index;
		}
    }
    std::cout << "There are no any contact with surname " << tmp << " in DB" << std::endl;
    return -1;
}

int findbpn(const DataBase& DB) {
    std::cout << "Contact phone number: ";
    char tmp[32];
    std::cin >> tmp; std::cin.ignore();
    int index;
    for (index = 0; index < DB.count; ++index) {
    	int result = strcmp(tmp, DB.data[index].phone);
        if (result == 0)
    	{
        	std::cout << DB.data[index] << std::endl;
    		return index;
		}
    }
    std::cout << "There are no any contact with phone number " << tmp << " in DB" << std::endl;
    return -1;
}

void exportDB(const DataBase& DB) {
    char fname[256];
    std::cout << "Database file name [contacts.txt]: ";
    std::cin.getline(fname, 256);
    if (strlen(fname) < 1)
        strcpy(fname, "contacts.txt");
    std::ofstream outFile;
    outFile.open(fname);
    if (!outFile) {
        std::cout << "Can not open file " << fname << std::endl;
        return;
    }
    for (int i = 0; i < DB.count; ++i) {
        outFile << DB.data[i] <<"  "<< std::endl;
    }
    outFile.close();
    std::cout << "Contacts succesfully exported to "<<fname<<std::endl;
}

void sortsurname(DataBase& DB) {
    MySort(DB.data, DB.count, compBySurname);
    std::cout << "Database sorted by Surname" << std::endl;
}

void sortbirth(DataBase& DB) {
    MySort(DB.data, DB.count, compByBirth);
    std::cout << "Database sorted by date of birth" << std::endl;
}

void sortdays(DataBase& DB) {
    MySort(DB.data, DB.count, compByDayMon);
    time_t now = time(0);
	tm *ltm = localtime(&now);
	int ld=0,lm=0,k=0;
	ld=ltm->tm_mday;
	lm=ltm->tm_mon;
    for(int i=0;i<DB.count;++i)
	{
		int rd=0,rm=0;
		rd=(DB.data[i].brthd[0]-48)*10+(DB.data[i].brthd[1]-48);
    	rm=(DB.data[i].brthd[3]-48)*10+(DB.data[i].brthd[4]-48);
    	if(ld<=rd&&lm<=rm)
    	{
    		k=i;
    		break;
		}
	}
	int l=0;
	student* tmp = new student[DB.count];
    for (int i = k; i < DB.count; ++i) {
        tmp[l++] = DB.data[i];
    }
    for(int i=0;i<k;++i)
    {
    	tmp[l++] = DB.data[i];
	}
    if (DB.data)
        delete[] DB.data;
    DB.data = tmp;
	
    std::cout << "Database sorted by days until date of birth" << std::endl;
}

void deleteRecord(DataBase& DB) {
    int index = findbs(DB);
    if (index < 0) {
        return;
    }
    std::cout << "Are you sure? (Y/N) ";
    char ch[128];
    std::cin.getline(ch, 128);
    if (ch[0] == 'Y' || ch[0] == 'y') {
        for (int i = index + 1; i < DB.count; ++i) {
            DB.data[i - 1] = DB.data[i];
        }
        --DB.count;
    }
    std::cout<<"Contact succesfully deleted!"<<std::endl;
}
