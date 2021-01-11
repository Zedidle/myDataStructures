#define MAXSIZE 1000





namespace StaticList {

	template <typename T>
	class StaticList {
		struct Node {
			T data;
			int cur;
		};
		int size;
		Node StaticLinkList;

	public:
		StaticList(int s): size(s){
		}




	};







	void Test() {
		StaticList<int> sList = StaticList<int>(MAXSIZE);
	}
}
