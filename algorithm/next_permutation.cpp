#include<iostream>
#include<iterator>
#include<algorithm>

using namespace std;

int arr[] = { 1,2,3,4 };

template <class BidirectionalIterator>
bool next_permutation1(BidirectionalIterator* first, BidirectionalIterator* last) {
	if (first == last) return false; //���Ұ� �ϳ��� ����.
	//[)
	BidirectionalIterator* i = last;

	//���۰� ���� ���� => ��ĭ¥�� �����̴�.
	if (first == --i) return false;

	for (;;) {
		BidirectionalIterator *i1, *i2;
		i1 = i; // �������� i1�� �־��ش�.

		// --i�� ���� �� i�� ������ ��.
		if (*--i < *i1) { // ���������̸�?
			i2 = last; // i2 = last�� �־��ش�.
			while (!(*i < *--i2)); //last�� --i2���� ũ��(���������̸�) ��, ���������� A[k]<A[h]�� �����ϴ� h Ž��
			std::iter_swap(i, i2); // swap ���� ��ġ ����.
			//std::reverse(i1, last); // ���������� ���ĵ� �κ� ������ ������������ ������ش�.
			return true;
		}
		//���� ���� ����
		if (i == first) {
			std::reverse(first, last);
			return false; // ���̻� ����.
		}
	}
}

int main() {
	do {
		for (int i = 0;i < 4;i++) {
			cout << arr[i] << ' ';
		}
		cout << '\n';
	}while(next_permutation1(arr, arr + 4));
}
