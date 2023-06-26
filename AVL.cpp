#include<iostream>
using namespace std;
struct node {
	int data;
	node* left;
	node* right;
};
node* root = NULL;
class AVL {
public:
	void insert(node*& root, int data) {
		if (root == NULL) {
			root = new node;
			root->data = data;
			root->left = NULL;
			root->right = NULL;
		}
		else if (root->data == data) {
			cout << "The Node Already Exits\n" << data << "\n";
		}
		else if (data < root->data) {
			insert(root->left, data);
			int bf = bl_fac(root);
			if (bf == 2) {
				if (data < root->left->data) {
					S_R_R(root);
				}
				else {
					D_L_R(root);
				}
			}
		}
		else if (data > root->data) {
			insert(root->right, data);
			int bf = bl_fac(root);
			if (bf == -2) {
				if (data > root->right->data) {
					S_L_R(root);
				}
				else {
					D_R_L(root);
				}
			}
		}
	}
	node* D_R_L(node*& root) {
		root->right = S_R_R(root->right);
		return S_L_R(root);
	}
	node* D_L_R(node*& root) {
		root->left = S_L_R(root->left);
		return S_R_R(root);
	}
	node* S_R_R(node*& root) {
		node* u = root->left;
		root->left = u->right;
		u->right = root;
		return u;
	}
	node* S_L_R(node*& root) {
		node* u = root->right;
		root->right = u->left;
		u->left = root;
		return u;
	}
	int bl_fac(node* root) {
		int bf = Height(root->left) - Height(root->right);
		return bf;
	}
	int Height(node* root) {
		int left = 0;
		int right = 0;
		if (root == NULL) {
			return NULL;
		}
		else {
			left = Height(root->left);
			right = Height(root->right);
			if (left > right) {
				return left + 1;
			}
			else {
				return right + 1;
			}
		}
	}
	void Display(node* root) {
		if (root == NULL) {
			return;
		}
		else {
			Display(root->left);
			cout << root->data << " ";
			Display(root->right);
		}

	}
	void Del(node*& temp) {
		node* temp2 = NULL;
		if (temp->right == NULL)
		{
			temp2 = temp;
			temp = temp->left;
			delete temp2;
		}
		else if (temp->left == NULL) {
			temp2 = temp;
			temp = temp->right;
			delete temp2;
		}
		else {
			temp2 = temp->right;
			while (temp2->left) {
				temp2 = temp2->left;
			}
			temp2->left = temp->left;
			temp2 = temp;
			temp = temp->right;
			delete temp2;
		}
	}
	void deleteNode(int Num, node*& temp) {
		if (temp == NULL) {
			cout << Num << "Not Found\n";
		}
		else if (Num < temp->data) {
			deleteNode(Num, temp->left);
		}
		else if (Num > temp->data) {
			deleteNode(Num, temp->right);
		}
		else {
			Del(temp);
		}
	}
};
int main() {
	AVL a;
	while (true) {
		cout << "Enter the Respective Number to Perform the Operation\n";
		cout << "1 Insert\n";
		cout << "2 BF\n";
		cout << "3 Display\n";
		cout << "4 Delete\n";
		int n;
		cin >> n;
		if (n == 1) {
			int data;
			cout << "Enter the The data you want to insert\n";
			cin >> data;
			a.insert(root, data);
		}
		if (n == 2) {
			cout << a.bl_fac(root) << "\n";
		}
		if (n == 3) {
			cout << "Your Data\n";
			a.Display(root);
			cout << "\n";
		}
		if (n == 4) {
			int data;
			cout << "Enter the The data you want to Delete\n";
			cin >> data;
			a.deleteNode(data,root);
		}
	}
}