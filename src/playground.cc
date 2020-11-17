#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class MySpecialPipe {
    private:
        char delimiter;
    public:
        vector<string> buffer;
        MySpecialPipe(char delimeter);
        friend istream& operator>> (istream &in, MySpecialPipe &p);
        friend istream& operator>> (MySpecialPipe &p, istream &in);
};

MySpecialPipe::MySpecialPipe(char delimeter): delimiter(delimeter) {}

istream& operator>> (istream &in,  MySpecialPipe &p)
{
    string s;
    while (getline(in, s, p.delimiter)) {
        p.buffer.push_back(s);
    }

    return in;
}

istream& operator>> (MySpecialPipe &p, istream &in) {
    for (string s: p.buffer) {
        // s >> in;
    }
    p.buffer.clear();
    return in;
}

int main() {
    MySpecialPipe p = MySpecialPipe(',');
    stringstream ss("1,2.2");
    stringstream ss2;
}
