#ifndef DLL_HPP
#define DLL_HPP

#include <iostream>
#include <limits>

template <typename T>
class DLL {
    private:
        struct Node {
            T val;
            Node* next;
            Node* prev;

            Node(T _val = T(), Node* n = nullptr, Node* p = nullptr) : val{_val}, next{n}, prev{p} {}
            template <typename... Args>
            Node(Node* n, Node* p, Args&&... args) : val{std::forward<Args>(args)...}, next{n}, prev{p} {}
        }; 
        
        Node* sentinel;
        size_t size = 0;

    public:
        class Iter {
            private:
                Node* curr;
            public:
                friend class DLL<T>;

                Iter(Node* c) : curr{c} {}
                Iter(const Iter& other) : curr{other.curr} {}
                
                bool operator !=(Iter other) const { return curr != other.curr; }  
                bool operator ==(Iter other) const { return curr == other.curr; }                        
                
                Iter& operator++() { 
                    curr = curr->next; 
                    return *this;
                }
                Iter operator++(int) { 
                    Iter tmp{curr}; 
                    curr = curr->next;   
                    return tmp;
                }
                Iter& operator--() { 
                    curr = curr->prev; 
                    return *this;
                }
                Iter operator--(int) { 
                    Iter tmp{curr}; 
                    curr = curr->prev;   
                    return tmp;
                }
                T& operator*() const { return curr->val; }
                T* operator->() const { return &(curr->val); }
        };
         
        class const_Iter {
            private:
                const Node* curr;
            public:
                friend class DLL<T>;

                const_Iter(Node* c) : curr{c} {}
               
                bool operator !=(const_Iter other) const { return curr != other.curr; }  
                bool operator ==(const_Iter other) const { return curr == other.curr; }                        
                
                const_Iter& operator++() { 
                    curr = curr->next; 
                    return *this;
                }
                const_Iter operator++(int) { 
                    const_Iter tmp{curr}; 
                    curr = curr->next;   
                    return tmp;
                }
                const_Iter& operator--() { 
                    curr = curr->prev; 
                    return *this;
                }
                const_Iter operator--(int) { 
                    const_Iter tmp{curr}; 
                    curr = curr->prev;   
                    return tmp;
                }
                const T& operator*() const { return curr->val; }
                const T* operator->() const { return &(curr->val); }
        };

        class reverse_Iter {
            private:
                Iter curr_iter;
            public:
                friend class DLL<T>;

                reverse_Iter(Iter c) : curr_iter{c} {}
                
                bool operator !=(reverse_Iter other) const { return curr_iter != other.curr_iter; }  
                bool operator ==(reverse_Iter other) const { return curr_iter == other.curr_iter; }                        
               
                reverse_Iter& operator++() { 
                    --curr_iter;
                    return *this;
                }
                reverse_Iter operator++(int) { 
                    reverse_Iter tmp{curr_iter}; 
                    --curr_iter;   
                    return tmp;
                }
                reverse_Iter& operator--() { 
                    ++curr_iter;
                    return *this;
                }
                reverse_Iter operator--(int) { 
                    reverse_Iter tmp{curr_iter}; 
                    ++curr_iter;   
                    return tmp;
                }
                T& operator*() const { 
                    auto tmp = curr_iter;
                    --tmp;
                    return *tmp;
                }
                T* operator->() const { 
                    auto tmp = curr_iter;
                    --tmp;
                    return tmp.operator->(); 
                }
        };

        class const_reverse_Iter {
            private:
                const_Iter curr_iter;
            public:
                friend class DLL<T>;

                const_reverse_Iter(const_Iter c) : curr_iter{c} {}
               
                bool operator !=(const_reverse_Iter other) const { return curr_iter != other.curr_iter; }  
                bool operator ==(const_reverse_Iter other) const { return curr_iter == other.curr_iter; }                        
               
                const_reverse_Iter& operator++() { 
                    --curr_iter;
                    return *this;
                }
                const_reverse_Iter operator++(int) { 
                    const_reverse_Iter tmp{curr_iter}; 
                    --curr_iter;   
                    return tmp;
                }
                const_reverse_Iter& operator--() { 
                    ++curr_iter;
                    return *this;
                }
                const_reverse_Iter operator--(int) { 
                    const_reverse_Iter tmp{curr_iter}; 
                    ++curr_iter;   
                    return tmp;
                }
                const T& operator*() const { 
                    auto tmp = curr_iter;
                    --tmp;
                    return *tmp;
                }
                const T* operator->() const { 
                    auto tmp = curr_iter;
                    --tmp;
                    return tmp.operator->(); 
                }
        };

        Iter begin() const {
            return Iter{sentinel->next};
        }
        
        Iter end() const {
            return Iter{sentinel};
        }

        const_Iter cbegin() const {
            return const_Iter{sentinel->next};
        }
        
        const_Iter cend() const {
            return const_Iter{sentinel};
        }

        reverse_Iter rbegin() const {
            return reverse_Iter{end()};
        }

        reverse_Iter rend() const {
            return reverse_Iter{begin()};
        }

        const_reverse_Iter crbegin() const {
            return const_reverse_Iter{end()};
        }

        const_reverse_Iter crend() const {
            return const_reverse_Iter{begin()};
        }

        DLL();
        DLL(size_t count, const T& _val);
        DLL(std::initializer_list<T> init);
        DLL(Iter first,Iter last);
        DLL(const DLL& other);
        DLL(DLL&& other) noexcept;
        ~DLL();

        DLL& operator=(const DLL& other);
        DLL& operator=(DLL&& other) noexcept;
        DLL& operator=(std::initializer_list<T> init);  
        void assign(size_t count, const T& _val);
        void assign(std::initializer_list<T> init);
       
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
       
        bool empty () const noexcept { return sentinel->next == sentinel; }
        size_t get_size() const noexcept { return size; }
        size_t max_size() const noexcept { return std::numeric_limits<size_t>::max(); } 
        Node* get_sentinel()const noexcept { return sentinel; }


        void clear() noexcept;
        void push_back(const T& value);
        void push_back(T&& value);
        void pop_back();
        void push_front(const T& value);
        void push_front(T&& value);
        void pop_front();
        void resize(size_t count );
        void resize(size_t count, const T& value);
        void swap(DLL& other ) noexcept;
        Iter insert(Iter pos, const T& value);
        Iter insert(Iter pos, T&& value );
        Iter insert(Iter pos, size_t count, const T& value );
        Iter insert(Iter pos, std::initializer_list<T> ilist);
        Iter insert(Iter pos, Iter first, Iter last);
        Iter erase(Iter pos);
        Iter erase(Iter first, Iter last);
        void splice(Iter pos, DLL& other);
        void splice(Iter pos, DLL&& other);
        void splice(Iter pos, DLL& other, Iter it);
        void splice(Iter pos, DLL&& other, Iter it);
        void splice(Iter pos, DLL& other, Iter first,Iter last);
        void splice(Iter pos, DLL&& other, Iter first, Iter last);
        template <typename... Args>
        void emplace_back(Args&&... args);
        template <typename... Args>
        void emplace_front(Args&&... args);
        template <typename... Args>
        void emplace(Iter pos, Args&&... args);


        
        void merge(DLL& other);
        size_t remove(const T& value);
        void reverse();
        void unique();

        template <typename U>
        friend bool operator==(const DLL<U>& l,const DLL<U>& r);
        template <typename U>
        friend bool operator!=(const DLL<U>& l,const DLL<U>& r) { return !(l == r); }
        template <typename U>
        friend bool operator<(const DLL<U>& l,const DLL<U>& r);
        template <typename U>
        friend bool operator<=(const DLL<U>& l,const DLL<U>& r) { return !(r < l); }
        template <typename U>
        friend bool operator>(const DLL<U>& l,const DLL<U>& r) { return r < l; }
        template <typename U>
        friend bool operator>=(const DLL<U>& l,const DLL<U>& r) { return !(l < r); }
};

template <typename T>
void DLL<T>::clear() noexcept {
    erase(begin(), end());
}

template <typename T>
void DLL<T>::push_back(const T& value) {
    insert(end(), value); 
}

template <typename T>
void DLL<T>::push_back(T&& value) {
    insert(end(), std::move(value));
}

template <typename T>
void DLL<T>::pop_back() {
    erase(--end());
}

template <typename T>
void DLL<T>::push_front(const T& value) {
    insert(begin(), value);
}

template <typename T>
void DLL<T>::push_front(T&& value) {
    insert(begin(), std::move(value));
}

template <typename T>
void DLL<T>::pop_front() {
    erase(begin());
}

template <typename T>
void DLL<T>::resize(size_t count) {
    if (count == size) return;
    
    if (size > count) {
        for (size_t i{}; i < size - count; ++i) 
            pop_back();
    }

    else if (size < count) {
        for (size_t i{}; i < count - size; ++i) 
            push_back(T());
    }
}

template <typename T>
void DLL<T>::resize(size_t count, const T& value) {
    if (count == size) return;
    
    if (size > count) {
        for (size_t i{}; i < size - count; ++i) 
            pop_back();
    }

    else if (size < count) {
        for (size_t i{}; i < count - size; ++i) 
            push_back(value);
    }
}

template <typename T>
void DLL<T>::swap(DLL& other) noexcept {
    std::swap(sentinel,other.sentinel);
    std::swap(size,other.size);
}

template <typename T>
typename DLL<T>::Iter DLL<T>::insert(Iter pos, const T& value) {
    auto* ins = pos.curr;

    auto* newNode = new Node(ins, ins->prev, value);
    ins->prev->next = newNode;
    ins->prev = newNode;
    
    ++size;
    return Iter(newNode);
}

template <typename T>
typename DLL<T>::Iter DLL<T>::insert(Iter pos, T&& value) {
    auto* ins = pos.curr;

    auto* newNode = new Node(ins, ins->prev, std::move(value));
    ins->prev->next = newNode;
    ins->prev = newNode;
    
    ++size;
    return Iter(newNode);
}

template <typename T>
typename DLL<T>::Iter  DLL<T>::insert(Iter pos, size_t count, const T& value ) {
    int i{};
    auto ans = pos;
    for (size_t j{}; j < count; ++j) {
        auto ret = insert(pos,value);
        if (i++ == 0) ans = ret;
    }
    return ans;
}

template <typename T>
typename DLL<T>::Iter DLL<T>::insert(Iter pos, std::initializer_list<T> ilist) {
    int i{};
    auto ans = pos;
    for (auto i : ilist) {
        auto ret = insert(pos,i);
        if (i++ == 0) ans = ret; 
    }
    return ans;
}

template <typename T>
typename DLL<T>::Iter DLL<T>::insert(Iter pos, Iter first, Iter last) {
    int i{};
    auto ans = pos;
    for (auto it = first; it != last; ++it) {
        auto ret = insert(pos, *it);
        if (i++ == 0) ans = ret;
    }
    return ans;
}

template <typename T>
typename DLL<T>::Iter DLL<T>::erase(Iter pos) {
    if(empty() || pos.curr == sentinel) return pos;
    --size;
     
    auto* tmp = pos.curr;
    auto it = Iter(tmp->next);
    
    tmp->next->prev = tmp->prev;
    tmp->prev->next = tmp->next;
    
    delete tmp;
    return it;
}

template <typename T>
typename DLL<T>::Iter DLL<T>::erase(Iter first, Iter last) {
    if (first == last) return last;
    auto ans = first;;
    for (auto it = first; it != last; it = ans) {
        ans = erase(it);
    }
    return ans;
}

template <typename T>
void DLL<T>::splice(Iter pos, DLL& other) {
    if (this == &other || other.empty()) return;

    Node* ins = pos.curr;
    Node* first = other.sentinel->next;
    Node* last = other.sentinel->prev;

    other.sentinel->next = other.sentinel;
    other.sentinel->prev = other.sentinel;

    Node* prevNode = ins->prev;

    prevNode->next = first;
    first->prev = prevNode;

    last->next = ins;
    ins->prev = last;

    size += other.size;
    other.size = 0;
}

template <typename T>
void  DLL<T>::splice(Iter pos, DLL&& other) {
    splice(pos,other);
}

template <typename T>
void  DLL<T>::splice(Iter pos, DLL& other, Iter it) {
    if (this == &other && (pos == it || pos.curr == it.curr->next)) return;
    
    Node* ins = pos.curr;
    Node* prevNode = ins->prev;

    Node* tmp = it.curr;
    Node* tmpPrev = tmp->prev;
    tmpPrev->next = tmp->next;
    tmp->next->prev = tmpPrev;
    --other.size;
    
    prevNode->next = tmp;
    ins->prev = tmp;
    tmp->next = ins;
    tmp->prev = prevNode;
    ++size;
}

template <typename T>
void  DLL<T>::splice(Iter pos, DLL&& other, Iter it) {
    splice(pos,other,it);
}

template <typename T>
void DLL<T>::splice(Iter pos, DLL& other, Iter first, Iter last) {
    if (first == last) return;

    Node* firstNode = first.curr;
    Node* lastNode  = last.curr->prev; 
    Node* srcBefore = firstNode->prev;
    Node* srcAfter  = last.curr;

    Node* ins = pos.curr;
    Node* destPrev = ins->prev;

    srcBefore->next = srcAfter;
    srcAfter->prev = srcBefore;

    destPrev->next = firstNode;
    firstNode->prev = destPrev;
    
    lastNode->next = ins;
    ins->prev = lastNode;

    if (this != &other) {
        size_t count = 0;
        for (auto it = first; it != last; ++it) ++count;
        size += count;
        other.size -= count;
    }
}
template <typename T>
void DLL<T>::splice(Iter pos, DLL&& other, Iter first, Iter last) {
    splice(pos,other,first,last);
}

template <typename T>
template <typename... Args>
void DLL<T>::emplace_back(Args&&... args) {
    ++size;
    auto* tmp = new Node(sentinel, sentinel->prev, std::forward<Args>(args)...);
    sentinel->prev->next = tmp;
    sentinel->prev = tmp;
}

template <typename T>
template <typename... Args>
void DLL<T>::emplace_front(Args&&... args) {
    ++size;
    auto* tmp = new Node(sentinel->next, sentinel, std::forward<Args>(args)...);
    sentinel->next->prev = tmp;
    sentinel->next = tmp;
}

template <typename T>
template <typename... Args>
void DLL<T>::emplace(Iter pos, Args&&... args) {
    auto* ins = pos.curr;

    auto* newNode = new Node(ins, ins->prev, std::forward<Args>(args)...);
    ins->prev->next = newNode;
    ins->prev = newNode;
    
    ++size;
}

template <typename T>
DLL<T>::DLL() : sentinel{new Node} {
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
}

template <typename T>
DLL<T>::DLL(size_t count, const T& _val) : DLL() {
    for (size_t i{}; i < count; ++i) {
        push_back(_val);
    }
}

template <typename T>
DLL<T>::DLL(std::initializer_list<T> init) : DLL() {
    for (auto i : init) {
        push_back(i);
    }
}

template <typename T>    
DLL<T>::DLL(Iter first,Iter last) : DLL() {
    insert(begin(), first, last);
}

template <typename T>
DLL<T>::DLL(const DLL& other) : DLL() {
    const auto* tmp = other.sentinel->next;
    while (tmp != other.sentinel) {
        push_back(tmp->val);
        tmp = tmp->next;
    }
}

template <typename T>
DLL<T>::DLL(DLL&& other) noexcept : sentinel{other.sentinel}, size{other.size} {
    other.sentinel = new Node(); 
    other.sentinel->next = other.sentinel;
    other.sentinel->prev = other.sentinel;
    other.size = 0;
}

template <typename T>
DLL<T>::~DLL() {
    clear();
    delete sentinel;
}

template <typename T>
DLL<T>& DLL<T>::operator=(const DLL& other) {
    if (this != &other) {
        clear();
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        const auto* tmp = other.sentinel->next;
        while (tmp != other.sentinel) {
            push_back(tmp->val);
            tmp = tmp->next;
        }
    }
    return *this;
}

template <typename T>
DLL<T>& DLL<T>::operator=(DLL&& other) noexcept {
    if (this != &other) {
        clear();
        sentinel = other.sentinel;
        size = other.size;
        other.sentinel = new Node(); 
        other.sentinel->next = other.sentinel;
        other.sentinel->prev = other.sentinel;
        other.size = 0;
    }
    return *this;
}

template <typename T>
DLL<T>& DLL<T>::operator=(std::initializer_list<T> init) {
    clear();
    for (auto i : init) {
        emplace_back(i);
    }
    return *this;
}

template <typename T>
void DLL<T>::assign(size_t count, const T& _val) {
    DLL<T> tmp(count,_val);
    swap(tmp); 
}

template <typename T>
void DLL<T>::assign( std::initializer_list<T> init) {
    DLL<T> tmp(init);
    swap(tmp);
}

template <typename T>
T& DLL<T>::front() {
    if (empty()) throw std::logic_error("Can't get empty list's first element.");
    return sentinel->next->val;
}

template <typename T>
const T& DLL<T>::front() const {
    if (empty()) throw std::logic_error("Can't get empty list's first element.");
    return sentinel->next->val;
}

template <typename T>
T& DLL<T>::back() {
    if (empty()) throw std::logic_error("Can't get empty list's last element.");
    return sentinel->prev->val;
}

template <typename T>
const T& DLL<T>::back() const {
    if (empty()) throw std::logic_error("Can't get empty list's last element.");
    return sentinel->prev->val;
}

template <typename T>
bool operator==(const DLL<T>& l,const DLL<T>& r) {
    if (l.get_size() != r.get_size()) return false;
   
    auto* tmp1 = l.get_sentinel()->next;
    auto* tmp2 = r.get_sentinel()->next; 
    
    while (tmp1 != l.get_sentinel()) {
        if(tmp1->val != tmp2->val) return false;
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    return true;
}

template <typename T>
bool operator<(const DLL<T>& l,const DLL<T>& r) {    
    auto* tmp1 = l.get_sentinel()->next;
    auto* tmp2 = r.get_sentinel()->next; 
    
    while (tmp1 != l.get_sentinel() && tmp2 != r.get_sentinel()) {
        if(tmp1->val < tmp2->val) return true;
        else if(tmp1->val > tmp2->val) return false;
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    if (l.get_size() < r.get_size()) return true;
    return false;
}

template <typename T>
void DLL<T>::merge(DLL& other) {
    if (this == &other) return;
    if (empty()) { 
        swap(other);
        return;
    }

    size += other.size;
    auto* tmp1 = sentinel->next;
    auto* current = other.sentinel->next;

    while (current != other.sentinel) {
        auto* tmp2 = current;
        if (tmp2->val >= tmp1->val) {
            if (tmp1 == sentinel->prev) { 
                current = current->next;
                tmp2->next = sentinel;
                tmp2->prev = tmp1;
                tmp1->next = tmp2;
                sentinel->prev = tmp2;
            }
            tmp1 = tmp1->next;
            continue;
        }
        
        current = current->next;        
        
        tmp2->next = tmp1;
        tmp2->prev = tmp1->prev;
        tmp1->prev->next = tmp2;
        tmp1->prev = tmp2; 
    }
    other.sentinel->next = other.sentinel;
    other.sentinel->prev = other.sentinel;
    other.size = 0;
}

template <typename T>
size_t DLL<T>::remove(const T& value) {
    if (empty()) return 0;
    
    size_t count = 0;
    auto* tmp = sentinel->next;

    while (tmp != sentinel) {
        if (tmp ->val == value) {
            auto* current = tmp;
            
            current->next->prev = current->prev;
            current->prev->next = current->next;
            tmp = tmp->next;
            delete current;
            
            ++count;
            --size;
        }
        else { 
            tmp = tmp->next;
        }
    }
    return count;
}

template <typename T>
void DLL<T>::reverse() {
    if (empty()) return;
    
    auto* tmp = sentinel->next;
    while (tmp != sentinel) {
        std::swap(tmp->next,tmp->prev);
        tmp = tmp->prev;
    }   
    std::swap(sentinel->next,sentinel->prev);
}

template <typename T>
void DLL<T>::unique() {
    if (empty()) return;
    
    auto* tmp = sentinel->next;
    while (tmp != sentinel->prev) {
        if (tmp->val == tmp->next->val) {
            auto* tmp2 = tmp->next;

            tmp2->next->prev = tmp;
            tmp->next = tmp2->next;
            
            delete tmp2;
            --size;
        }
        else tmp = tmp->next;
    }
}

#endif
