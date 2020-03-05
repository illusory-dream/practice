#include "func.h"
#include <utility>
#include <Windows.h>
using namespace std;
//�ж��ĸ�TreeNode*��Ӧ��int��С�����ҳ���ǰȨֵ��С�������������ɹ�������
unordered_map<TreeNode*, int>::const_iterator myMin(const unordered_map<TreeNode*, int>& count)
{
	auto min = count.cbegin();
	for (auto it = min; it != count.cend(); ++it)
	{
		if (it->second < min->second)
		{
			min = it;
		}
	}
	return min;
}
//���ɹ�������
TreeNode* huffman(const vector<char>& vec)
{
	unordered_map<char, int> num;
	unordered_map<TreeNode*, int> count;
	for (auto c : vec)
	{
		++num[c];
	}
	for (const auto &it : num)
	{
		count[new TreeNode(it.first)] = it.second;
	}
	while (count.size() > 1)
	{
		int power = 0;
		TreeNode* root = new TreeNode('\0');
		auto treeA = myMin(count);
		power += treeA->second;
		root->left = treeA->first;
		count.erase(treeA);

		auto treeB = myMin(count);
		power += treeB->second;
		root->right = treeB->first;
		count.erase(treeB);
		count[root] = power;
	}
	return count.cbegin()->first;
}
//�ݹ�������������ɱ����ֵ����Ҫ����
void preOrder(TreeNode* tn, vector<char> code, unordered_map<char, vector<char>> &codLst)
{
	if (tn)
	{
		if (!tn->left && !tn->right)
		{
			codLst[tn->c] = code;
			delete tn;
			return;
		}
		code.push_back('0');
		preOrder(tn->left, code, codLst);
		code.back() = '1';
		preOrder(tn->right, code, codLst);
		delete tn;
	}
}
//��������->�����ֵ�
unordered_map<char, vector<char>> treeToCode(TreeNode* tn)
{
	unordered_map<char, vector<char>> ret;
	preOrder(tn, vector<char>(), ret);
	return ret;
}

unordered_map<char, std::vector<char>> init(istream& is)
{
	vector<char> cvec;
	int val;
	while ((val = is.get()) != -1)
	{
		char c = val;
		cvec.push_back(c);
	}
	TreeNode* root = huffman(cvec);
	return treeToCode(root);
}

void coding(istream& is, ostream& os, const unordered_map<char, vector<char>>& lst)
{
	int sz = 0;

	char bit = 0;
	int count = 0;
	int val;
	while ((val = is.get()) != -1)
	{
		char c = val;
		vector<char> cvec = lst.at(c);
		for (auto ch : cvec)
		{
			bit <<= 1;
			bit += ('1' == ch) ? 1 : 0;
			++count;
			if (8 == count)
			{
				os << bit;
				bit = 0;
				count = 0;

				++sz;
				if (sz >= 1024 && 0 == sz % 1024)
				{
					cout << "\r\t\t\t�Ѵ���" << (sz / 1024) << "KB";
				}
			}
		}
	}
	if (count != 0)
	{
		bit <<= (8 - count);
		os << bit;
	}
}

void decoding(istream& is, ostream& os, const unordered_map<char, vector<char>>& lst)
{
	int sz = 0;

	map<vector<char>, char> reverseLst;
	for (const auto& it : lst)
	{
		reverseLst[it.second] = it.first;
	}
	vector<char> word;
	int val;
	while ((val = is.get()) != -1)
	{
		char c = val;
		int count = 0;
		while (count != 8)
		{
			word.push_back((c >> 7) ? '1' : '0');
			c <<= 1;
			++count;
			if (reverseLst.count(word))
			{
				os << reverseLst[word];
				word.clear();
			}
		}

		++sz;
		if (sz >= 1024 && 0 == sz % 1024)
		{
			cout << "\r\t\t\t�Ѵ���" << (sz / 1024) << "KB";
		}
	}
}

void saveDict(ostream& os, const unordered_map<char, vector<char>>& lst)
{
	for (const auto& it : lst)
	{
		os << static_cast<int>(it.first) << " ";
		for (auto c : it.second)
		{
			os << c;
		}
		os << endl;
	}
}

unordered_map<char, vector<char>> loadDict(istream& is)
{
	unordered_map<char, vector<char>> lst;
	int c;
	while (is >> c)
	{
		string code;
		is >> code;
		lst[static_cast<char>(c)] = vector<char>(code.cbegin(), code.cend());
	}
	return lst;
}

void tips()
{
	cout << "-c \"Դ�ļ�\" \"Ŀ���ļ�\" \"�ֵ��ļ�Ҫ��ŵ�λ��\"\t���ã������ļ�" << endl;
	cout << "-d \"Դ�ļ�\" \"Ŀ���ļ�\" \"�ֵ��ļ�\"\t���ã������ļ�" << endl;
	cout << "-e �˳�" << endl;
	cout << "for example: -c srce.txt dest.txt dict.txt" << endl;
}

void userCoding(const std::string& srce, const std::string& dest, const std::string& dict)
{
	long long t = GetTickCount64();
	ifstream huffmanSrce(srce, ios::binary);
	cout << "�������ɱ���...";
	auto lst = init(huffmanSrce);
	cout << "\t\t���--��ʱ:" << (GetTickCount64() - t) << "ms" << endl; t = GetTickCount64();
	ifstream ifs(srce, ios::binary);
	ofstream ofs(dest, ios::binary);
	cout << "���ڽ��б���..." << endl;
	coding(ifs, ofs, lst);
	cout << "\r\t\t\t���--��ʱ:" << (GetTickCount64() - t) << "ms" << endl; t = GetTickCount64();
	ofstream outDict(dict);
	cout << "���ڴ�ӡ�����ֵ�...";
	saveDict(outDict, lst);
	cout << "\t���--��ʱ:" << (GetTickCount64() - t) << "ms" << endl; t = GetTickCount64();
	huffmanSrce.close(); ifs.close(); ofs.close(); outDict.close();
}

void userDecoding(const std::string& srce, const std::string& dest, const std::string& dict)
{
	long long t = GetTickCount64();
	ifstream inDict(dict);
	cout << "���ڶ�ȡ�����ֵ�...";
	auto lst = loadDict(inDict);
	cout << "\t���--��ʱ:" << (GetTickCount64() - t) << "ms" << endl; t = GetTickCount64();
	ifstream ifs(srce, ios::binary);
	ofstream ofs(dest, ios::binary);
	cout << "���ڽ���..." << endl;
	decoding(ifs, ofs, lst);
	cout << "\r\t\t\t���--��ʱ:" << (GetTickCount64() - t) << "ms" << endl;
	inDict.close(); ifs.close(); ofs.close();
}
//����ȷ�ĸ�ʽ�����ļ���
void loadFilename(istream& is, string& str)
{
	is >> str;
	if ('\"' == str.front())
	{
		string tmp;
		while (str.back() != '\"')
		{
			is >> tmp;
			str += " " + tmp;
		}
		str.pop_back();
		str.erase(str.begin());
	}
}

void run()
{
	string cmd, srce, dest, dict;
	tips();
	cout << ">>";
	while (cin >> cmd)
	{
		if ("-c" == cmd)
		{
			loadFilename(cin, srce);
			loadFilename(cin, dest);
			loadFilename(cin, dict);
			userCoding(srce, dest, dict);
		}
		else if ("-d" == cmd)
		{
			loadFilename(cin, srce);
			loadFilename(cin, dest);
			loadFilename(cin, dict);
			userDecoding(srce, dest, dict);
		}
		else if ("-e" == cmd)
		{
			cout << "bye" << endl;
			break;
		}
		else
		{
			cout << "wrong command" << endl;
		}
		std::cin.ignore(INT_MAX, '\n');
		cout << ">>";
	}
}