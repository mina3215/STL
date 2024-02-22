class Node {
public:
	int data;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(int _data, Node* _left, Node* _right)
		:data(_data),left(_left),right(_right){}
};

// 탐색
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

//삽입 (현재 재귀 단게 서브 트리의 루트, 삽입할 노드)
void BST_InsertNode(Node* tree, Node* node) {
	//루트 노드가 데이터 보다 크다 -> 왼쪽으로 
	if (node->data < tree->data) {
		//근데 왼쪽 노드가 없다 ? 리프 노드에 추가해줘야 한다.
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

//삭제. 
// 삭제하려는 노드의 자식 개수에 따라 삭제 방법이다르다.
// 1. 삭제할 노드의 서브트리가 0
// 2. 삭제할 노드의 서브트리가 1
// 3. 삭제할 노드의 서브트리가 2

Node* BST_SearchMinNode(Node* tree) {
	//트리가 없으면 null반환
	if (tree == nullptr) return nullptr;
	// 트리의 왼쪽이 null이면 해당 트리 반환
	if (tree->left == nullptr) return tree;
	// 트리의 왼쪽이 null이 아니면 재귀
	else return BST_SearchMinNode(tree->left);
}

Node* BST_RemoveNode(Node* tree, Node* parent, int target) {
	// target과 일치하는 노드는 삭제할 노드다.
	// 삭제할 노드의 위치가 되는 노드는 tree에, 삭제할 노드의 부모는 parent에 저장
	// 삭제할 노드(tree)는 removedNode에 복사해 옮겨두고 나중에 리턴
	// tree 값을 새롭게 세팅해 이제 삭제되고 새로운 노드로 대체된 것처럼 연산한다.
	if (tree == nullptr) return nullptr;

	Node* removedNode = nullptr;

	if (tree->data > target)
		removedNode = BST_RemoveNode(tree->left, tree, target);
	else if (tree->data < target)
		removedNode = BST_RemoveNode(tree->right, tree, target);
	else if (tree->data == target) {
		
		removedNode = tree;
		
		//1. 내가 리프노드일때 -> 서브트리 0
		if (tree->left == nullptr && tree->right == nullptr) {
			if (parent!=nullptr&&parent->left == tree) parent->left = nullptr;
			else if (parent != nullptr&&parent->right == tree)parent->right == nullptr;
			else return removedNode;
		}

		//2. 왼쪽이나 오른쪽에 서브트리가 없을 때
		if (tree->left == nullptr || tree->right == nullptr) {
			Node* temp = nullptr;
			//temp에 트리를 옮겨 주고
			if (tree->left != nullptr) temp = tree->left;
			else temp = tree->right;

			if (parent->left == tree) parent->left = temp;
			else parent->right = temp;
		}

		// 3. 삭제하려는 노드 자식 서브트리가 2개
		else if (tree->left != nullptr && tree->right != nullptr) {
			// 삭제할 노드보다 큰 서브 트리 중 가장 작은 노드를 찾는다
			Node* minNnode_of_BiggerNodes = BST_SearchMinNode(tree->right);
			// 찾은 노드를 내 위치에 가져다 덮는다.
			minNnode_of_BiggerNodes = BST_RemoveNode(tree, nullptr, minNnode_of_BiggerNodes->data);
			tree->data = minNnode_of_BiggerNodes->data;
		}
	}

	return removedNode;
}