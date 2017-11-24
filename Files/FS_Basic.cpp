#include <fstream>

struct node
{
    int key;
    int data;
    int fwd;
    int bkwd;
};

void init(int n)
{
    fstream f;
    f.open("file.dat", ios::binary | ios::out);
    node a = {-1, -1, -1, -1};
    for(int i=0; i<n; i++)
        f.write((char*)&a, sizeof(a));
    f.close();
}

// Opening File
f.open("filename.txt", ios::in); // ios::binary, ios::app, ios::out

// Reading 
f.read((char*)&node, sizeof(node));
f>>chara; //  Takes space as delimeter - can put int, double, string
f.get(chara); // Can put same as above
f.getline(string, strlen, 'delimeter'); 

// Writing
f.write((char*)&node, sizeof(node));
f<<dummy;

// To move the pointer
// seekg - input mode, seekp - output mode
f.seekg(pos*sizeof(node), ios::curr); // ios::curr, ios::beg, ios::end