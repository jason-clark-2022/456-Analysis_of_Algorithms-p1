using namespace std;

class Node
{
    private:
        char character;
        int characterCount;
        string treeBits;
        Node* leftChild;
        Node* rightChild;
    
    public:
        Node(char character)
        {
            this->character = character;
            characterCount = 0;
            leftChild = rightChild = NULL;
            treeBits = "";
        } 
    
    void incrementCharacterCount()
    {
        characterCount++;
    }

    void setCharacterCount(int newCharacterCount)
    {
        characterCount = newCharacterCount;
    }

    void setLeftChild(Node* childNode)
    {
        leftChild = childNode;
    }

    void setRightChild(Node* childNode)
    {
        rightChild = childNode;
    }

    void setTreeBits(string s)
    {
        treeBits = s;
    }

    char getCharacter()
    {
        return character;
    }

    int getCharacterCount()
    {
        return characterCount;
    }
    
    Node* getLeftChild()
    {
        return leftChild;
    }

    Node* getRightChild()
    {
        return rightChild;
    }

    string getTreeBits()
    {
        return treeBits;
    }

};