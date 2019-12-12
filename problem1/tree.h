#pragma once

#include <memory>

namespace bintree {
    template <typename T>
    struct TNode: public std::enable_shared_from_this<TNode<T>> {
        using TNodePtr = std::shared_ptr<TNode<T>>;
        using TNodeConstPtr = std::shared_ptr<const TNode<T>>;

        // Чтобы избежать циклических ссылок
        using TWeakPtr = std::weak_ptr<TNode<T>>;

        bool hasLeft() const {
            return bool(left);
        }

        bool hasRight() const {
            return bool(right);
        }

        // Теперь parent -- weak_ptr
        bool hasParent() const {
            return not(bool(parent.expired()));
        }

        T& getValue() {
            return value;
        }

        const T& getValue() const {
            return value;
        }

        TNodePtr getLeft() {
            return left;
        }

        TNodeConstPtr getLeft() const {
            return left;
        }

        TNodePtr getRight() {
            return right;
        }

        TNodeConstPtr getRight() const {
            return right;
        }

        // Теперь parent -- weak_ptr
        TNodePtr getParent() {
            return static_cast<TNodePtr>(parent.lock());
        }

        // Теперь parent -- weak_ptr
        TNodeConstPtr getParent() const {
            return static_cast<TNodeConstPtr>(parent.lock());
        }

        // конструктор TNode перенесён из private в public,
        // чтобы вызов make_shared сработал
        static TNodePtr createLeaf(T v) {
            //return std::make_shared<TNode>(v);
            return std::shared_ptr<TNode>(new TNode(v));
        }

        // Изменены типы входных параметров
        // Теперь вместо сырых указателей -- "умные"
        static TNodePtr fork(T v, TNodePtr left, TNodePtr right) {
            //TNodePtr ptr = std::make_shared<TNode>(v, left, right);
            TNodePtr ptr = std::shared_ptr<TNode>(new TNode(v, left, right));
            setParent(ptr->getLeft(), ptr);
            setParent(ptr->getRight(), ptr);
            return ptr;
        }

        // Поправлена работа с this с помощью конструкции shared_from_this
        TNodePtr replaceLeft(TNodePtr l) {
            //setParent(l, std::enable_shared_from_this<TNode<T>>::shared_from_this());
            setParent(l, this->shared_from_this());
            setParent(left, nullptr);
            std::swap(l, left);
            return l;
        }

        // Поправлена работа с this с помощью конструкции shared_from_this
        TNodePtr replaceRight(TNodePtr r) {
            //setParent(r, std::enable_shared_from_this<TNode<T>>::shared_from_this());
            setParent(r, this->shared_from_this());
            setParent(right, nullptr);
            std::swap(r, right);
            return r;
        }

        TNodePtr replaceRightWithLeaf(T v) {
            return replaceRight(createLeaf(v));
        }

        TNodePtr replaceLeftWithLeaf(T v) {
            return replaceLeft(createLeaf(v));
        }

        TNodePtr removeLeft() {
            return replaceLeft(nullptr);
        }
        TNodePtr removeRight() {
            return replaceRight(nullptr);
        }
/*
		TNode(T v)
            : value(v) {}
        
        // сырые указатели заменены на "умные"
        // код перенесён из private в public,
        // чтобы вызов make_shared работал
        TNode(T v, TNodePtr left, TNodePtr right)
            : value(v)
            , left(left)
            , right(right) {}
*/
    private:
        T value;
        TNodePtr left = nullptr;
        TNodePtr right = nullptr;
        // Чтобы избежать циклических ссылок, используем weak_ptr
        TWeakPtr parent = TWeakPtr();

        TNode(T v)
            : value(v) {}
        
        // сырые указатели заменены на "умные"
        TNode(T v, TNodePtr left, TNodePtr right)
            : value(v)
            , left(left)
            , right(right) {}

        static void setParent(TNodePtr node, TNodePtr parent) {
            if (node)
                node->parent = parent;
        }
    };
}
