#ifndef RPC_MAP_H_
#define RPC_MAP_H_

namespace rpc {

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 private:
  typedef struct Node {
    key_type key;
    mapped_type data;
    Node *left;
    Node *right;
    Node *parent;

    Node() : left(nullptr), right(nullptr), parent(nullptr) {}
    Node(const key_type &key, const mapped_type &data)
        : key(key),
          data(data),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}

  } Node;

  Node *root_ = nullptr;
  size_type size_ = 0;

 public:
  template <typename key_type, typename mapped_type>
  class MapIterator {
   public:
    Node *m_node;

   public:
    MapIterator(Node *node) : m_node(node) {};
    MapIterator &operator*();
    MapIterator &operator++();
    MapIterator &operator--();
    bool operator==(const MapIterator &other) const;
    bool operator!=(const MapIterator &other) const;
  };
  template <typename key_type, typename mapped_type>
  class MapConstIterator : public MapIterator<key_type, mapped_type> {
    const Node *m_node;

   public:
    MapConstIterator(Node *node) : m_node(node) {};
    MapConstIterator &operator*();
    MapConstIterator &operator++();
    MapConstIterator &operator--();
  };
  using iterator = MapIterator<key_type, mapped_type>;
  using const_iterator = MapConstIterator<key_type, mapped_type>;

 private:
  void changeConnections(iterator pos);
  Node *CopyTree(const Node &node, Node *parent = nullptr);
  Node *insertRecursive(Node *&current,
                        const std::pair<const key_type, mapped_type> &value,
                        Node *parent = nullptr);

 public:
  map();
  map(std::initializer_list<std::pair<const key_type, mapped_type>> const
          &items);
  map(const map &m);
  map(map &&m);
  ~map();
  map &operator=(map &&m) noexcept;

  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();

  std::pair<iterator, bool> insert(
      const std::pair<const key_type, mapped_type> &value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);

  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);
  iterator find(const key_type &key);
  bool contains(const key_type &key);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};
}  // namespace rpc

#include "rpc_map.cpp"

#endif  // _RPC_MAP_H_
