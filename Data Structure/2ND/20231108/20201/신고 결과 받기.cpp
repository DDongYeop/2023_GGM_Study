#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k)
{
	int index;
	string str1, str2;
	vector<int> result(id_list.size());
	unordered_map<string, tuple<int, int, unordered_set<string>>> um;

	for (int i = 0; i < id_list.size(); ++i)
		um.insert(make_pair(id_list[i], make_tuple(i, 0, unordered_set<string>())));

	for (string str : report)
	{
		stringstream ss(str);
		ss >> str1 >> str2;
		if (get<2>(um[str1]).find(str2) == get<2>(um[str1]).end())
		{
			get<2>(um[str1]).insert(str2);
			get<1>(um[str2])++;
		}
	}

	for (auto p : um)
	{
		index = 0;
		for (auto s : get<2>(p.second))
		{
			if (get<1>(um[s]) >= k)
				++index;
		}
		result[get<0>(p.second)] = index;
	}

	return result;
}
