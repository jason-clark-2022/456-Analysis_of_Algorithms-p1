#include <iostream>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <chrono>
#include <thread>
#include <queue>
#include "Node.cpp"

using namespace std;

vector<Node*> countOccurrences(string myFile);
Node* createHuffmanTree(vector<Node*> nodeList);
void huffmanEncode(Node* root, string fileIn, string fileOut);
void huffmanDecode(Node* root, string fileIn, string fileOut);
void setAllTreeBits(Node* root, string treeBits);
Node* searchTree(Node* root, char target);
void printTree(Node* root); // test method
bool fileExists(string filename);


class Compare
{
    public:
    bool operator() (Node* n1, Node* n2)
    {
        int a = n1->getCharacterCount();
        int b = n2->getCharacterCount();
        return a > b;
    }
};

int main()
{

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::microseconds;

    bool valid = false;
    string userInput;
    string huffmanTreeFile;
    string encodeINF;
    string encodeOPF;
    string decodeINF;
    string decodeOPF;
    
    cout << "\nPlease type the name of the file to create the huffman tree\n(Do not use .txt extension : 'e' to exit)" << endl << ">";
    while(!valid)
    {
        cin >> userInput;
        encodeINF = userInput + ".txt";

        if(userInput == "e")
        {
            break;
        }
        else if(fileExists(encodeINF))
        {
            valid = true;
        }
        else
        {
            cout << "Unable to open file. Please try again..." << endl << ">";
        }
    }
    if(!valid)
        return 0;
    valid = false;

    huffmanTreeFile = userInput;
    
    cout << "\nPlease type the name of the file to compress using huffman tree from: " << huffmanTreeFile; 
    cout << "\n(Do not use .txt extension : 'e' to exit : 'r' to use same file)" << endl;
    while(!valid)
    {
        cout << ">";
        cin >> userInput;
        encodeINF = userInput + ".txt";

        if(userInput == "e")
        {
            break;
        }
        else if(userInput == "r")
        {
            encodeINF = huffmanTreeFile + ".txt";
            valid = true;
        }
        else if(fileExists(encodeINF))
        {

            valid = true;
        }
        else
        {
            cout << "Unable to open file. Please try again..." << endl << ">";
        }
    }
    if(!valid)
        return 0;
    valid = false;

    if(userInput == "r")
    {
 
        encodeOPF = huffmanTreeFile + "_ENC.txt";
        decodeINF = encodeOPF;
        decodeOPF = huffmanTreeFile + "_DEC.txt";

    }
    else
    {
        encodeOPF = huffmanTreeFile + userInput +"_ENC.txt";
        decodeINF = encodeOPF;
        decodeOPF = huffmanTreeFile + userInput +"_DEC.txt";
    }
    huffmanTreeFile +=".txt";


    cout << endl << "Creating tree... " << endl;
    auto start = high_resolution_clock::now();
    vector<Node*> nodeList = countOccurrences(huffmanTreeFile);
    Node* root = createHuffmanTree(nodeList);
    auto stop = high_resolution_clock::now();
    auto time = duration_cast<microseconds>(stop - start);
    cout << "Time to create tree: " << time.count() << " microseconds" << endl;

    cout << "\nEncoding " << encodeINF << "...\n";
    cout << "Using tree from " << huffmanTreeFile << endl << endl;

    start = high_resolution_clock::now();
    huffmanEncode(root, encodeINF, encodeOPF);
    stop = high_resolution_clock::now();
    time = duration_cast<microseconds>(stop - start);
    cout << "Encode Success: Compressed to file " << encodeOPF << ".\n";
    cout << "Time to Compress: " << time.count() << " microseconds" << endl << endl;


    cout << "Decoding " << decodeINF << "...\n";
    start = high_resolution_clock::now();
    huffmanDecode(root, decodeINF, decodeOPF);
    stop = high_resolution_clock::now();
    time = duration_cast<microseconds>(stop - start);
    cout << "Decode Success: Decompressed to file " << decodeOPF << ".\n";
    cout << "Time to Decompress: " << time.count() << " microseconds" << endl << endl;

    cout << "Goodbye...\n";
}

vector<Node*> countOccurrences(string myFile)
{
    int nodeListSize = 128; // 128 for base ascii table size
    vector<Node*> nodeList(nodeListSize);
    
    // populate the nodelist with all characters derived from ascii values
    char charFromAscii;
    char characterFromFile;
    for(int i = 0; i < nodeListSize; i++)
    {
        charFromAscii = (char)i;
        nodeList[i] = new Node(charFromAscii);
    }

    ifstream file;
    file.open(myFile);
    if(file.is_open())
    {
        int characterAsAscii;
        while (file.get(characterFromFile))
        {
            characterAsAscii = (int)characterFromFile;
            if(characterAsAscii > 127 || characterAsAscii < 0) // checking for character not in ascii table
            {
                bool specialCharacterInList = false;
                for(int i = 128; i < nodeListSize || specialCharacterInList == true; i++)
                {
                    if(nodeList[i]->getCharacter() == characterFromFile)
                    {
                        specialCharacterInList = true;
                        nodeList[i]->incrementCharacterCount();
                    }
                }
                if(!specialCharacterInList)
                {
                    nodeList.push_back(new Node(characterFromFile));
                    nodeList.back()->incrementCharacterCount();
                    nodeListSize++;
                }
            }
            else
            {
                nodeList[characterAsAscii]->incrementCharacterCount();
            }
        }

        //delete all nodes that have not had the character size incremented
        // for (int i = 0; i < nodeListSize; i++)
        // {
        //     if(nodeList[i]->getCharacterCount() == 0)
        //     {
        //         nodeList.erase(nodeList.begin()+i);
        //         i--;
        //         nodeListSize--;
        //     }
        // }
        file.close();
    }
    else
    {
        cerr << "Unable to open file";
    }
    return nodeList;
}

Node* createHuffmanTree(vector<Node*> nodeList)
{
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    for(int i = 0; i < nodeList.size(); i++)
    {
        pq.push(nodeList[i]);
    }

    while(pq.size() != 1)
    {
        Node* z = new Node(NULL);
        z->setLeftChild(pq.top());
        pq.pop();
        z->setRightChild(pq.top());
        pq.pop();
        z->setCharacterCount(z->getLeftChild()->getCharacterCount() + z->getRightChild()->getCharacterCount());
        pq.push(z);
    }
    setAllTreeBits(pq.top(), "");
    return pq.top();
}

void huffmanEncode(Node* root, string fileIn, string fileOut)
{
    char characterFromFile;
    Node* nodeOfCharacter;
    ifstream inFile;
    ofstream outFile;
    inFile.open(fileIn);
    if(inFile.is_open())
    {
        outFile.open(fileOut);
        if(outFile.is_open())
        {
            while (inFile.get(characterFromFile))
            {
                nodeOfCharacter = searchTree(root, characterFromFile);
                outFile << nodeOfCharacter->getTreeBits();
            }
            inFile.close();
            outFile.close();
        }
        else
        {
            cerr << "Unable to open output file";
        }
    }
    else
    {
        cerr << "Unable to open read file";
    }
}

void huffmanDecode(Node* root, string fileIn, string fileOut)
{
    char characterFromFile;
    Node* searchNode = root;
    ifstream inFile;
    ofstream outFile;
    inFile.open(fileIn);
    if(inFile.is_open())
    {
        outFile.open(fileOut);
        if(outFile.is_open())
        {
            while (!inFile.eof())
            {
                inFile.get(characterFromFile);
                if(searchNode->getLeftChild() == NULL || searchNode->getRightChild() == NULL)
                {
                    outFile << searchNode->getCharacter();
                    searchNode = root;
                }
                if(characterFromFile == '0')
                    searchNode = searchNode->getLeftChild();
                else
                    searchNode = searchNode->getRightChild();
            }
            inFile.close();
            outFile.close();
        }
        else
        {
            cerr << "Unable to open output file";
        }
    }
    else
    {
        cerr << "Unable to open input file";
    }
}

void setAllTreeBits(Node* root, string treeBits)
{
    if(root == NULL)
        return;
    
    if(root->getLeftChild() != NULL)
    {
        root->getLeftChild()->setTreeBits(treeBits + "0");
        setAllTreeBits(root->getLeftChild(), treeBits + "0");
    }
    if(root->getRightChild() != NULL)
    {
        root->getRightChild()->setTreeBits(treeBits+"1");
        setAllTreeBits(root->getRightChild(), treeBits+"1");
    }
}

Node* searchTree(Node* root, char target)
{
    Node* nextChild;
    if(root == NULL)
    {
        return NULL;
    }
    if(root->getCharacter() == target)
    {
        return root;
    }
    nextChild = searchTree(root->getLeftChild(), target);
    if(nextChild != NULL)
        return nextChild;

    nextChild = searchTree(root->getRightChild(), target);
    if(nextChild != NULL)
        return nextChild;

    return NULL;
}

void printTree(Node* root)
{
    if(root == NULL)
        return;
    if(root->getCharacter() != NULL)
        cout << root->getCharacter() << ": " << root->getCharacterCount() << ": " << root->getTreeBits() << "\n";
    printTree(root->getLeftChild());
    printTree(root->getRightChild());
}

bool fileExists(string filename)
{
    ifstream file(filename.c_str());
    return file.good();
}