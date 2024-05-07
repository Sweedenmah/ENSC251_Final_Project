#ifndef NODE_HPP
#define NODE_HPP

template <class T>
class Node
{
public:
    Node<T>(T *right)
    {
        link = nullptr;
        data = right;
    }
    ~Node<T>()
    {
        //if (data != nullptr)
        //{
        //    delete data;
        //}
        //data = nullptr;
    }
    void setLink(Node<T> *linkInput)
    {
        link = linkInput;
    }
    T *getDataPtr() const
    {
        return data;
    }

    Node<T> *getLink()
    {
        return link;
    }

private:
    T *data;
    Node<T> *link;
};

#endif //NODE_HPP