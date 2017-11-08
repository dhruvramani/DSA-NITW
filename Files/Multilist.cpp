#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N = 10;

bool done(int k1, int k2)
{
	for(int i = 0; i < already.size(); i++)
		if(already[i].first == k1 && already[i].second == k2)
			return true;

	return false;
}

struct stud_list {
	int sno, pos;
};

struct sub_list {
	char cno;
	int pos;
};

class student {
	int sno, sfwd, sbck, cfwd, cbck;
	char cno;

public:
	void fill()
	{
		fstream f;
		student temp;
		temp.sno = 0;
		temp.cno = '\0';
		temp.sfwd = -1;
		temp.sbck = -1;
		temp.cfwd = -1;
		temp.cbck = -1;

		f.open("info.bin", ios::binary|ios::out);
		for(int i = 0; i < N; i++)
			f.write((char*)&temp, sizeof(temp));
		f.close();
	}

	void display()
	{
		if(sno > 0)
		{
			cout<<"\nRoll number: "<<sno;
			cout<<"\nCourse name: "<<cno;
		}
	}

	void read()
	{
		student dummy, temp;
		sub_list sb;
		stud_list st;
		cout<<"\nEnter roll number: ";
		cin>>dummy.sno;
		cout<<"\nEnter course name: ";
		cin>>dummy.cno;
		dummy.sfwd = -1;
		dummy.sbck = -1;
		dummy.cfwd = -1;
		dummy.cbck = -1;

		int sflag = 0, sfirstpos;
		fstream f;
		f.open("students.bin", ios::in|ios::binary);
		while(f.read((char*)&st, sizeof(st)))
		{
			if(st.sno == dummy.sno)
			{
				sfirstpos = st.pos; 
				sflag = 1;
			}
		}
		f.close();

		int cflag = 0, cfirstpos;
		f.open("courses.bin", ios::in|ios::binary);
		while(f.read((char*)&sb, sizeof(sb)))
		{
			if(sb.cno == dummy.cno)
			{
				cfirstpos = sb.pos; 
				cflag = 1;
			}
		}
		f.close();

		if(sflag == 0)
		{
			st.sno = dummy.sno;
			st.pos = N;
			f.open("students.bin", ios::out|ios::app|ios::in|ios::binary);
			f.write((char*)&st, sizeof(st));
			f.close();

			f.open("info.bin", ios::binary|ios::out|ios::app|ios::in);
			f.write((char*)&dummy, sizeof(dummy));
			f.close();
		}

		if(cflag == 0)
		{
			sb.cno = dummy.cno;
			sb.pos = N;
			f.open("courses.bin", ios::out|ios::app|ios::binary);
			f.write((char*)&sb, sizeof(sb));
			f.close();
		}

		if(sflag == 1)
		{
			f.open("info.bin", ios::binary|ios::out|ios::ate|ios::in);
			f.seekg(sfirstpos*sizeof(dummy), ios::beg);
			f.seekp(sfirstpos*sizeof(dummy), ios::beg);
			
			while(f.read((char*)&temp, sizeof(temp)))
			{
				if(temp.sfwd == -1)
				{
					temp.sfwd = N;
					f.write((char*)&temp, sizeof(temp));
					break;
				}
				else
				{
					f.seekg(temp.sfwd*sizeof(dummy), ios::beg);
					f.seekp(temp.sfwd*sizeof(dummy), ios::beg);					
				}
			}
			f.close();
		}

		if(cflag == 1)
		{
			f.open("info.bin", ios::binary|ios::out|ios::ate|ios::in);
			f.seekg(cfirstpos*sizeof(dummy), ios::beg);
			f.seekp(cfirstpos*sizeof(dummy), ios::beg);
			
			while(f.read((char*)&temp, sizeof(temp)))
			{
				if(temp.cfwd == -1)
				{
					temp.cfwd = N;
					f.write((char*)&temp, sizeof(temp));
					break;
				}
				else
				{
					f.seekg(temp.cfwd*sizeof(dummy), ios::beg);
					f.seekp(temp.cfwd*sizeof(dummy), ios::beg);					
				}
			}
			f.close();
		}
	}

};


int main()
{
	int ans, num;
	student dummy;
	
	while(1)
	{
		cout<<"\n\n1. Add\n2. Display all\n3. Exit\nEnter choice: ";
		cin>>ans;
		
		if(ans == 100)
			dummy.fill();
		else if(ans == 1)
			dummy.read();
		else if(ans == 2)
		{
			already.clear();
			fstream f;
			f.open("info.bin", ios::in|ios::binary);
			while(f.read((char*)&dummy, sizeof(dummy)))
				dummy.display();
			f.close();
		}
		else
			exit(0);
	}
	
	return 0;
}
