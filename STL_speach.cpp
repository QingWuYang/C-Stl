
#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<list>
#include<set>
#include<map>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>

//选手类
class Speaker
{
public:
	string m_name;
	int m_score[3];
};

//产生选手
int GenSpeaker(map<int, Speaker> &mapSpeaker, vector<int> &v1)
{
	string str = "abcdefghijklmnopqrstuvwxyz";
	random_shuffle(str.begin(), str.end());

	for (int i = 0; i < 24; i++)
	{
		Speaker temp;
		temp.m_name = "选手";
		temp.m_name = temp.m_name + str[i];
		*temp.m_score = { 0 };
		mapSpeaker.insert(pair<int, Speaker>(100 + i, temp));
	}
	for (int i = 0; i < 24; i++)
	{
		v1.push_back(100 + i);
	}
	return 0;
}

//选手抽签
int speach_contest_draw(vector<int> &v1)
{
	random_shuffle(v1.begin(), v1.end());
	return 0;
}

//选手比赛
int speach_contest(int index, vector<int> &v1, map<int, Speaker> &mapSpeaker, vector<int> &v2)
{
	int groupCount = 0;//小组数目
	//小组的比赛的分记录,求出前三名 后三名
	multimap<int, int, greater<int>> multimapGruopScore;
	int tempCount = 0;
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		tempCount++;
		//打分
		
		{
			deque<int> dscore;
			for (int j = 0; j < 10; j++)
			{
				int score = 50 + rand() % 50;
				dscore.push_back(score);
			}
			sort(dscore.begin(), dscore.end());//的分排序
			dscore.pop_back();
			dscore.pop_front();//取出最高分和最低分
			//求平均分
			int total_score = accumulate(dscore.begin(), dscore.end(), 0);
			int average_score = total_score / dscore.size();

			//选手的分放进容器中*it是选手编号
			mapSpeaker[*it].m_score[index] = average_score;
			//小组的分
			multimapGruopScore.insert(pair<int, int>(average_score, *it));
		}
		//处理分组
		if (tempCount % 6 == 0)
		{
			groupCount++;
			cout << "第"<< groupCount <<"小组的比赛成绩：" << endl;
			for (multimap<int, int, greater<int>>::iterator it2 = multimapGruopScore.begin(); it2 != multimapGruopScore.end(); it2++)
			{
				cout << it2->second << "\t" << mapSpeaker[it2->second].m_name << "\t" << it2->first ;
				cout << endl;
			}
			cout << endl;
			//前三名晋级
			while (multimapGruopScore.size() > 3)
			{
				multimap<int, int, greater<int>>::iterator it3 = multimapGruopScore.begin();
				v2.push_back(it3->second);//把前三名放到v2晋级名单中
				multimapGruopScore.erase(it3);
			}
			multimapGruopScore.clear();
		}
		
		
	}
	return 0;
}

//查看比赛结果
int speach_contest_print(int index, vector<int> &v2, map<int, Speaker> &mapSpeaker)
{
	cout << "第" << index + 1 << "晋级名单:" << endl;
	for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
	{
		cout << "参赛编号: " << *it << "\t" << mapSpeaker[*it].m_name << "\t" << mapSpeaker[*it].m_score[index] << endl;
	}
	return 0;
}

void main()
{
	//int a[4] = { 0 };
	map<int, Speaker> mapSpeaker;//参加比赛的选手
	vector<int> v1;//第一轮演讲比赛名单
	vector<int> v2;//第二轮演讲比赛名单
	vector<int> v3;//第三轮演讲比赛名单
	vector<int> v4;//第四轮演讲比赛名单
	
	//产生选手，得到第一轮选手比赛名单
	GenSpeaker(mapSpeaker, v1);

	//第一轮 选手抽签 选手比赛 查看比赛结果
	cout << "\n\n\n任意键，开始第一轮比赛" << endl;
	cin.get();
	speach_contest_draw(v1);
	speach_contest(0, v1,mapSpeaker,v2);
	speach_contest_print(0, v2, mapSpeaker);

	//第二轮 选手抽签 选手比赛 查看比赛结果
	cout << "\n\n\n任意键，开始第二轮比赛" << endl;
	cin.get();
	speach_contest_draw(v2);
	speach_contest(1, v2, mapSpeaker, v3);
	speach_contest_print(1, v3, mapSpeaker);

	//第三轮 选手抽签 选手比赛 查看比赛结果
	cout << "\n\n\n任意键，开始第三轮比赛" << endl;
	cin.get();
	speach_contest_draw(v3);
	speach_contest(2, v3, mapSpeaker, v4);
	speach_contest_print(2, v4, mapSpeaker);

	cout << "hello.." << endl;
	system("pause");
}
