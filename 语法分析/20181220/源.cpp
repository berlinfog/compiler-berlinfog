#include<iostream>
#include<string>
#include<vector>
#include<iomanip> 
#include<stack>
#include<fstream>
using namespace std;
//action
int action[16][10] = {
	 { 0	, 0	 ,4	,5	, 0	 ,9	, 0	, 2 , 3	, 0},//0
	 { 6	, 7	 ,0	,0	, 0	 ,0	, 0	, 0	, 0	,100},//1
	 {-6	,-6	 ,0 ,0	, -6 ,0, 0  , 0 , 0 ,-6},//2
	 {-7	,-7	 ,0 ,0  , -7 ,0, 0  , 0 , 0 ,-7},//3
	 { 0	, 0	 ,4	,5	, 0	 ,9	, 0	, 2	, 3	, 0},//4
	 { 0	, 0	 ,4	,5	, 0	 ,9	, 0	, 2	, 3	, 0},//5
	 { 0	, 0	 ,4	,5	, 0	 ,9	, 0	, 2	, 3	, 0},//6
	 { 0	, 0	 ,4	,5	, 0	 ,9	, 0	, 2	, 3	, 0},//7
	 {-3	,-3	 ,0 ,0  ,-3 ,0 ,0	, 0 , 0 , -3},//8 
	 { 0	, 0	 ,0	,0	, 0	 ,0	, 13, 0	, 0	,  0},//9
	 { 6	, 7	 ,0	,0	, 15 ,0	, 0	, 0	, 0	,  0},//10
	 { -1   , 7	 ,0 ,0  ,-1  ,0 , 0	,0	,0  , -1},//11
	 {-2	,-2	 ,0 ,0  , -2 ,0 ,0	,0	,0  , -2},//12 
	 { 0	, 0	 ,0	,0  , 0  ,14,0	, 0	, 0	,  0},//13
	 {-5	,-5	 ,0 ,0  , -5 ,0 ,0	,0	,0  , -5},//14 
	 {-4	,-4	 ,0 ,0  , -4 ,0 ,0	,0	,0  , -4}//15 
};
//�ս��
string endchar[10] = { "or","and","not","(",")", "id","rop", "true","false","#" };
//����ʽ
string chanshengshi[8] = { "E","E or E","E and E","not E","( E )","id rop id","true", "false" };
//goto
int gotoformat[16] = { 1, 0, 0, 0,
				 8,10,11,12,
				 0, 0, 0, 0,
				 0 ,0, 0, 0
};



void printfuhao(stack<int> statestac)//���ջ�ڵ�����Ԫ��
{
	string str = " ";
	while (!statestac.empty())
	{
		char ch1 = (statestac.top() / 10) + 48;
		char ch2 = (statestac.top() % 10) + 48;
		statestac.pop();
		str += ch1;
		str += ch2;
	}
	cout << setw(30) << str;
}
void printbiaozhi(stack<string> symbolstac)
{
	string str = " ";
	while (!symbolstac.empty())
	{
		str += symbolstac.top();
		symbolstac.pop();
	}
	cout << setw(30) << str;
}
class buildlr
{
private:
	int step;
	string inputstr;//�������ʽ
	stack<int> statestac;//״̬ջ
	stack<string> symbolstac;//����ջ
public:
	//���캯��
	buildlr() :step(0), inputstr(" ")
	{}
	//��ʼ������ջ
	void initialstack()
	{
		statestac.push(0);
		symbolstac.push("#");
	}
	//�������
	void printmore(int str1, stack<int> state, stack<string> symbol, string str4, string str5)
	{
		cout << setw(5) << str1;
		printfuhao(state);
		printbiaozhi(symbol);
		cout << setw(30) << str4;
		cout << setw(32) << str5 << endl;
	}
	//��ʼ����
	void initstageInfo()
	{
		cout << "�������ʽ���£�" << endl;
		cout << "S -> E" << endl;
		cout << "E -> E or E" << endl;
		cout << "E -> E and E" << endl;
		cout << "E -> T or F" << endl;
		cout << "E -> not E" << endl;
		cout << "E -> ( E )" << endl;
		cout << "E -> id rop id" << endl;
		cout << "E -> true" << endl;
		cout << "E -> false \n" << endl;
		cout << "����������ʽĿ¼ΪE:\\example.txt��\n" << endl;
		cout << "���ж�ȡ֮�󾭹��ʷ��������浽E:\\data.txt��\n" << endl;
		cout << "�����﷨������E:\\example.txtt��ȡ�ʷ�������Ľ������������ʼ�﷨������\n" << endl;

	}
	//��ʼ���벼�����ʽ
	void initInputstr()
	{
		cout << "���ڴ��ļ���ȡ���ʽ�ʷ�������Ľ��\n" << endl;
		ifstream fin("E:\\data.txt");
		getline(fin, inputstr);
		while (inputstr[inputstr.length() - 1] != '#')
		{
			inputstr = inputstr.substr(0, inputstr.length() - 1);
		}cout << "��ȡ���\n" << endl;
		cout << "��������ַ���Ϊ" << inputstr << endl << endl;
	}

	//���ս���ͷ��ս��ת��Ϊaction��gotol���ж�Ӧ������
	int stringtonum(string str)
	{
		if (str == "or")
			return 0;
		if (str == "and")
			return 1;
		if (str == "not")
			return 2;
		if (str == "(")
			return 3;
		if (str == ")")
			return 4;
		if (str == "id")
			return 5;
		if (str == "rop")
			return 6;
		if (str == "true")
			return 7;
		if (str == "false")
			return 8;
		if (str == "#")
			return 9;
		if (str == "E")
			return 0;
	}
	//�ж��ַ�Ϊ�ս��
	bool judgeend(string str)
	{
		for (int i = 0; i < 10; i++)
		{
			if (endchar[i] == str)
				return true;
		}
		return false;
	}
	//�����ַ�����Ԫ�صĸ����������������
	int calculatenum(string str)
	{
		int num = 0;
		for (int i = 0; i < str.size(); ++i)
		{
			if (isgraph(str[i]))
				continue;
			else
			{
				++num;
			}
		}
		++num;
		return num;
	}
	//���ַ������ո�ֿ����������С�
	vector<string> fenkaijuzi(string str)
	{
		vector<string> separatedstring;
		int stat = 0;
		int i = 0;
		while (i < str.size())
		{
			if (isspace(str[i]))//����ո�
			{
				separatedstring.push_back(str.substr(stat, i - stat));//���Ƴ���Ϊi-pos���ַ�����
				stat = i + 1;
			}
			++i;
		}
		separatedstring.push_back(str.substr(stat, str.size() - stat));
		return separatedstring;
	}
	//��vector�����е��ַ���������
	string connectvec(vector<string> &vecs, vector<string>::iterator iter)
	{
		string str = " ";
		vector<string>::iterator it;//���������б���
		it = iter;
		for (it; it < vecs.end(); it++)
		{
			str += *it;
		}
		return str;
	}

	void Start()//��ʼ����.
	{
		initstageInfo();
		initialstack();//��ʼ��
		initInputstr();
		vector<string> vec = fenkaijuzi(inputstr);//�ֿ��������ʽ
		vector<string>::iterator iter = vec.begin();
		cout << "LR�������Ĺ�������" << endl;
		cout << setw(6) << setiosflags(ios_base::left) << "����";
		cout << setw(30) << setiosflags(ios_base::left) << "״̬ջ";
		cout << setw(30) << setiosflags(ios_base::left) << "����ջ";
		cout << setw(30) << setiosflags(ios_base::left) << "���봮";
		cout << setw(10) << setiosflags(ios_base::left) << "����" << endl;
		for (iter; iter != vec.end(); ++iter)//���α����ַ�
		{
			string str1 = connectvec(vec, iter);
			actionGoto(*iter, str1);
		}
	}
	//LR��������
	void actionGoto(string str, string str1)
	{
		int x = statestac.top();//��ǰջ��״̬
		int y = stringtonum(str);//��ǰ��Ҫ������ַ�
		if (action[x][y] > 0 && judgeend(str) && (str != "#"))//�ƽ�
		{
			printmore(step, statestac, symbolstac, str1, "����" + str);
			statestac.push(action[x][y]);
			symbolstac.push(str);
			++step;
		}
		if (action[x][y] < 0 && judgeend(str))//��Լ
		{
			int z = -action[x][y];//��-action[x][y]��Ӧ�Ĳ���ʽ��Լ
			string lenstr = chanshengshi[z];//������Ҫ��Լ�Ĳ���ʽ
			int n = calculatenum(lenstr);//�������ʽ�ĳ��ȣ����й�Լ
			string ch = "E";//���ɹ�Լ��ķ��ս��
			printmore(step, statestac, symbolstac, str1, "��Լ" + ch + "->" + chanshengshi[z]);
			for (int i = 0; i < n; i++)
			{
				statestac.pop();
			}
			for (int i = 0; i < n; i++)
			{
				symbolstac.pop();
			}
			int m = statestac.top();//��ȡ��Լ���ջ��״̬
			if (gotoformat[m] > 0)
			{
				int g = gotoformat[m];
				statestac.push(g);
				symbolstac.push(ch);
			}
			++step;
			actionGoto(str, str1);
		}
		if ((action[x][y] == 100) && (str == "#"))
		{
			printmore(step, statestac, symbolstac, str1, "�������");
		}
	}
};
int main()
{
	buildlr lirunlong = buildlr();
	lirunlong.Start();

	system("pause");
	return 0;
}