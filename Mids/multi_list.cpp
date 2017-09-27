#include <iostream>
#include <fstream>

using namespace std;

int N = 10;

struct student_list {
    int stud_no, pos;
};

struct class_list {
    char class_no;
    int pos;
};


struct student {
    int stud_no, stud_fwd, stud_back, class_forward, class_back;
    char class_no;
};

void add()
{
    student dummy, temp;
    class_list sb;
    student_list st;
    cout<<"\nEnter roll number: ";
    cin>>dummy.stud_no;
    cout<<"\nEnter course name: ";
    cin>>dummy.class_no;
    dummy.stud_fwd = -1;
    dummy.stud_back = -1;
    dummy.class_forward = -1;
    dummy.class_back = -1;

    int stud_flag = 0, sfirstpos;
    fstream f;
    f.open("students.bin", ios::in|ios::binary);
    while(f.read((char*)&st, sizeof(st)))
    {
        if(st.stud_no == dummy.stud_no)
        {
            sfirstpos = st.pos; 
            stud_flag = 1;
            break;
        }
    }
    f.close();

    int class_flag = 0, cfirstpos;
    f.open("class.bin", ios::in|ios::binary);
    while(f.read((char*)&sb, sizeof(sb)))
    {
        if(sb.class_no == dummy.class_no)
        {
            cfirstpos = sb.pos; 
            class_flag = 1;
            break;
        }
    }
    f.close();

        if(stud_flag == 0)
        {
            st.stud_no = dummy.stud_no;
            st.pos = N;
            f.open("students.bin", ios::out|ios::app|ios::in|ios::binary);
            f.write((char*)&st, sizeof(st));
            f.close();

            f.open("main.bin", ios::binary|ios::out|ios::app|ios::in);
            f.write((char*)&dummy, sizeof(dummy));
            f.close();
        }

        if(class_flag == 0)
        {
            sb.class_no = dummy.class_no;
            sb.pos = N;
            f.open("class.bin", ios::out|ios::app|ios::binary);
            f.write((char*)&sb, sizeof(sb));
            f.close();
        }

        if(stud_flag == 1)
        {
            f.open("main.bin", ios::binary|ios::out|ios::ate|ios::in);
            f.seekg(sfirstpos*sizeof(dummy), ios::beg);
            f.seekp(sfirstpos*sizeof(dummy), ios::beg);
            
            while(f.read((char*)&temp, sizeof(temp)))
            {
                if(temp.stud_fwd == -1)
                {
                    temp.stud_fwd = N;
                    f.write((char*)&temp, sizeof(temp));
                    break;
                }
                else
                {
                    f.seekg(temp.stud_fwd*sizeof(dummy), ios::beg);
                    f.seekp(temp.stud_fwd*sizeof(dummy), ios::beg);                 
                }
            }
            f.close();
        }

        if(class_flag == 1)
        {
            f.open("main.bin", ios::binary|ios::out|ios::ate|ios::in);
            f.seekg(cfirstpos*sizeof(dummy), ios::beg);
            f.seekp(cfirstpos*sizeof(dummy), ios::beg);
            
            while(f.read((char*)&temp, sizeof(temp)))
            {
                if(temp.class_forward == -1)
                {
                    temp.class_forward = N;
                    f.write((char*)&temp, sizeof(temp));
                    break;
                }
                else
                {
                    f.seekg(temp.class_forward*sizeof(dummy), ios::beg);
                    f.seekp(temp.class_forward*sizeof(dummy), ios::beg);                    
                }
            }
            f.close();
        }
    }


void search(char course1, char course2)
{
    student s;
    student_list d1;
    class_list d2;
    int class_flag = 0, cfirstpos, sfirstpos;
    fstream f;
    f.open("class.bin", ios::in|ios::binary);
    while(f.read((char*)&d2, sizeof(d2)))
    {
        if(d2.class_no == course1)
        {
            cfirstpos = d2.pos; 
            class_flag = 1;
            break;
        }
    }
    f.close();
    if(class_flag == 0)
        cout<<"Course Doesn't Exist\n";
    else 
    {
        cout<<cfirstpos<<endl;y
        f.open("main.bin", ios::binary|ios::out|ios::ate|ios::in);
        f.seekg(cfirstpos*sizeof(s), ios::beg);
        f.seekp(cfirstpos*sizeof(s), ios::beg);
        f.read((char*)&s, sizeof(s));
        int stud_no = s.stud_no;
        f.close();
        int stud_flag = 0, sfirstpos;
        f.open("students.bin", ios::in|ios::binary);
        while(f.read((char*)&d1, sizeof(d1)))
        {
            if(d1.stud_no == stud_no)
            {
                sfirstpos = d1.pos; 
                stud_flag = 1;
                break;
            }
        }
        f.close();
        if(stud_flag == 0)
            cout<<"Student Not Found\n";
        else 
        {
            f.open("main.bin", ios::binary|ios::out|ios::ate|ios::in);
            f.seekg(sfirstpos*sizeof(s), ios::beg);
            f.seekp(sfirstpos*sizeof(s), ios::beg);
            int class_pointer = s.class_forward;
            while(class_pointer != -1)
            {
                int stud_pointer = sfirstpos;
                while(stud_pointer != -1)
                {
                    stud_pointer = s.stud_fwd;
                    if(stud_pointer == -1)
                        break;
                    f.seekg(stud_pointer*sizeof(s), ios::beg);
                    f.seekp(stud_pointer*sizeof(s), ios::beg);
                    f.read((char*)&s, sizeof(s));
                    if(s.class_no == course2)
                    {
                        cout<<"Student "<<s.stud_no<<" has taken both the courses"<<endl;
                        break;
                    }
                }
                f.seekg(sfirstpos*sizeof(s), ios::beg);
                f.seekp(sfirstpos*sizeof(s), ios::beg);
                class_pointer = s.class_forward;
                if(class_pointer == -1)
                    break;
                f.seekg(class_pointer*sizeof(s), ios::beg);
                f.seekp(class_pointer*sizeof(s), ios::beg);
                sfirstpos = class_pointer;
            }
            f.close();
        }
    }
}

int main()
{
    int ans = 0, num;
    while(ans != 3)
    {
        cout<<"\n\n1. Add\n2. Search Course\n3. Exit\nEnter choice: ";
        cin>>ans;
        if(ans == 1)
            add();
        if(ans == 2)
        {
            char a, b;
            cout<<"Enter Course1 & Course2 : ";
            cin>>a>>b;
            search(a, b);   
        }
    }
    return 0;
}   