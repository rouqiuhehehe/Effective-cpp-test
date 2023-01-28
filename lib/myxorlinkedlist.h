//
// Created by admin on 2023/1/19.
//

#ifndef CPP_TEST_MY_CLASS_MYXORLINKEDLIST_H_
#define CPP_TEST_MY_CLASS_MYXORLINKEDLIST_H_

#include <utility>
#include "address.h"
#include "log.h"
#include <functional>

template <class T>
class MyXORLinkedList
{
    typedef const T &Item;
public:
    class Node
    {
        friend class MyXORLinkedList <T>;
    public:
        explicit Node (Item it) noexcept
            : node(it)
        {
        }

        const T &operator* () const
        {
            return node;
        }
        T &operator* ()
        {
            return node;
        }
        const T *operator-> () const
        {
            return addressOf(node);
        }
        T *operator-> ()
        {
            return addressOf(node);
        }
    private:
        T node;
        Node *XORPoint = nullptr;
    };
public:
    typedef const std::function <void (Item &)> &Callback;
    typedef const std::function <bool (Node *)> &PrivateCallback;

    MyXORLinkedList () = default;
    MyXORLinkedList (const MyXORLinkedList &rhs)
    {
        swap(this, rhs);
    };
    MyXORLinkedList &operator= (const MyXORLinkedList &rhs)
    {
        if (this == *rhs)
            return *this;

        swap(this, rhs);
        return *this;
    };
    ~MyXORLinkedList () noexcept
    {
        clear();
    }

    void clear () noexcept
    {
        // 遍历需要基于上一个节点，所以不能先把节点删除
        Node *arr[size()];
        int i = 0;
        _traverse(
            [&arr, &i] (Node *node) {
                arr[i++] = node;
                return true;
            }
        );
        for (int j = 0; j < i; ++j)
            delete arr[j];
        front = nullptr;
        rear = nullptr;
        _size = 0;
    };

    void push (Item item)
    {
        insert(item, _size);
    }
    void unshift (Item item)
    {
        insert(item, 0);
    }

    void insert (Item item, std::size_t pos)
    {
        pos = pos >= _size ? _size : pos;
        if (pos == 0)
            addFront(item);
        else if (pos == _size)
            addRear(item);
        else
        {
            int i = 0;

            Node *prev = nullptr;
            auto *curr = front;
            Node *next;

            while (curr)
            {
                next = XOR(prev, curr->XORPoint);
                if (i == pos - 1)
                {
                    Node *node = new Node(item);
                    node->XORPoint = XOR(curr, next);
                    curr->XORPoint = XOR(XOR(curr->XORPoint, next), node);
                    next->XORPoint = XOR(node, XOR(curr, next->XORPoint));

                    break;
                }
                prev = curr;
                curr = next;
                i++;
            }
        }
        _size++;
    }

    void traverse (Callback callback)
    {
        if (!size())
            return;
        Node *prev = nullptr;
        auto *curr = front;
        Node *next;

        while (curr)
        {
            callback(**curr);

            next = XOR(prev, curr->XORPoint);
            prev = curr;
            curr = next;
        }
    }

    [[nodiscard]] std::size_t size () const
    {
        return _size;
    }

    template <class U>
    friend void swap (MyXORLinkedList <U> &, MyXORLinkedList <U> &);
#if __cplusplus >= 201103
    MyXORLinkedList (MyXORLinkedList &&rhs) noexcept
    {
        swap(this, rhs);
        rhs.clear();
    }

    MyXORLinkedList &operator= (MyXORLinkedList &&rhs) noexcept
    {
        if (this == &rhs)
            return *this;

        swap(this, rhs);
        rhs.clear();
        return *this;
    }
#endif
private:
    static Node *XOR (const Node *a, const Node *b)
    {
        return reinterpret_cast<Node *>((uintptr_t)a ^ (uintptr_t)b);
    }

    void addFront (Item item)
    {
        auto *node = new Node(item);
        node->XORPoint = XOR(nullptr, front);

        if (front)
            front->XORPoint = XOR(node, front->XORPoint);
        else
            rear = node;

        front = node;
    }

    void addRear (Item item)
    {
        auto *node = new Node(item);
        node->XORPoint = XOR(rear, nullptr);

        rear->XORPoint = XOR(rear->XORPoint, node);

        rear = node;
    }

    void _traverse (PrivateCallback callback)
    {
        if (!size())
            return;
        Node *prev = nullptr;
        auto *curr = front;
        Node *next;

        while (curr)
        {
            if (!callback(curr))
                break;
            next = XOR(prev, curr->XORPoint);
            prev = curr;
            curr = next;
        }
    }
private:
    Node *rear = nullptr;
    Node *front = nullptr;
    std::size_t _size = 0;
};
template <class T>
inline void swap (MyXORLinkedList <T> &lhs, MyXORLinkedList <T> &rhs)
{
    using std::swap;
    swap(lhs.rear, rhs.rear);
    swap(lhs.front, rhs.front);
    swap(lhs._size, rhs._size);
}

#endif //CPP_TEST_MY_CLASS_MYXORLINKEDLIST_H_
