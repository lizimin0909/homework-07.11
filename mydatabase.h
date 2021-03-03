#ifndef __MYDATABASE_2020__
#define __MYDATABASE_2020__
#include <iostream>

struct student {
    char surname[32];
    char name[16];
    char phone[16];
    char mail[32];
    char brthd[12];
};

struct DataBase {
    int count;
    student* data;
};

std::ostream& operator << (std::ostream& out, const student& st);
std::istream& operator >> (std::istream& in, student& st);

bool operator < (const student& left, const student& right);
bool compByBirth(const student& left, const student& right);
bool compBySurname(const student& left, const student& right);
bool compByDayMon(const student& left, const student& right);

int addRecord(DataBase& DB);
int findRecord(const DataBase& DB);
int findbs(const DataBase& DB);
int findbpn(const DataBase& DB);
void deleteRecord(DataBase& DB);

void saveDB(const DataBase& DB);
void exportDB(const DataBase& DB);
void sortsurname(DataBase& DB);
void sortbirth(DataBase& DB);
void sortdays(DataBase& DB);


template <typename T>
void MySort(T* M, int n, bool (*comparator)(const T&, const T&)) {
    for (int j = 0; j < n - 1; ++j) {
        int k = j; // индекс минимального элемента
        for (int i = k + 1; i < n; ++i) {
            if (comparator(M[i], M[k]))  // M[i] < M[k]
                k = i;
        }
        if (j < k) {
            std::swap(M[k], M[j]);
        }
    }
}
#endif
