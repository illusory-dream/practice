#include "func.h"
using namespace std;

int main()
{
	cout << "��������>>   "; test(insertSort);
	cout << "ϣ������>>   "; test(shellSort);
	cout << "ð������>>   "; test(bubbleSort);
	cout << "��������>>   "; test(quickSort);
	cout << "ѡ������>>   "; test(selectSort);
	cout << "�� �� ��>>   "; test(heapSort);
	cout << "�鲢����>>   "; test(mergeSort);
	cout << "��������>>   "; test(radixSort);
	return 0;
}