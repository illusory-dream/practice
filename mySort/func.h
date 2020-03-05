#pragma once
#include <iostream>
#include <vector>

void insertSort(std::vector<int>&);
void shellSort(std::vector<int>&);

void bubbleSort(std::vector<int>&);
void quickSort(std::vector<int>&);

void selectSort(std::vector<int>&);
void heapSort(std::vector<int>&);

void mergeSort(std::vector<int>&);
void radixSort(std::vector<int>&);	//only positive number

void test(void(*)(std::vector<int>&));