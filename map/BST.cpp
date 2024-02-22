class Node {
public:
	int data;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(int _data, Node* _left, Node* _right)
		:data(_data),left(_left),right(_right){}
};

// Ž��
bool BST_SearchNode(Node* tree, int target) {
	if (tree == nullptr) return false;

	if (tree->data == target) return true;
	else if (tree->data > target) return BST_SearchNode(tree->left, target);
	else if (tree->data < target) return BST_SearchNode(tree->right, target);
}

/*
Node* BST_SearchNode(Node* tree, int target) {
	if (tree == nullptr) return nullptr;
	if (tree->data == target) return tree;
	else if (tree->data > target) return BST_SearchNode(tree->left, target);
	else if (tree->data < target) return BST_SearchNode(tree->right, target);
}
*/

//���� (���� ��� �ܰ� ���� Ʈ���� ��Ʈ, ������ ���)
void BST_InsertNode(Node* tree, Node* node) {
	//��Ʈ ��尡 ������ ���� ũ�� -> �������� 
	if (node->data < tree->data) {
		//�ٵ� ���� ��尡 ���� ? ���� ��忡 �߰������ �Ѵ�.
		if (tree->left == nullptr) {
			tree->left = node;
			return;
		}
		else {
			BST_InsertNode(tree->left, node);
		}
	}
	else if (node->data > tree->data) {
		if (tree->right == nullptr) {
			tree->right = node;
			return;
		}
		else {
			BST_InsertNode(tree->right, node);
		}
	}
}

//����. 
// �����Ϸ��� ����� �ڽ� ������ ���� ���� ����̴ٸ���.
// 1. ������ ����� ����Ʈ���� 0
// 2. ������ ����� ����Ʈ���� 1
// 3. ������ ����� ����Ʈ���� 2

Node* BST_SearchMinNode(Node* tree) {
	//Ʈ���� ������ null��ȯ
	if (tree == nullptr) return nullptr;
	// Ʈ���� ������ null�̸� �ش� Ʈ�� ��ȯ
	if (tree->left == nullptr) return tree;
	// Ʈ���� ������ null�� �ƴϸ� ���
	else return BST_SearchMinNode(tree->left);
}

Node* BST_RemoveNode(Node* tree, Node* parent, int target) {
	// target�� ��ġ�ϴ� ���� ������ ����.
	// ������ ����� ��ġ�� �Ǵ� ���� tree��, ������ ����� �θ�� parent�� ����
	// ������ ���(tree)�� removedNode�� ������ �Űܵΰ� ���߿� ����
	// tree ���� ���Ӱ� ������ ���� �����ǰ� ���ο� ���� ��ü�� ��ó�� �����Ѵ�.
	if (tree == nullptr) return nullptr;

	Node* removedNode = nullptr;

	if (tree->data > target)
		removedNode = BST_RemoveNode(tree->left, tree, target);
	else if (tree->data < target)
		removedNode = BST_RemoveNode(tree->right, tree, target);
	else if (tree->data == target) {
		
		removedNode = tree;
		
		//1. ���� ��������϶� -> ����Ʈ�� 0
		if (tree->left == nullptr && tree->right == nullptr) {
			if (parent!=nullptr&&parent->left == tree) parent->left = nullptr;
			else if (parent != nullptr&&parent->right == tree)parent->right == nullptr;
			else return removedNode;
		}

		//2. �����̳� �����ʿ� ����Ʈ���� ���� ��
		if (tree->left == nullptr || tree->right == nullptr) {
			Node* temp = nullptr;
			//temp�� Ʈ���� �Ű� �ְ�
			if (tree->left != nullptr) temp = tree->left;
			else temp = tree->right;

			if (parent->left == tree) parent->left = temp;
			else parent->right = temp;
		}

		// 3. �����Ϸ��� ��� �ڽ� ����Ʈ���� 2��
		else if (tree->left != nullptr && tree->right != nullptr) {
			// ������ ��庸�� ū ���� Ʈ�� �� ���� ���� ��带 ã�´�
			Node* minNnode_of_BiggerNodes = BST_SearchMinNode(tree->right);
			// ã�� ��带 �� ��ġ�� ������ ���´�.
			minNnode_of_BiggerNodes = BST_RemoveNode(tree, nullptr, minNnode_of_BiggerNodes->data);
			tree->data = minNnode_of_BiggerNodes->data;
		}
	}

	return removedNode;
}