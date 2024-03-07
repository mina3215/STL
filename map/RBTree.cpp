
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
	//삽입
	void leftRotate(Node* node);
	void rightRotate(Node* node);
	void Change_Tree(Node* node);
	void Insert_Node(Node* tree, Node* node);
	void Insert_Case5(Node* node);

	//삭제
	Node* sibling(Node* node);
	void Replace_Node(Node* node, Node* child);
	void Delete_one_child(Node* node);
	void Delete_Case1(Node* node);
	void Delete_Case2(Node* node);
	void Delete_Case3(Node* node);
	void Delete_Case4(Node* node);
	void Delete_Case5(Node* node);
	void Delete_Case6(Node* node);

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


Node* RedBlackTree::grandparent(Node* node) {
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

void RedBlackTree::Insert_Case5(Node* node) {
	Node* g = grandparent(node);
	node->parent->color = BLACK;
	g->color = RED;
	if (node == node->parent->left)
		rightRotate(g);
	else
		leftRotate(g);
}

void RedBlackTree::Change_Tree(Node* node) {
	Node* u = uncle(node), * g;

	//case 1. 내가 루트 노드
	if (node->parent == nullptr) {
		node->color = BLACK;
		root = node;
	}
	// case 2. 내 부모 노드가 검은색 -> 조건 만족
	else if (node->parent && node->parent->color == BLACK) {
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
	else if ((node == node->parent->right) && (node->parent == g->left)) {
		leftRotate(node->parent);
		node = node->left;
		Insert_Case5(node);
	}
	else if ((node == node->parent->left) && (node->parent == g->right)) {
		rightRotate(node->parent);
		node = node->right;
		Insert_Case5(node);
	}
	//case 5. P : 붉은색, U : 검은색 
	// N : P의 왼쪽 자식 노드, P : G의 왼쪽 자식 노드
	// 오른쪽 회전
}

//형제 노드를 찾는다. 
Node* RedBlackTree::sibling(Node* node) {
	if (node == node->parent->left) {
		return node->parent->right;
	}
	else
		return node->parent->left;
}

//리프노드 판별
int is_leaf(Node* node) {
	if (node->parent && !node->right && !node->left)
		return 1;
	else
		return 0;
}

void RedBlackTree::Replace_Node(Node* node, Node* child) {
	// 앞에서 n의 부모가 NULL이 되는 경우를 DELETE_CASE에 오지 않게 미리 처리해준다. 
	// child? 
	child->parent = node->parent;
	if (node->parent && node->parent->left == node)
		node->parent->left = child;
	if (node->parent && node->parent->right == node)
		node->parent->right = child;
}

// CASE1 루트노드라면 해줄게 없다. 
void RedBlackTree::Delete_Case1(Node* node) {
	if (node->parent != nullptr)
		Delete_Case2(node);
}


//CASE 2임.
void RedBlackTree::Delete_Case2(Node* node) {
	//node는 삭제할 노드의 자식. 
	// 삭제할 노드의 자식의 형제가 
	Node* s = sibling(node);

	//RED이면
	if (s->color == RED) {
		// 삭제할 노드의 부모 노드 색상을 RED로 바꿔준다.
		node->parent->color = RED;
		// 형제의 색상은 BLACK
		s->color = BLACK;
		// 그대로 회전. 
		if (node == node->parent->left)
			leftRotate(node->parent);
		else
			rightRotate(node->parent);
	}

	Delete_Case3(node);

}
//CASE3. P,S 그리고 S의 자식들이 검은 경우, 우리는 간단히 S를 빨강으로 칠한다. 
// 그 결과, S를 지나는 모든 경로들은 하나의 검은노드를 적게 갖고 있게 됨
void RedBlackTree::Delete_Case3(Node* node) {
	Node* s = sibling(node);

	if ((node->parent->color == BLACK) &&
		(s->color == BLACK) &&
		(s->left->color == BLACK) &&
		(s->right->color == BLACK)) {
		s->color = RED;
		Delete_Case1(node->parent);
	}
	else
		Delete_Case4(node);
}
//  S와 S의 자식들은 검은색이지만, P는 빨강인 경우. 
// 단순히 S와 P의 색을 바꾸면 된다.
void RedBlackTree::Delete_Case4(Node* node) {
	Node* s = sibling(node);
	// P는 RED. 형제 = BLACK, 형제의 자식들은 BLACK.
	if ((node->parent->color == RED) &&
		(s->color == BLACK) &&
		(s->left->color == BLACK) &&
		(s->right->color == BLACK)) {
		s->color = RED;
		node->parent->color = BLACK;
	}
	else
		Delete_Case5(node);
}

void RedBlackTree::Delete_Case5(Node* node) {
	Node* s = sibling(node);
	if (s->color == BLACK) {
		//빨강을 Node의 부모 노드 오른쪽 자식의 오른쪽 자식으로 두기 위함. 
		// 혹은 Node의 부모 노드 왼쪽 자식의 왼쪽 자식으로 두기 위함.->case 6으로
		if ((node == node->parent->left) &&
			(s->right->color == BLACK) &&
			(s->left->color == RED)) {
			s->color = RED;
			s->left->color = BLACK;
			rightRotate(s);
		}
		else if ((node == node->parent->right) &&
			(s->left->color == BLACK) &&
			(s->right->color == RED)) {
			s->color = RED;
			s->right->color = BLACK;
			leftRotate(s);
		}
	}
	Delete_Case6(node);

}

void RedBlackTree::Delete_Case6(Node* node) {
	Node* s = sibling(node);

	s->color = node->parent->color;
	node->parent->color = BLACK;

	if (node == node->parent->left) {
		s->right->color = BLACK;
		leftRotate(node->parent);
	}
	else {
		s->left->color = BLACK;
		rightRotate(node->parent);
	}
}



// n이 최대 하나의 non-null 자식을 갖고 있다. 
void RedBlackTree::Delete_one_child(Node* node) {
	//리프노드인 child를 찾아서 넣는다. 
	//둘 다 non-leaf라면 node->right.
	Node* child = is_leaf(node->right) ? node->left : node->right;
	//우선, parent에서 node가 있는 자리에 node의 child를 넣는다.
	Replace_Node(node, child);
	//삭제할 노드가 BLACK이면
	// 1) child가 RED인 경우 BLACK으로 변경한다. (5번 조건)
	if (node->color == BLACK) {
		if (child->color == RED)
			child->color = BLACK;
		// 2) child가 BLACK이면 5번 조건을 맞추기 위한 재조정에 들어간다. 
		else {
			Delete_Case1(child);
		}
	}
	//free(node);
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