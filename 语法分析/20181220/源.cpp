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
//终结符
string endchar[10] = { "or","and","not","(",")", "id","rop", "true","false","#" };
//产生式
string chanshengshi[8] = { "E","E or E","E and E","not E","( E )","id rop id","true", "false" };
//goto
int gotoformat[16] = { 1, 0, 0, 0,
				 8,10,11,12,
				 0, 0, 0, 0,
				 0 ,0, 0, 0
};



void printfuhao(stack<int> statestac)//输出栈内的所有元素
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
	string inputstr;//布尔表达式
	stack<int> statestac;//状态栈
	stack<string> symbolstac;//符号栈
public:
	//构造函数
	buildlr() :step(0), inputstr(" ")
	{}
	//初始化两个栈
	void initialstack()
	{
		statestac.push(0);
		symbolstac.push("#");
	}
	//输出函数
	void printmore(int str1, stack<int> state, stack<string> symbol, string str4, string str5)
	{
		cout << setw(5) << str1;
		printfuhao(state);
		printbiaozhi(symbol);
		cout << setw(30) << str4;
		cout << setw(32) << str5 << endl;
	}
	//初始函数
	void initstageInfo()
	{
		cout << "布尔表达式如下：" << endl;
		cout << "S -> E" << endl;
		cout << "E -> E or E" << endl;
		cout << "E -> E and E" << endl;
		cout << "E -> T or F" << endl;
		cout << "E -> not E" << endl;
		cout << "E -> ( E )" << endl;
		cout << "E -> id rop id" << endl;
		cout << "E -> true" << endl;
		cout << "E -> false \n" << endl;
		cout << "最初布尔表达式目录为E:\\example.txt。\n" << endl;
		cout << "从中读取之后经过词法分析保存到E:\\data.txt。\n" << endl;
		cout << "本次语法分析从E:\\example.txtt提取词法分析后的结果。接下来开始语法分析。\n" << endl;

	}
	//初始输入布尔表达式
	void initInputstr()
	{
		cout << "正在从文件读取表达式词法分析后的结果\n" << endl;
		ifstream fin("E:\\data.txt");
		getline(fin, inputstr);
		while (inputstr[inputstr.length() - 1] != '#')
		{
			inputstr = inputstr.substr(0, inputstr.length() - 1);
		}cout << "读取完毕\n" << endl;
		cout << "分析后的字符串为" << inputstr << endl << endl;
	}

	//将终结符和非终结符转换为action和gotol表中对应的数字
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
	//判断字符为终结符
	bool judgeend(string str)
	{
		for (int i = 0; i < 10; i++)
		{
			if (endchar[i] == str)
				return true;
		}
		return false;
	}
	//计算字符串中元素的个数，方便后面运算
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
	//将字符串按空格分开存入数组中。
	vector<string> fenkaijuzi(string str)
	{
		vector<string> separatedstring;
		int stat = 0;
		int i = 0;
		while (i < str.size())
		{
			if (isspace(str[i]))//如果空格
			{
				separatedstring.push_back(str.substr(stat, i - stat));//复制长度为i-pos的字符串。
				stat = i + 1;
			}
			++i;
		}
		separatedstring.push_back(str.substr(stat, str.size() - stat));
		return separatedstring;
	}
	//将vector容器中的字符串连起来
	string connectvec(vector<string> &vecs, vector<string>::iterator iter)
	{
		string str = " ";
		vector<string>::iterator it;//迭代器进行遍历
		it = iter;
		for (it; it < vecs.end(); it++)
		{
			str += *it;
		}
		return str;
	}

	void Start()//开始函数.
	{
		initstageInfo();
		initialstack();//初始化
		initInputstr();
		vector<string> vec = fenkaijuzi(inputstr);//分开布尔表达式
		vector<string>::iterator iter = vec.begin();
		cout << "LR分析法的过程如下" << endl;
		cout << setw(6) << setiosflags(ios_base::left) << "步骤";
		cout << setw(30) << setiosflags(ios_base::left) << "状态栈";
		cout << setw(30) << setiosflags(ios_base::left) << "符号栈";
		cout << setw(30) << setiosflags(ios_base::left) << "输入串";
		cout << setw(10) << setiosflags(ios_base::left) << "操作" << endl;
		for (iter; iter != vec.end(); ++iter)//依次遍历字符
		{
			string str1 = connectvec(vec, iter);
			actionGoto(*iter, str1);
		}
	}
	//LR分析函数
	void actionGoto(string str, string str1)
	{
		int x = statestac.top();//当前栈顶状态
		int y = stringtonum(str);//当前将要输入的字符
		if (action[x][y] > 0 && judgeend(str) && (str != "#"))//移进
		{
			printmore(step, statestac, symbolstac, str1, "移入" + str);
			statestac.push(action[x][y]);
			symbolstac.push(str);
			++step;
		}
		if (action[x][y] < 0 && judgeend(str))//规约
		{
			int z = -action[x][y];//用-action[x][y]对应的产生式规约
			string lenstr = chanshengshi[z];//生成需要规约的产生式
			int n = calculatenum(lenstr);//计算产生式的长度，进行规约
			string ch = "E";//生成规约后的非终结符
			printmore(step, statestac, symbolstac, str1, "规约" + ch + "->" + chanshengshi[z]);
			for (int i = 0; i < n; i++)
			{
				statestac.pop();
			}
			for (int i = 0; i < n; i++)
			{
				symbolstac.pop();
			}
			int m = statestac.top();//获取规约后的栈顶状态
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
			printmore(step, statestac, symbolstac, str1, "分析完成");
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