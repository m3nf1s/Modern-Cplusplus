#include "xml.h"

#include <string_view>
#include <iostream>

using namespace std;

namespace Xml
{
    
    pair<string_view, string_view> Split(string_view line, char by)
    {
        size_t pos = line.find(by);
        string_view left = line.substr(0, pos);
        
        if (pos < line.size() && pos + 1 < line.size())
        {
            return {left, line.substr(pos + 1)};
        } 
        else 
        {
            return {left, string_view()};
        }
    }
    
    string_view Lstrip(string_view line)
    {
        while (!line.empty() && isspace(line[0]))
        {
            line.remove_prefix(1);
        }
        return line;
    }
    
    string_view Unquote(string_view value)
    {
        if (!value.empty() && value.front() == '"')
        {
            value.remove_prefix(1);
        }
        if (!value.empty() && value.back() == '"')
        {
            value.remove_suffix(1);
        }
        return value;
    }
    
    Node LoadNode(istream& input) 
    {
        string root_name;
        getline(input, root_name);
        
        Node root(root_name.substr(1, root_name.size() - 2), {});
        for (string line; getline(input, line) && line[1] != '/'; )
        {
            auto [node_name, attrs] = Split(Lstrip(line), ' ');
            attrs = Split(attrs, '>').first;
            unordered_map<string, string> node_attrs;
            while (!attrs.empty()) 
            {
                auto [head, tail] = Split(attrs, ' ');
                auto [name, value] = Split(head, '=');
                if (!name.empty() && !value.empty()) 
                {
                  node_attrs[string(Unquote(name))] = string(Unquote(value));
                }
                attrs = tail;
            }
            
            root.AddChild(Node(string(node_name.substr(1)), move(node_attrs)));
        }
        return root;
    }
    
    Document Load(istream& input)
    {
      return Document{LoadNode(input)};
    }
    
    Node::Node(string name, unordered_map<string, string> attrs)
        : name(move(name))
        , attrs(move(attrs))
    {
    }
    
    const vector<Node>& Node::Children() const 
    {
        return children;
    }
    
    Document::Document(Node root) : root(move(root))
    {
    }
    
    const Node& Document::GetRoot() const 
    {
        return root;
    }
    
    void Node::AddChild(Node node) 
    {
        children.push_back(move(node));
    }
    
    string_view Node::Name() const
    {
        return name;
    }
}