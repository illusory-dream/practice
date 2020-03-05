#include "func.h"
using namespace std;

int main()
{
	cout << "²åÈëÅÅÐò>>   "; test(insertSort);
	cout << "Ï£¶ûÅÅÐò>>   "; test(shellSort);
	cout << "Ã°ÅÝÅÅÐò>>   "; test(bubbleSort);
	cout << "¿ìËÙÅÅÐò>>   "; test(quickSort);
	cout << "Ñ¡ÔñÅÅÐò>>   "; test(selectSort);
	cout << "¶Ñ ÅÅ Ðò>>   "; test(heapSort);
	cout << "¹é²¢ÅÅÐò>>   "; test(mergeSort);
	cout << "»ùÊýÅÅÐò>>   "; test(radixSort);
	return 0;
}