#include<iostream>
#include<fstream>
#include<map>

using namespace std;

class IP
{
	public:
		map<string,string>companyNum;
		map<string,map<string,int> >Company;//IP--company---num of this company
		void InsertIp(string ip, string company, bool flag);
		void Traverse();
		IP()
		{
			MAX = 0;
			Name = "";
		}
		int MAX;
		string Name;
};

void IP::InsertIp(string ip, string company, bool flag)
{
	typedef map<string, int> Map1;
	if(0 == flag)
	{
		MAX = 0;
	}
	Map1 M;
	Company.insert(make_pair(ip,M));
	//Company[ip].insert(make_pair(ip,company));	
	if(++Company[ip][company] > MAX && Company[ip][company] > 2)
	{
		MAX = Company[ip][company];
		Name = company;
		companyNum[ip] = company;
	}	

}
void IP::Traverse()
{
	cout << "Traverse\n";
	for(map<string, string>::iterator iter=companyNum.begin(); iter!=companyNum.end();++iter)
	{
		cout << iter->first << "\t" << iter->second << endl;
	}
}

IP ip;

void ReadFile(char *infile)
{
	ifstream in(infile);
	string buffer;
	string preIp="";
	bool flag;// 标志是否与下一行ip相同
	while(getline(in,buffer))
	{
		int pos = buffer.find("\t");
		if( preIp == buffer.substr(0,pos)) flag = 1;
		else flag = 0;
		ip.InsertIp(buffer.substr(0,pos),buffer.substr(pos+1,buffer.length()-pos-1),flag);
		preIp = buffer.substr(0,pos);
	}
}

int main(int argc, char *argv[])
{

	if(argc <2)
	{
		cout << "need ip---company file" << endl;
		return 0;
	}
	//IP ip;
	ReadFile(argv[1]);
	ip.Traverse();
	return 0;
}
