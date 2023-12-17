// 2022.09.28
// Component Foundation Class

#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

#include <string>
#include <memory>
#include <random>
#include <chrono>
#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define sptr shared_ptr
#define wptr weak_ptr

template<typename T>
inline void free_container(T& _p_container)
{
    T empty;
    std::swap(_p_container, empty);
}

#define COMPONENT_ID size_t
class Component : public enable_shared_from_this<Component>
{
protected:
    COMPONENT_ID id;
    string name;
    string type;
    wptr<Component> parent;
    uint64_t depth;
private:
    vector<COMPONENT_ID> order;
    unordered_map<COMPONENT_ID, sptr<Component>> child_map;
    unordered_map<COMPONENT_ID, wptr<Component>> weak_map;
    unordered_map<string, COMPONENT_ID> name_map;
public:
    // Component Depth 반환 함수
    inline uint64_t get_depth()
    {
        return this->depth;
    }
    // Component ID 반환 함수
    inline COMPONENT_ID get_component_id()
    {
        return this->id;
    }
    // Component String Name 반환 함수
    inline string get_name()
    {
        return this->name;
    }
    // Component String Name 설정 함수
    inline void set_name(string _name)
    {
        this->name = _name;
    }
    // Component Type 반환 함수
    inline string get_component_type()
    {
        return this->type;
    }
    // Component Type 설정 함수
    inline void set_component_type(string _type)
    {
        this->type = _type;
    }
public:
    // 상위 Component 반환 함수
    template <class T>
    wptr<T> get_parent()
    {
        return static_pointer_cast<T>(parent.lock());
    }
    // 하위 Component 추가
    template <class T>
    wptr<T> add_component()
    {
        return add_component<T>("noname", false);
    }
    // 하위 Component 추가
    template <class T>
    wptr<T> add_component(string _name, bool unique_name = true)
    {
        sptr<T> comp = make_shared<T>();
        wptr<T> weak = comp;
        COMPONENT_ID target_id = comp->get_component_id();
        string new_name = _name;
        if (unique_name == true)
        {
            int cnt = 0;
            while (true)
            {
                bool flag = false;
                auto itr = name_map.find(new_name);
                if (itr != name_map.end())
                {
                    flag = true;
                }
                /*auto itr = weak_map.begin();
                while (itr != weak_map.end())
                {
                    string name = itr->second.lock()->get_name();
                    if (name == new_name)
                    {
                        flag = true;
                        break;
                    }
                    itr++;
                }*/
                if (flag == true)
                {
                    new_name = _name;
                    new_name.append("_");
                    new_name.append(to_string(cnt));
                    cnt++;
                }
                else break;
            }
        }
        comp->name = new_name;
        //comp->name = _name;
        comp->parent = shared_from_this();
        //find depth
        depth = 1;
        wptr<Component> depth_target = comp->parent.lock();
        while (true)
        {
            if (depth_target.lock() == nullptr) break;
            depth_target = depth_target.lock()->parent.lock();
            depth++;
        }
        order.push_back(comp->get_component_id());
        name_map.insert(pair<string, COMPONENT_ID>(comp->name, target_id));
        child_map.insert(pair<COMPONENT_ID, sptr<Component>>(target_id, std::move(comp)));
        weak_map.insert(pair<COMPONENT_ID, wptr<Component>>(target_id, weak));
        return weak;
    }
    // Component 하위 연결(weak pointer)
    template <class T>
    void link_component(wptr<T>& _target_module)
    {
        COMPONENT_ID target_id = _target_module.lock()->get_component_id();
        order.push_back(target_id);
        // weak map 연결
        weak_map.insert(pair<COMPONENT_ID, wptr<Component>>(target_id, _target_module));
        name_map.insert(pair<string, COMPONENT_ID>(_target_module.lock()->get_name(), target_id));
    }
    // Component ID로 하위 Component 찾아서 제거
    template <class T>
    void delete_component(COMPONENT_ID _id)
    {
        auto weak = weak_map.find(_id);
        if (weak != weak_map.end())
        {
            // name map에서 제거
            auto np = name_map.find(weak->second.lock()->get_name());
            if (np != name_map.end())
            {
                np = name_map.erase(np);
            }
            // Erase
            auto order_itr = order.begin();
            while (order_itr != order.end())
            {
                if ((*order_itr) == weak->first)
                {
                    order.erase(order_itr);
                    break;
                }
                order_itr++;
            }
            order.shrink_to_fit();
            weak->second.reset();
            weak = weak_map.erase(weak);
            // Child map 에서 원본 제거
            auto comp = child_map.find(_id);
            if (comp != child_map.end())
            {
                comp->second.reset();
                comp->second = nullptr;
                comp = child_map.erase(comp);
            }
        }
    }
    // Component Name으로 하위 Component 찾아서 제거
    template <class T>
    void delete_component(string _name)
    {
        auto weak = weak_map.begin();
        while (weak != weak_map.end())
        {
            auto sptr_comp = weak->second.lock();
            if (sptr_comp->name == _name)
            {
                // name map에서 제거
                auto np = name_map.find(sptr_comp->get_name());
                if (np != name_map.end())
                {
                    np = name_map.erase(np);
                }
                //Erase
                auto order_itr = order.begin();
                while (order_itr != order.end())
                {
                    if ((*order_itr) == weak->first)
                    {
                        order.erase(order_itr);
                        break;
                    }
                    order_itr++;
                }
                order.shrink_to_fit();
                // Child map 에서 원본 제거
                auto comp = child_map.find(weak->first);
                if (comp != child_map.end())
                {
                    comp->second.reset();
                    comp->second = nullptr;
                    comp = child_map.erase(comp);
                }
                weak->second.reset();
                weak = weak_map.erase(weak);
                continue;
            }
            weak++;
        }
    }
    // Find Component with ID (recursive = 상위 모든 객체 탐색(단일객체 탐색, Tree 아님)
    template <class T>
    wptr<T> find_component(COMPONENT_ID _id, bool recursive_search = false)
    {
        if (recursive_search == false)
        {
            auto itr = weak_map.find(_id);
            if (itr != weak_map.end()) return static_pointer_cast<T>(itr->second.lock());
        }
        else
        {
            sptr<Component> search_target = shared_from_this();
            while (true)
            {
                auto itr = search_target->weak_map.find(_id);
                if (itr != search_target->weak_map.end())
                {
                    return static_pointer_cast<T>(itr->second.lock());
                }
                else
                {
                    search_target = search_target->get_parent<Component>().lock();
                    if (!search_target) break;
                }
            }
        }
        return wptr<T>();
    }
    // Find Component with Component Name (recursive = 상위 모든 객체 탐색(단일객체 탐색, Tree 아님)
    template <class T>
    wptr<T> find_component(string _name, bool recursive_search = false)
    {
        if (recursive_search == false)
        {
            auto itr = weak_map.begin();
            while (itr != weak_map.end())
            {
                if (itr->second.lock()->name == _name)
                {
                    return static_pointer_cast<T>(itr->second.lock());
                }
                itr++;
            }
        }
        else
        {
            sptr<Component> search_target = shared_from_this();
            auto itr = search_target->weak_map.begin();
            while (true)
            {
                if (search_target->name == _name)
                {
                    return static_pointer_cast<T>(search_target);
                }
                itr = search_target->weak_map.begin();
                while (itr != search_target->weak_map.end())
                {
                    if (itr->second.lock()->name == _name)
                    {
                        return static_pointer_cast<T>(itr->second.lock());
                    }
                    itr++;
                }
                search_target = search_target->get_parent<Component>().lock();
                if (!search_target) break;
            }
        }
        return wptr<T>();
    }
    // Find Components with Component Type(Ordered)
    template <class T>
    deque<wptr<T>> find_components_with_type(string _type)
    {
        deque<wptr<T>> vec;
        auto itr = order.begin();
        while (itr != order.end())
        {
            auto weak = weak_map.find((*itr));
            if (weak->second.lock()->type.find(_type) != string::npos)
            {
                vec.push_back(static_pointer_cast<T>(weak->second.lock()));
            }
            else
            {
                auto vec_child = weak->second.lock()->find_components_with_type<T>(_type);
                for (int i = 0; i < vec_child.size(); i++) vec.push_back(vec_child[i]);
            }
            itr++;
        }
        return vec;
    }
public:
    // 생성자
    Component()
    {
        id = COMPONENT_ID(this);
        set_name("basic_component");
        set_component_type("basic_component");
        parent.reset();
    }
    // 소멸자
    ~Component()
    {
        size_t count = weak_map.size();
        auto weak = weak_map.begin();
        while (weak != weak_map.end())
        {
            auto child = child_map.find(weak->first);
            if (child != child_map.end())
            {
                child->second.reset();
                child->second = nullptr;
                child = child_map.erase(child);
            }
            weak->second.reset();
            weak = weak_map.erase(weak);
        }
        parent.reset();

        free_container(child_map);
        free_container(weak_map);
        free_container(order);
    }
};

#endif