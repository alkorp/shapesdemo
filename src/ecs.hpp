#pragma once

/**
 * Incomplete, bare minimum ECS (Entity-Component-System) registry example
 */

#include <any>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

using Entity = std::size_t;

class Registry;

template<typename T>
class ComponentAdapter {
    using Data = std::unordered_map<Entity, std::any>;
    
    class Iterator {
        using value_type = std::pair<const Entity, T&>;
    public:
        value_type operator*() const {
            auto&& [first, second] = *source_it;
            return value_type{first, std::any_cast<T&>(second)};
        }
        Iterator& operator++() { source_it++; return *this; }  

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.source_it == b.source_it; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.source_it != b.source_it; };
    private:
        friend class ComponentAdapter<T>;
        explicit Iterator(Data::iterator it): source_it{it} {};
        Data::iterator source_it;
    };
    Data& data_;
    explicit ComponentAdapter(Data& data): data_(data) {};
    friend class Registry;
public:
    Iterator begin() {return Iterator(data_.begin());}
    Iterator end() {return Iterator(data_.end()); }
};

class Registry {
public:
    auto create() {
        static std::size_t counter = 0;
        return ++counter;
    }

    template<typename T>
    T& addComponent(size_t ent) {
        auto& bucket = data_[std::type_index(typeid(T))];
        std::any& val = bucket[ent];
        val = T{};
        return std::any_cast<T&>(val);
    }

    template<typename T>
    T* getComponent(Entity entity) {
        try {
            return std::any_cast<T>(&data_.at(std::type_index(typeid(T))).at(entity));
        } catch (const std::out_of_range&) {
            return nullptr;
        }
    }
    template <typename T>
    ComponentAdapter<T> view() {
        return ComponentAdapter<T>(data_[std::type_index(typeid(T))]);
    }

private:
    std::unordered_map<std::type_index, std::unordered_map<size_t, std::any>> data_;
};
