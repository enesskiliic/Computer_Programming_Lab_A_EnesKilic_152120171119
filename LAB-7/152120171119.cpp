#include <iostream>
#include <fstream>
using namespace std;

struct Sensor 
{
    int sensor_id;
    float sicaklik;

};

int main()
{
    long ID;
    cout << "Enter your student ID: ";
    cin >> ID;
    int N = ID % 50;
    int E = ID % 100;

    
    fstream file("sensors.bin", ios::binary | ios::in | ios::out);
    file.seekg(N* sizeof(Sensor), ios::beg);
    Sensor temp;
    file.read(reinterpret_cast<char*>(&temp), sizeof(Sensor));
    float first = temp.sicaklik;
    temp.sicaklik += E;
    file.seekp(N* sizeof(Sensor), ios::beg);
    file.write(reinterpret_cast<char*>(&temp), sizeof(Sensor));
    file.close();

    ofstream txt("152120171119_Quiz5.txt", ios::out);
    txt << "Number [" << ID << "]" << endl;
    txt << "Sensor Index Used in the Process: [" << N << "]" << endl;
    txt << "First Temperature [" << first << "] -> New Temperature: [" << temp.sicaklik << "]" << endl;
    txt.close();
}