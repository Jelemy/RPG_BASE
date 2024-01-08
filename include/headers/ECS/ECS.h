#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>

class Component;
class Entity;
// Define typedef for component ID
using ComponentID = std::size_t;

inline ComponentID getComponentID() 
{
    static ComponentID lastID = 0;
    return lastID++;
}

// Returns unique ComponentID based on (component) type passed.
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentID();
    return typeID;
}

// Define maximum number of components
constexpr std::size_t maxComponents = 32;
// typedef an `std::bitset` for our components:
using ComponentBitSet = std::bitset<maxComponents>;
// typedef an std::array
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};

class Entity
{
private:
    bool active = true;
    // List of components.
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
public:
    void update()
    {
        for(auto& c : components) c->update();
    }
    void draw() {
        for(auto& c : components) c->draw();
    }
    bool isActive() const { return active; }
    void destroy() {active = false; }

    // Check if entity has component by qerying bitset
    template <typename T> 
    bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        // ensure Entity doesnt already have component
        assert(!hasComponent<T>());

        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));

        // Add component of type T to bitset and array
        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template<typename T> 
    T& getComponent() const
    {
        assert(hasComponent<T>());
        auto ptr(componentArray[getComponentTypeID<T>()]);
        // ptr is a pointer to a base class component, so then we need to cast it to the
        // more specific component class that we are looking for
        return *static_cast<T*>(ptr);
    }
};

class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
public:
    void update()
    {
        for (auto& e : entities) e->update();
    }
    void draw()
    {
        for (auto& e : entities) e->draw();
    }

    void refresh() 
    {
        entities.erase(
            std::remove_if(std::begin(entities), std::end(entities),
                [](const std::unique_ptr<Entity> &mEntity)
                {
                    return !mEntity->isActive();
                }),
            std::end(entities));
    }
    Entity& addEntity()
    {
        Entity* e = new Entity();
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};