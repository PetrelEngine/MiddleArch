//
// Created by liuqian8 on 2019/7/10.
//
#include "Node.h"

Node::Node(Context *context):
    Animatable(context)
{

}

Node::~Node()
{

}

bool Node::load(std::string source, bool setInstanceDefault)
{
    return false;
}

Node* Node::createChild(const string &name, CreateMode mode, unsigned int id, bool temporary)
{

    return nullptr;
}

void Node::addChild(Node *node, unsigned int index)
{
    if(!node || node == this || node->parent_ == this)
        return;

}

void Node::setPosition(const glm::vec3 &position)
{

}

void Node::setScale(const glm::vec3 scale)
{

}

Component* Node::createComponent(string type, CreateMode mode, unsigned int id)
{
    return nullptr;
}
