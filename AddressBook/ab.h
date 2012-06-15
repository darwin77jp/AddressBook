// ab.h 
#include <string>
using namespace std;
/*
data structure of person
@param name
@param mobile
@param address
@param process for each feature
*/
class Person{
public:
    string name;
    string mobile;
    string address;
    Person(void){}
    void menu();
    void add();
    void search();
    void remove();
    static void reading(void);
    static void file_read(void);

private:
    void adding();
    void file_write();

};
