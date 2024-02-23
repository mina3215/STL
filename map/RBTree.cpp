
// enum 열거형 : 서로 연관된 상수들의 집합
enum Color {
	RED,
	BLACK
};

class Node {
public:
	int data;
	Node* left = nullptr;
	Node* right = nullptr;
	
	// BST와 다르게 parent와 color가 있다.
	Node* parent = nullptr;
	Color color = BLACK;
};


class RedBlackTree {
private:
	Node* root = nullptr;
public: 
	void leftRotate(Node* node);
	void rightRotate(Node* node);
	void Change_Tree(Node* node);
	void Insert_Node(Node* tree, Node* node);
	void Case5(Node* node);

	//삼촌, 할머니 노드 찾음
	Node* uncle(Node* node);
	Node* grandparent(Node* node);

};

Node* nil;

void RedBlackTree::leftRotate(Node* node) {
	if (node == nil || nil == node->right) return;
	Node* temp = node->right;
	// 기존 오른쪽 서브트리의 왼쪽을 기준 노드 오른쪽 서브트리로
	// 옮긴 서브트리의 부모도 바꿔줌
	node->right = node->right->left;
	if (nil != node->right) node->right->parent = node;
	// 왼쪽을 기준 노드로
	temp->left = node;
	temp->parent = node->parent;
	if (nullptr != node->parent) {
		if (node->parent->left == node)
			node->parent->left = temp;
		else
			node->parent->right = temp;
	}
	node->parent = temp;
	if (root == node)
		root = temp;
}

void RedBlackTree::rightRotate(Node* node) {
	if (node == nil || node->left == nil) return;
	Node* temp = node->left;
	node->left = node->left->right;
	if (nil != node->left) node->left->parent = node;
	temp->right = node;
	temp->parent = node->parent;
	if (nullptr != node->parent) {
		if (node->parent->right == node)
			node->parent->right = temp;
		else
			node->parent->left = temp;
	}
	node->parent = temp;
	if (root = node)
		root = temp;

}


Node* RedBlackTree::grandparent(Node * node) {
	if ((node) && node->parent != nullptr) {
		return node->parent->parent;
	}
	else
		return nullptr;
}
Node* RedBlackTree::uncle(Node* node) {
	Node* g = grandparent(node);
	if (g == nullptr)
		return nullptr;
	else
		return node->parent == g->left ? g->right : g->left;
}

void RedBlackTree::Case5(Node* node) {
	Node* g = grandparent(node);
	node->parent->color = BLACK;
	g->color = RED;
	if (node == node->parent->left)
		rightRotate(g);
	else
		leftRotate(g);
}

void RedBlackTree::Change_Tree(Node* node) {
	Node* u = uncle(node), *g;

	//case 1. 내가 루트 노드
	if (node->parent == nullptr) {
		node->color = BLACK;
		root = node;
	}
	// case 2. 내 부모 노드가 검은색 -> 조건 만족
	else if (node->parent&&node->parent->color == BLACK) {
		return;
	}
	//case 3. 부모 노드와 삼촌 노드가 모드 붉은색
	// 1) P, U를 검은색으로 변경
	// 2) G를 붉은색으로 변경 -> 2번,4번 속성을 만족하지 않는다면
	// 3) 재귀적으로 작업.
	else if (u && u->color == RED) {
		node->parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(node);
		g->color = RED;
		//조부모에 대한 root 연산을 계속한다. 서브트리 자체를 삽입시키는듯.
		Change_Tree(g);
	}
	//case 4. P: 붉은색+G의 왼쪽 자식, U: 검은색 
	// N: P의 오른쪽 자식 
	// N과 P의 역할을 변경해야 한다.(왼쪽 회전) 
	// 부모 노드 였던 P는 case5에서 처리한다. -> 4번쨰 속성 
	//  
	else if((node==node->parent->right)&&(node->parent==g->left)){
		leftRotate(node->parent);
		node = node->left;
		Case5(node);
	}
	else if ((node == node->parent->left) && (node->parent == g->right)) {
		rightRotate(node->parent);
		node = node->right;
		Case5(node);
	}
	//case 5. P : 붉은색, U : 검은색 
	// N : P의 왼쪽 자식 노드, P : G의 왼쪽 자식 노드
	// 오른쪽 회전
}



void RedBlackTree::Insert_Node(Node* tree, Node* node) {

	// 빨간색 노드로 시작한다.
	node->right = nil;
	node->left = nil;
	node->color = RED; 
	//이진탐색트리 삽입 로직
	if (node->data < tree->data) {
		if (tree->left == nil) {
			tree->left = node;
			node->parent = tree;
		}
		else {
			Insert_Node(tree->left, node);
		}
	}
	if (node->data > tree->data) {
		if (tree->right == nil) {
			tree->right = node;
			node->parent = tree;
		}
		else {
			Insert_Node(tree->right, node);
		}
	}
	
}