//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Keith Breazeale
// Date        : 2 December 2021
// Class       : CS-260
// Version     : 1.0
// CopyidRight   : CopyidRight © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <algorithm>
#include <iostream>
#include "CSVparser.hpp"

using namespace std;


//============================================================================
// Global definitions visible to all methods and classes
//============================================================================
// forward declarations
double strToDouble(string str, char ch);

struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amt;
    Bid() {
        amt = 0.0;
    }
};

// FIXME (1): Internal structure for tree node
struct Node {
    Bid current;
    Node* idLeft;
    Node* idRight;

    Node(Bid bid) {
        current = bid;
        idLeft = NULL;
        idRight = NULL;
    }

    ~Node() {
        if (idLeft) {
            delete idLeft;
        }
        if (idRight) {
            delete idRight;
        }
    }
};



void displayBid(Bid bid) {
    cout
        << bid.bidId
        << ": "
        << bid.title
        << " | "
        << bid.amt
        << " | "
        << bid.fund
        << endl;

    return;
}


//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;
    void inOrder(Node* node);
    void removeNode(Node* rootNode, string removeBidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    root = NULL;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node

}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    this->inOrder(this->root);
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid inputBid) {
    // FIXME (2a) Implement inserting a bid into the tree
    Node* prevNode = NULL;
    Node* testNode = this->root;
    string direction = "Z";

    while (testNode) {
        cout << testNode->current.bidId;
        prevNode = testNode;
        if (inputBid.bidId < testNode->current.bidId) {
            direction = "L";
            testNode = testNode->idLeft;
        }
        else {
            direction = "R";
            testNode = testNode->idRight;
        }
    }

    if (not prevNode) {
        this->root = new Node(inputBid);
    }
    else {
        if (direction == "L") {
            prevNode->idLeft = new Node(inputBid);
        }
        else {
            prevNode->idRight = new Node(inputBid);
        }
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string removeBidId) {
    // FIXME (4a) Implement removing a bid from the tree
    removeNode(this->root, removeBidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string searchBidId) {
    // FIXME (3) Implement searching the tree for a bid
    Bid bid;
    Node* testNode = this->root;

    while (testNode) {
        if (testNode->current.bidId == searchBidId) {
            bid = testNode->current;
            break;
        }
        if (searchBidId < testNode->current.bidId) {
            testNode = testNode->idLeft;
        }
        else {
            testNode = testNode->idRight;
        }
    }
    return bid;
}

void BinarySearchTree::inOrder(Node* node) {
    if (node) {
        inOrder(node->idLeft);
        displayBid(node->current);
        inOrder(node->idRight);
    }
}

void BinarySearchTree::removeNode(Node* rootNode, string removeBidId) {
    Node* parentNode = NULL;
    Node* currentNode = rootNode;
    while (currentNode) {
        // If the bid is found
        if (currentNode->current.bidId == removeBidId) {
            // if neither the Left or Right node exist
            if (not currentNode->idLeft && not currentNode->idRight) {
                if (not parentNode) {
                    currentNode = NULL;
                }
                else if (parentNode->idLeft == currentNode) {
                    parentNode->idLeft = NULL;
                }
                else {
                    parentNode->idRight = NULL;
                }
            }
            // if only the Left node exists
            else if (currentNode->idLeft && not currentNode->idRight) {
                if (not parentNode) {
                    currentNode->current = currentNode->idLeft->current;
                }
                else if (parentNode->idLeft == currentNode) {
                    parentNode->idLeft = currentNode->idLeft;
                }
                else {
                    parentNode->idRight = currentNode->idLeft;
                }
            }
            // if only the Right node exists
            else if (currentNode->idRight) {
                if (not parentNode) {
                    currentNode->current = currentNode->idRight->current;
                }
                else if (parentNode->idLeft == currentNode) {
                    parentNode->idLeft = currentNode->idRight;
                }
                else {
                    parentNode->idRight = currentNode->idRight;
                }
            }
            // if both nodes exist
            else {
                Node* successorNode = currentNode->idRight;
                while (successorNode->idLeft) {
                    successorNode = successorNode->idLeft;
                }
                currentNode = successorNode;
                removeNode(currentNode->idRight, successorNode->current.bidId);
            }
        }
        // If removeBidId is less than current its in Left branch
        if (removeBidId < currentNode->current.bidId) {
            currentNode = currentNode->idLeft;
        }
        // Else Right branch
        else {
            currentNode = currentNode->idRight;
        }
    }
    return;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amt = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", amt: " << bid.amt << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst = new BinarySearchTree();

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;


        switch (choice) {
        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
