#include<iostream>
#include<fstream>
using namespace std;

class User {
private:
    int Calgoal;
    int CalConsumed,CalConsumedPre;
public:
    User(int CG) : CalConsumed(0),CalConsumedPre(0) {}

    void addCal(int c) {
        CalConsumed += c;
    }
    void setPrevious(int c) {
        CalConsumedPre = c;
    }

    void setToday(int c) {
        CalConsumed = c;
    }

    int getToday()
    {return CalConsumed;}

    void show(bool sp) {
        cout << "Calories Goal = " << Calgoal << endl;
        if(sp)
        {
            cout << "Previous Calories = " << CalConsumedPre << endl;
        }
        cout << "Calories Consumed (Today) = " << CalConsumed << endl;
        CalConsumedPre=CalConsumed;
    }
};

class File {
    private:
    bool loaded;
    public:
    File () : loaded (false) {}
    void loadData(User &u)
    {
        ifstream file("calories.txt");

        if(file.is_open())
        {
            int val;
            file>>val;
            u.setPrevious(val);
            loaded=true;
            file.close();
        }
        else
        {
            u.setPrevious(0);
            loaded=false;
        }
    }
    void saveData(User &u)
    {
        ofstream file("calories.txt");

        if(file.is_open())
        {
            file<<u.getToday();
            file.close();
        }
    }
    bool isloaded()
    {
        return loaded;
    }

};

int main() {
    int goal;

    cout << "Enter your calorie goal: ";
    cin >> goal;

    User U(goal);
    File F;
    char choice;
    int cal;
    cout << "Enter calories Consumed today: ";
    cin >> cal;
    cout << "Load previous calories? (y/n): ";
    cin >> choice;
    bool sp=false; //show previous
    if (choice == 'y' || choice == 'Y') {
        F.loadData(U);
        sp=true;
    }
    U.addCal(cal);
    U.show(sp);
    F.saveData(U);

    system("pause");
}
