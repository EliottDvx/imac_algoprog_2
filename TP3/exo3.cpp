#include "mainwindow.h"
#include "tp3.h"
#include <QApplication>
#include <time.h>
#include <stack>
#include <queue>

MainWindow* w = nullptr;
using std::size_t;

struct SearchTreeNode : public Node
{    
    SearchTreeNode* left;
    SearchTreeNode* right;
    int value;

    void initNode(int value)
    {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }

	void insertNumber(int value) {
        if(value < this->value){
            if(this->left == nullptr){
                this->left = new SearchTreeNode(value);
            }
            else{
                this->left->insertNumber(value);
            }
        }
        else{
            if(this->right == nullptr){
                this->right = new SearchTreeNode(value);
            }
            else{
                this->right->insertNumber(value);
            }
        }
    }

    uint height() const	{
        if(this->left != nullptr && this->right != nullptr){
            if(this->left->height() > this->right->height()){
                return (this->left->height() + 1);
            }
            else{
                return (this->right->height() + 1);
            }
        }
        else{
            if(this->left != nullptr){
                return (this->left->height() + 1);
            }
            else if(this->right != nullptr){
                return (this->right->height() + 1);
            }
        }

        return 1;
    }

	uint nodesCount() const {
        // should return the sum of nodes within left child and
        // right child +1 for itself. If there is no child, return
        // just 1
        return 1;
	}

	bool isLeaf() const {
        // return True if the node is a leaf (it has no children)
        return false;
	}

	void allLeaves(Node* leaves[], uint& leavesCount) {
        // fill leaves array with all leaves of this tree
	}

	void inorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with inorder travel
	}

	void preorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with preorder travel
	}

	void postorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with postorder travel
	}

	Node* find(int value) {
        // find the node containing value
		return nullptr;
	}

    void reset()
    {
        if (left != NULL)
            delete left;
        if (right != NULL)
            delete right;
        left = right = NULL;
    }

    SearchTreeNode(int value) : Node(value) {initNode(value);}
    ~SearchTreeNode() {}
    int get_value() const {return value;}
    Node* get_left_child() const {return left;}
    Node* get_right_child() const {return right;}
};

Node* createNode(int value) {
    return new SearchTreeNode(value);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 200;
    w = new BinarySearchTreeWindow<SearchTreeNode>();
	w->show();

	return a.exec();
}
