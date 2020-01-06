#include "json.h"
using namespace std;

namespace Json 
{
    
    Node::Node(vector<Node> array)
        : as_array(move(array))
    {
    }
    
    Node::Node(map<string, Node> map) 
        : as_map(move(map))
    {
    }
    
    Node::Node(int value) 
        : as_int(value)
    {
    }
    
    Node::Node(string value) 
        : as_string(move(value)) 
    {
    }
    
    const vector<Node>& Node::AsArray() const
    {
      return as_array;
    }
    
    const map<string, Node>& Node::AsMap() const
    {
      return as_map;
    }
    
    int Node::AsInt() const
    {
      return as_int;
    }
    
    const string& Node::AsString() const
    {
      return as_string;
    }
    
    Document::Document(Node root) 
        : root(move(root))
    {
    }
    
    const Node& Document::GetRoot() const 
    {
      return root;
    }
    
    Node LoadNode(istream& input);
    
    Node LoadArray(istream& input)
    {
        vector<Node> result;
        
        for (char c; input >> c && c != ']'; )
        {
            if (c != ',') 
            {
                input.putback(c);
            }
            result.push_back(LoadNode(input));
        }
        
        return Node(move(result));
    }
    
    Node LoadInt(istream& input) 
    {
        int result = 0;
        while (isdigit(input.peek()))
        {
            result *= 10;
            result += input.get() - '0';
        }
        return Node(result);
    }
    
    Node LoadString(istream& input)
    {
        string line;
        getline(input, line, '"');
        return Node(move(line));
    }
    
    Node LoadDict(istream& input) 
    {
        map<string, Node> result;
        
        for (char c; input >> c && c != '}'; )
        {
            if (c == ',') 
            {
                input >> c;
            }
            
            string key = LoadString(input).AsString();
            input >> c;
            result.insert({move(key), LoadNode(input)});
        }
        
        return Node(move(result));
    }
    
    Node LoadNode(istream& input)
    {
        char c;
        input >> c;
        
        if (c == '[')
        {
            return LoadArray(input);
        } 
        else if (c == '{')
        {
            return LoadDict(input);
        } 
        else if (c == '"')
        {
            return LoadString(input);
        } 
        else 
        {
            input.putback(c);
            return LoadInt(input);
        }
    }
    
    Document Load(istream& input)
    {
        return Document{LoadNode(input)};
    }
}