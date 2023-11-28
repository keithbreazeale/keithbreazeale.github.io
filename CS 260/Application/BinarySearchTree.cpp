//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Keith Breazeale
// Date        : 9 November 2023
// Class       : CS-260
// Version     : 2.0
// Copyright   : Copyright © 2017 SNHU COCE
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

//Internal Structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amt;
    Bid() {
        amt = 0.0;
    }
};

//Enhancements were done to allow for the new functionality of the search tree.
//Internal Structure for Tree Node
struct Node {
    Bid current;
    Node* idLeft;
    Node* idRight;
    Node* amtParent;
    Node* amtLeft;
    Node* amtRight;

    Node(Bid bid) {
        current = bid;
        idLeft = NULL;
        idRight = NULL;
        amtParent = NULL;
        amtLeft = NULL;
        amtRight = NULL;
    }

    ~Node() {
        if (idLeft) {
            delete idLeft;
        }
        if (idRight) {
            delete idRight;
        }
        if (amtParent) {
            delete amtParent;
        }
        if (amtLeft) {
            delete amtLeft;
        }
        if (amtRight) {
            delete amtRight;
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

// Private class variables start in lower case where as Public class variables start in Upper Case
class BinarySearchTree {
    private:
        Node* root;
        Node* amtRoot;
        void inIdOrder(Node* node);
        void inAmtOrder(Node* node);
        void insertId(Bid bid, Node* createdNode);
        void insertAmt(Bid bid, Node* createdNode);
        void removeNode(Node* rootNode, string removeBidId);
        void amtSearch(Node* node, double lowAmt, double highAmt);

    public:
        BinarySearchTree();
        virtual ~BinarySearchTree();
        void InIdOrder();
        void InAmtOrder();
        void Insert(Bid bid);
        void Remove(string bidId);
        Bid IdSearch(string bidId);
        void AmtSearch(double lowAmt, double highAmt);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    root = NULL;
    amtRoot = NULL;
}

/**
 * Destructor
 */

//Enhancement - The destructor was missing during the code review.
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    if (this->root) {
        delete root;
        delete amtRoot;
    }
}

/**
 * Traverse the tree in id order
 */
void BinarySearchTree::InIdOrder() {
    this->inIdOrder(this->root);
}

/**
* Traverse the tree in amount order - ENHANCEMENT
*/
void BinarySearchTree::InAmtOrder() {
    this->inAmtOrder(this->root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid inputBid) {
    Node* createdNode = new Node(inputBid);
    insertId(inputBid, createdNode);
    insertAmt(inputBid, createdNode);
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string removeBidId) {
    removeNode(this->root, removeBidId);
}

/**
 * Search for a bid by id
 */
Bid BinarySearchTree::IdSearch(string searchBidId) {
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

/**
 * Search for bids by range of values - ENHANCEMENT
 */
void BinarySearchTree::AmtSearch(double lowAmt, double highAmt) {
    amtSearch(this->root, lowAmt, highAmt);
}

/**
 * Search for bids by ID Order
 */
void BinarySearchTree::inIdOrder(Node* node) {
    if (node) {
        // Recursive call left
        inIdOrder(node->idLeft);

        // If left is done display current
        displayBid(node->current);

        // Recursive call right
        inIdOrder(node->idRight);
    }
}

/**
 * Search for bids by Amount Order - ENHANCEMENT
 */
void BinarySearchTree::inAmtOrder(Node* node) {
    if (node) {
        // Recursive call left
        inAmtOrder(node->amtLeft);

        // If left is done display current
        displayBid(node->current);

        // Recursive call right
        inAmtOrder(node->amtRight);
    }
}

/**
 * Process for Inserting a Bid and where to place it in the BST
 */
void BinarySearchTree::insertId(Bid inputBid, Node* createdNode) {
    Node* prevNode = NULL;
    Node* testNode = this->root;
    string direction = "Z";

    while (testNode) {
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
        this->root = createdNode;
    }
    else {
        if (direction == "L") {
            prevNode->idLeft = createdNode;
        }
        else {
            prevNode->idRight = createdNode;
        }
    }
}

/**
 * Process for Inserting an Amount for a bid and where to place it in the BST
 */

void BinarySearchTree::insertAmt(Bid inputBid, Node* createdNode) {
    Node* prevNode = NULL;
    Node* testNode = this->amtRoot;
    string direction = "Z";

    while (testNode) {
        prevNode = testNode;
        if (inputBid.amt < testNode->current.amt) {
            direction = "L";
            testNode = testNode->amtLeft;
        }
        else {
            direction = "R";
            testNode = testNode->amtRight;
        }
    }

    if (not prevNode) {
        this->amtRoot = createdNode;
    }
    else {
        createdNode->amtParent = prevNode;
        if (direction == "L") {
            prevNode->amtLeft = createdNode;
        }
        else {
            prevNode->amtRight = createdNode;
        }
    }
}

/**
 * Process for Removing a Bid and where to find it in the BST
 */

void BinarySearchTree::removeNode(Node* rootNode, string removeBidId) {
    Node* parentNode = NULL;
    Node* currentNode = rootNode;
    while (currentNode) {
        // If the bid is found
        if (currentNode->current.bidId == removeBidId) {
            // clean up the amount order
            Node* amtParentNode = currentNode->amtParent;
            if (not currentNode->amtLeft && not currentNode->amtRight) {
                if (amtParentNode) {
                    if (amtParentNode->amtLeft == currentNode) {
                        amtParentNode->amtLeft = NULL;
                    }
                    else {
                        amtParentNode->amtRight = NULL;
                    }
                }
            }
            else if (currentNode->amtLeft && not currentNode->amtRight) {
                if (not amtParentNode) {
                    this->amtRoot = currentNode->amtLeft;
                }
                else if (amtParentNode->amtLeft == currentNode) {
                    amtParentNode->amtLeft = currentNode->amtLeft;
                }
                else {
                    amtParentNode->amtRight = currentNode->amtLeft;
                }
            }
            else if (not currentNode->amtLeft && currentNode->amtRight) {
                if (not amtParentNode) {
                    this->amtRoot = currentNode->amtRight;
                }
                else if (amtParentNode->amtLeft == currentNode) {
                    amtParentNode->amtLeft = currentNode->amtRight;
                }
                else {
                    amtParentNode->amtRight = currentNode->amtRight;
                }
            }
            else {
                Node* amtSuccessorNode = currentNode->amtRight;
                Node* amtSuccessorParent = currentNode;
                while (amtSuccessorNode->amtLeft) {
                    amtSuccessorParent = amtSuccessorNode;
                    amtSuccessorNode = amtSuccessorNode->amtLeft;
                }
                amtSuccessorNode->amtLeft = currentNode->amtLeft;
                amtSuccessorNode->amtRight = currentNode->amtRight;
                amtSuccessorParent->amtLeft = NULL;
            }


            // if neither left or right node exists
            if (not currentNode->idLeft && not currentNode->idRight) {
                if (parentNode) {
                    if (parentNode->idLeft == currentNode) {
                        parentNode->idLeft = NULL;
                    }
                    else {
                        parentNode->idRight = NULL;
                    }
                }
            }
            // if only the left node exists
            else if (currentNode->idLeft && not currentNode->idRight) {
                if (not parentNode) {
                    this->root = currentNode->idLeft;
                }
                else if (parentNode->idLeft == currentNode) {
                    parentNode->idLeft = currentNode->idLeft;
                }
                else {
                    parentNode->idRight = currentNode->idLeft;
                }
                currentNode->idLeft = NULL;
            }
            // if only the right node exists
            else if (currentNode->idRight) {
                if (not parentNode) {
                    this->root = currentNode->idRight;
                }
                else if (parentNode->idLeft == currentNode) {
                    parentNode->idLeft = currentNode->idRight;
                }
                else {
                    parentNode->idRight = currentNode->idRight;
                }
                currentNode->idRight = NULL;
            }
            // if both nodes exist
            else {
                Node* successorNode = currentNode->idRight;
                Node* successorParent = currentNode;
                while (successorNode->idLeft) {
                    successorParent = successorNode;
                    successorNode = successorNode->idLeft;
                }
                successorNode->idLeft = currentNode->idLeft;
                successorNode->idRight = currentNode->idRight;
                successorParent->idLeft = NULL;
            }

            // Remove the current node
            currentNode->idLeft = NULL;
            currentNode->idRight = NULL;
            currentNode->amtParent = NULL;
            currentNode->amtLeft = NULL;
            currentNode->amtRight = NULL;
            delete currentNode;
            currentNode = NULL;
        }
        // If removeBidId is less than current its in left branch
        else if (currentNode->current.bidId > removeBidId) {
            parentNode = currentNode;
            currentNode = currentNode->idLeft;
        }
        // Else the node is in the right branch
        else {
            parentNode = currentNode;
            currentNode = currentNode->idRight;
        }
    }
    return;
}

/**
 * Process for Searching by Amount for a bid and where to look within the BST
 */

void BinarySearchTree::amtSearch(Node* node, double lowAmt, double highAmt) {
    if (node) {
        // Recursive call left
        amtSearch(node->amtLeft, lowAmt, highAmt);

        // If left is done display current if there is a match
        if (node->current.amt >= lowAmt && node->current.amt <= highAmt) {
            displayBid(node->current);
        }

        // Recursive call right
        amtSearch(node->amtRight, lowAmt, highAmt);
    }
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
    double amtHigh, amtLow;
    switch (argc) {
        case 2:
            csvPath = argv[1];
            bidKey = "98109";
            amtLow = 300;
            amtHigh = 600;
            break;
        case 3:
            csvPath = argv[1];
            bidKey = argv[2];
            amtLow = 300;
            amtHigh = 600;
            break;
        default:
            csvPath = "eBid_Monthly_Sales.csv";
            bidKey = "98109";
            amtLow = 300;
            amtHigh = 600;
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
        cout << "  2. Display All Bids by ID" << endl;
        cout << "  3. Display All Bids by Amount" << endl;
        cout << "  4. Find Bid by ID" << endl;
        cout << "  5. Find Bids in Amount Range" << endl;
        cout << "  6. Remove Bid" << endl;
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

                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;

            case 2:
                bst->InIdOrder();
                break;

            case 3:
                bst->InAmtOrder();
                break;

            case 4:
                ticks = clock();

                bid = bst->IdSearch(bidKey);

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

            case 5:
                bst->AmtSearch(amtLow, amtHigh);
                break;

            case 6:
                bst->Remove(bidKey);
                break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
