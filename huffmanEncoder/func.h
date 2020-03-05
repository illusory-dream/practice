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

//初始化：使用输入数据生成哈夫曼树，并使用哈夫曼树生成编码字典
std::unordered_map<char, std::vector<char>> init(std::istream&);
//读取原始文件，编码并写入新文件
void coding(std::istream&, std::ostream&, const std::unordered_map<char, std::vector<char>>&);
//读取编码后的文件，解码并写入新文件
void decoding(std::istream&, std::ostream&, const std::unordered_map<char, std::vector<char>>&);
//存储字典
void saveDict(std::ostream&, const std::unordered_map<char, std::vector<char>>&);
//读取字典
std::unordered_map<char, std::vector<char>> loadDict(std::istream&);
//显示提示信息
void help();
//coding界面
void userCoding(const std::string&, const std::string&, const std::string&);
//decoding界面
void userDecoding(const std::string&, const std::string&, const std::string&);
//入口
void run();