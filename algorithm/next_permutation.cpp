#include<iostream>
#include<iterator>
#include<algorithm>

using namespace std;

int arr[] = { 1,2,3,4 };

template <class BidirectionalIterator>
bool next_permutation1(BidirectionalIterator* first, BidirectionalIterator* last) {
	if (first == last) return false; //원소가 하나도 없다.
	//[)
	BidirectionalIterator* i = last;

	//시작과 끝이 같다 => 한칸짜리 순열이다.
	if (first == --i) return false;

	for (;;) {
		BidirectionalIterator *i1, *i2;
		i1 = i; // 마지막을 i1에 넣어준다.

		// --i는 이전 것 i는 현재의 것.
		if (*--i < *i1) { // 오름차순이면?
			i2 = last; // i2 = last를 넣어준다.
			while (!(*i < *--i2)); //last가 --i2보다 크면(오름차순이면) 끝, 끝에서부터 A[k]<A[h]를 만족하는 h 탐색
			std::iter_swap(i, i2); // swap 둘의 위치 변경.
			//std::reverse(i1, last); // 내림차순을 정렬된 부분 수열을 오름차순으로 만들어준다.
			return true;
		}
		//완전 내림 차순
		if (i == first) {
			std::reverse(first, last);
			return false; // 더이상 없다.
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
