#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>

struct TreeNode {
	char c;
	TreeNode* left, * right;
	TreeNode(char ch) :c(ch), left(nullptr), right(nullptr) {}
};

//��ʼ����ʹ�������������ɹ�����������ʹ�ù����������ɱ����ֵ�
std::unordered_map<char, std::vector<char>> init(std::istream&);
//��ȡԭʼ�ļ������벢д�����ļ�
void coding(std::istream&, std::ostream&, const std::unordered_map<char, std::vector<char>>&);
//��ȡ�������ļ������벢д�����ļ�
void decoding(std::istream&, std::ostream&, const std::unordered_map<char, std::vector<char>>&);
//�洢�ֵ�
void saveDict(std::ostream&, const std::unordered_map<char, std::vector<char>>&);
//��ȡ�ֵ�
std::unordered_map<char, std::vector<char>> loadDict(std::istream&);
//��ʾ��ʾ��Ϣ
void help();
//coding����
void userCoding(const std::string&, const std::string&, const std::string&);
//decoding����
void userDecoding(const std::string&, const std::string&, const std::string&);
//���
void run();