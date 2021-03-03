#include "mydatabase.h"
#include "mydabase.cpp"
#include <ctime>
int menu() {
    for (int i = 0; i < 20; ++i)
        std::cout << '*';
    std::cout << std::endl;
    std::cout << "1. Add record" << std::endl;
    std::cout << "2. Delete record" << std::endl;
    std::cout << "3. Export database" << std::endl;
    std::cout << "4. Sorting by surname" << std::endl;
    std::cout << "5. Sorting by date of birth" << std::endl;
    std::cout << "6. Sorting by days until birthday" << std::endl;
    std::cout << "7. Find by surname" << std::endl;
    std::cout << "8. Find by phone number" << std::endl;
    std::cout << "0. Exit" << std::endl;
    int tmp;
    std::cin >> tmp;
    std::cin.ignore();
    return tmp;
}

int main()
{
    DataBase DB;
    DB.count= 0;
    DB.data = nullptr;
    int action;
    do {
        action = menu();
        switch (action) {
	        case 1: addRecord(DB); break;
	        case 2: deleteRecord(DB); break;
	        case 3: exportDB(DB); break;
	        case 4: sortsurname(DB); break;
	        case 5: sortbirth(DB); break;
	        case 6: sortdays(DB); break;
	        case 7: findbs(DB); break;
	        case 8: findbpn(DB); break;
        }
    } while (action != 0);

    // free memory
    if (DB.data)
        delete[] DB.data;

    return 0;
}
