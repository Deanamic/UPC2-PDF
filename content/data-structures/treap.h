struct Tree {
  Tree *left, *right, *parent; // if parent needed.
  ll x, y, count;
  Tree (ll x) : x(x), y(rand()), count(1) {
    left = right = parent = nullptr;
  }
};

inline int card(Tree* t) {return (t ? t->count : 0);}
inline void setp(Tree *t, Tree *p) {
  if(t) t->parent = p; }

void update(Tree* t) { //Update when pointers change
  if (!t) return;
  t->count = 1 + card(t->left) + card(t->right);
  setp(t->left, t);
  setp(t->right, t);
}

Tree* merge(Tree* t1, Tree* t2) {
  if (t1 == nullptr) return t2;
  if (t2 == nullptr) return t1;
  if (t1->y >= t2->y) {
    t1->right = merge(t1->right, t2);
    update(t1);
    return t1;
  } else {
    t2->left = merge(t1, t2->left);
    update(t2);
    return t2;
  }
}

// leaves on the left all nodes less than x.
pair<Tree*, Tree*> split(Tree* t, ll x) {
  if (t == nullptr) return {nullptr, nullptr};
  if (t->x < x) {// if (card(t->left) + 1 <= x) {
  // auto p = split(t->right, x - card(t->left) - 1);
    auto p = split(t->right, x);
    t->right = p.first;
    update(t);
    setp(t, nullptr);
    return {t, p.second};
  } else {
    auto p = split(t->left, x);
    t->left = p.second;
    update(t);
    setp(t, nullptr);
    return {p.first, t};
  }
}

Tree* insert(Tree* t, Tree* n) {
  auto p = split(t, n->x);
  t = merge(p.first, n);
  t = merge(t, p.second);
  return t;
}

// Devuelve cuantos hay <= x
int count(Tree* t, int x) {
  if (!t) return 0;
  if (t->x <= x) 
    return 1 + card(t->left) + count(t->right, x);
  else return count(t->left, x);
}

Tree* update_node(Tree* &root, Tree* node, ll nx) {
  setp(node->left, nullptr);
  setp(node->right, nullptr);
  auto m = merge(node->left, node->right);
  auto p = node->parent;
  node->left = node->right = node->parent = nullptr;
  node->x = nx;
  update(node);
  if (p) {
    p->left == node ? p->left = m : p->right = m;
    if (m) m->parent = p;
    while (p) { update(p); p = p->parent; }
  } else {
    root = m;
  }
  return insert(root, node);
}

int main() {
  int n; cin >> n;
  vector<Tree*> nodes(n);
  Tree* treap = nullptr;
  for (int i = 0; i < n; ++i) {
    ll x; cin >> x;
    Tree* n = new Tree(x);
    update(n);
    nodes[i] = n;
    treap = insert(treap, n);
  }
  int m; cin >> m; // Update k-th node with value x
  for (int i = 0; i < m; ++i) {
    int k; ll x; cin >> k >> x;
    Tree* t = nodes[k-1];
    treap = update_node(treap, t, x);
  }
}
