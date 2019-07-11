//
// Created by liuqian8 on 2019/7/10.
//
#pragma once
#include "fwd.hpp"
#include "Animatable.h"
#include "vec3.hpp"
#include "vec2.hpp"
#include <vector>
class Component;
enum CreateMode
{
    REPLICATED = 0,
    LOCAL = 1
};
class Node: public Animatable
{
    ENGINE_OBJECT(Node,Animatable);
public:
    Node(Context* context);

    virtual ~Node();

//    virtual bool load(std::string source, bool setInstanceDefault = false);

    Node* createChild(const string& name = "", CreateMode mode = REPLICATED, unsigned id = 0, bool temporary = false);

    void addChild(Node* node, unsigned index = UINT_MAX);

    void setPosition(const glm::vec3& position);

    void setScale(const glm::vec3 scale);

    Component* createComponent(string type, CreateMode mode = REPLICATED, unsigned id = 0);

    template <class T> T* createComponent(CreateMode mode = REPLICATED, unsigned id = 0);

private:
    Node* parent_;
    std::vector<Node*> children_;
};

template <class T > T* Node::createComponent(CreateMode mode, unsigned int id)
{
    return static_cast<T*>(createComponent(T::GetTypeStatic(),mode,id));
}
