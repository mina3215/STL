
// enum ������ : ���� ������ ������� ����
enum Color {
	RED,
	BLACK
};

class Node {
public:
	int data;
	Node* left = nullptr;
	Node* right = nullptr;

	// BST�� �ٸ��� parent�� color�� �ִ�.
	Node* parent = nullptr;
	Color color = BLACK;
};


class RedBlackTree {
private:
	Node* root = nullptr;
public:
	//����
	void leftRotate(Node* node);
	void rightRotate(Node* node);
	void Change_Tree(Node* node);
	void Insert_Node(Node* tree, Node* node);
	void Insert_Case5(Node* node);

	//����
	Node* sibling(Node* node);
	void Replace_Node(Node* node, Node* child);
	void Delete_one_child(Node* node);
	void Delete_Case1(Node* node);
	void Delete_Case2(Node* node);
	void Delete_Case3(Node* node);
	void Delete_Case4(Node* node);
	void Delete_Case5(Node* node);
	void Delete_Case6(Node* node);

	//����, �ҸӴ� ��� ã��
	Node* uncle(Node* node);
	Node* grandparent(Node* node);

};

Node* nil;

void RedBlackTree::leftRotate(Node* node) {
	if (node == nil || nil == node->right) return;
	Node* temp = node->right;
	// ���� ������ ����Ʈ���� ������ ���� ��� ������ ����Ʈ����
	// �ű� ����Ʈ���� �θ� �ٲ���
	node->right = node->right->left;
	if (nil != node->right) node->right->parent = node;
	// ������ ���� ����
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

	//case 1. ���� ��Ʈ ���
	if (node->parent == nullptr) {
		node->color = BLACK;
		root = node;
	}
	// case 2. �� �θ� ��尡 ������ -> ���� ����
	else if (node->parent && node->parent->color == BLACK) {
		return;
	}
	//case 3. �θ� ���� ���� ��尡 ��� ������
	// 1) P, U�� ���������� ����
	// 2) G�� ���������� ���� -> 2��,4�� �Ӽ��� �������� �ʴ´ٸ�
	// 3) ��������� �۾�.
	else if (u && u->color == RED) {
		node->parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(node);
		g->color = RED;
		//���θ� ���� root ������ ����Ѵ�. ����Ʈ�� ��ü�� ���Խ�Ű�µ�.
		Change_Tree(g);
	}
	//case 4. P: ������+G�� ���� �ڽ�, U: ������ 
	// N: P�� ������ �ڽ� 
	// N�� P�� ������ �����ؾ� �Ѵ�.(���� ȸ��) 
	// �θ� ��� ���� P�� case5���� ó���Ѵ�. -> 4���� �Ӽ� 
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
	//case 5. P : ������, U : ������ 
	// N : P�� ���� �ڽ� ���, P : G�� ���� �ڽ� ���
	// ������ ȸ��
}

//���� ��带 ã�´�. 
Node* RedBlackTree::sibling(Node* node) {
	if (node == node->parent->left) {
		return node->parent->right;
	}
	else
		return node->parent->left;
}

//������� �Ǻ�
int is_leaf(Node* node) {
	if (node->parent && !node->right && !node->left)
		return 1;
	else
		return 0;
}

void RedBlackTree::Replace_Node(Node* node, Node* child) {
	// �տ��� n�� �θ� NULL�� �Ǵ� ��츦 DELETE_CASE�� ���� �ʰ� �̸� ó�����ش�. 
	// child? 
	child->parent = node->parent;
	if (node->parent && node->parent->left == node)
		node->parent->left = child;
	if (node->parent && node->parent->right == node)
		node->parent->right = child;
}

// CASE1 ��Ʈ����� ���ٰ� ����. 
void RedBlackTree::Delete_Case1(Node* node) {
	if (node->parent != nullptr)
		Delete_Case2(node);
}


//CASE 2��.
void RedBlackTree::Delete_Case2(Node* node) {
	//node�� ������ ����� �ڽ�. 
	// ������ ����� �ڽ��� ������ 
	Node* s = sibling(node);

	//RED�̸�
	if (s->color == RED) {
		// ������ ����� �θ� ��� ������ RED�� �ٲ��ش�.
		node->parent->color = RED;
		// ������ ������ BLACK
		s->color = BLACK;
		// �״�� ȸ��. 
		if (node == node->parent->left)
			leftRotate(node->parent);
		else
			rightRotate(node->parent);
	}

	Delete_Case3(node);

}
//CASE3. P,S �׸��� S�� �ڽĵ��� ���� ���, �츮�� ������ S�� �������� ĥ�Ѵ�. 
// �� ���, S�� ������ ��� ��ε��� �ϳ��� ������带 ���� ���� �ְ� ��
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
//  S�� S�� �ڽĵ��� ������������, P�� ������ ���. 
// �ܼ��� S�� P�� ���� �ٲٸ� �ȴ�.
void RedBlackTree::Delete_Case4(Node* node) {
	Node* s = sibling(node);
	// P�� RED. ���� = BLACK, ������ �ڽĵ��� BLACK.
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
		//������ Node�� �θ� ��� ������ �ڽ��� ������ �ڽ����� �α� ����. 
		// Ȥ�� Node�� �θ� ��� ���� �ڽ��� ���� �ڽ����� �α� ����.->case 6����
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



// n�� �ִ� �ϳ��� non-null �ڽ��� ���� �ִ�. 
void RedBlackTree::Delete_one_child(Node* node) {
	//��������� child�� ã�Ƽ� �ִ´�. 
	//�� �� non-leaf��� node->right.
	Node* child = is_leaf(node->right) ? node->left : node->right;
	//�켱, parent���� node�� �ִ� �ڸ��� node�� child�� �ִ´�.
	Replace_Node(node, child);
	//������ ��尡 BLACK�̸�
	// 1) child�� RED�� ��� BLACK���� �����Ѵ�. (5�� ����)
	if (node->color == BLACK) {
		if (child->color == RED)
			child->color = BLACK;
		// 2) child�� BLACK�̸� 5�� ������ ���߱� ���� �������� ����. 
		else {
			Delete_Case1(child);
		}
	}
	//free(node);
}



void RedBlackTree::Insert_Node(Node* tree, Node* node) {

	// ������ ���� �����Ѵ�.
	node->right = nil;
	node->left = nil;
	node->color = RED;
	//����Ž��Ʈ�� ���� ����
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