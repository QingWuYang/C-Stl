
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

//ѡ����
class Speaker
{
public:
	string m_name;
	int m_score[3];
};

//����ѡ��
int GenSpeaker(map<int, Speaker> &mapSpeaker, vector<int> &v1)
{
	string str = "abcdefghijklmnopqrstuvwxyz";
	random_shuffle(str.begin(), str.end());

	for (int i = 0; i < 24; i++)
	{
		Speaker temp;
		temp.m_name = "ѡ��";
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

//ѡ�ֳ�ǩ
int speach_contest_draw(vector<int> &v1)
{
	random_shuffle(v1.begin(), v1.end());
	return 0;
}

//ѡ�ֱ���
int speach_contest(int index, vector<int> &v1, map<int, Speaker> &mapSpeaker, vector<int> &v2)
{
	int groupCount = 0;//С����Ŀ
	//С��ı����ķּ�¼,���ǰ���� ������
	multimap<int, int, greater<int>> multimapGruopScore;
	int tempCount = 0;
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		tempCount++;
		//���
		
		{
			deque<int> dscore;
			for (int j = 0; j < 10; j++)
			{
				int score = 50 + rand() % 50;
				dscore.push_back(score);
			}
			sort(dscore.begin(), dscore.end());//�ķ�����
			dscore.pop_back();
			dscore.pop_front();//ȡ����߷ֺ���ͷ�
			//��ƽ����
			int total_score = accumulate(dscore.begin(), dscore.end(), 0);
			int average_score = total_score / dscore.size();

			//ѡ�ֵķַŽ�������*it��ѡ�ֱ��
			mapSpeaker[*it].m_score[index] = average_score;
			//С��ķ�
			multimapGruopScore.insert(pair<int, int>(average_score, *it));
		}
		//�������
		if (tempCount % 6 == 0)
		{
			groupCount++;
			cout << "��"<< groupCount <<"С��ı����ɼ���" << endl;
			for (multimap<int, int, greater<int>>::iterator it2 = multimapGruopScore.begin(); it2 != multimapGruopScore.end(); it2++)
			{
				cout << it2->second << "\t" << mapSpeaker[it2->second].m_name << "\t" << it2->first ;
				cout << endl;
			}
			cout << endl;
			//ǰ��������
			while (multimapGruopScore.size() > 3)
			{
				multimap<int, int, greater<int>>::iterator it3 = multimapGruopScore.begin();
				v2.push_back(it3->second);//��ǰ�����ŵ�v2����������
				multimapGruopScore.erase(it3);
			}
			multimapGruopScore.clear();
		}
		
		
	}
	return 0;
}

//�鿴�������
int speach_contest_print(int index, vector<int> &v2, map<int, Speaker> &mapSpeaker)
{
	cout << "��" << index + 1 << "��������:" << endl;
	for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
	{
		cout << "�������: " << *it << "\t" << mapSpeaker[*it].m_name << "\t" << mapSpeaker[*it].m_score[index] << endl;
	}
	return 0;
}

void main()
{
	//int a[4] = { 0 };
	map<int, Speaker> mapSpeaker;//�μӱ�����ѡ��
	vector<int> v1;//��һ���ݽ���������
	vector<int> v2;//�ڶ����ݽ���������
	vector<int> v3;//�������ݽ���������
	vector<int> v4;//�������ݽ���������
	
	//����ѡ�֣��õ���һ��ѡ�ֱ�������
	GenSpeaker(mapSpeaker, v1);

	//��һ�� ѡ�ֳ�ǩ ѡ�ֱ��� �鿴�������
	cout << "\n\n\n���������ʼ��һ�ֱ���" << endl;
	cin.get();
	speach_contest_draw(v1);
	speach_contest(0, v1,mapSpeaker,v2);
	speach_contest_print(0, v2, mapSpeaker);

	//�ڶ��� ѡ�ֳ�ǩ ѡ�ֱ��� �鿴�������
	cout << "\n\n\n���������ʼ�ڶ��ֱ���" << endl;
	cin.get();
	speach_contest_draw(v2);
	speach_contest(1, v2, mapSpeaker, v3);
	speach_contest_print(1, v3, mapSpeaker);

	//������ ѡ�ֳ�ǩ ѡ�ֱ��� �鿴�������
	cout << "\n\n\n���������ʼ�����ֱ���" << endl;
	cin.get();
	speach_contest_draw(v3);
	speach_contest(2, v3, mapSpeaker, v4);
	speach_contest_print(2, v4, mapSpeaker);

	cout << "hello.." << endl;
	system("pause");
}
