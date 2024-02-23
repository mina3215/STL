
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
	void leftRotate(Node* node);
	void rightRotate(Node* node);
	void Change_Tree(Node* node);
	void Insert_Node(Node* tree, Node* node);
	void Case5(Node* node);

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

	//case 1. ���� ��Ʈ ���
	if (node->parent == nullptr) {
		node->color = BLACK;
		root = node;
	}
	// case 2. �� �θ� ��尡 ������ -> ���� ����
	else if (node->parent&&node->parent->color == BLACK) {
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
	//case 5. P : ������, U : ������ 
	// N : P�� ���� �ڽ� ���, P : G�� ���� �ڽ� ���
	// ������ ȸ��
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