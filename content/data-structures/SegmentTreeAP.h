/**
 * Author: Dean Zhu
 * Date: 2018-11-28
 * License: CC0
 * Source: https://github.com/radoslav11/Coding-Library/blob/master/data_structures/segment_tree_AP.cpp
 * Description: Update adds a arithmetic progression.
 */

struct SegTreeAp {
  struct Node {
    int sum, lazy, lazyAp;
    Node() {sum = 0; lazy = 0; lazyAp = 0;}
    Node(int val) {
      sum = val; lazy = 0; lazyAp = 0;
    }
    Node operator +(const Node& n) {
      Node ans;
      ans.sum = sum + n.sum;
      ans.lazy = ans.lazyAp = 0;
      return ans;
    }
  };
  vector<Node> S;
  SegTreeAp(int n) : S(4*n) {}

  void update(int id, int l, int r) {
    if(S[id].lazy) {
      S[id].sum += (r - l) * S[id].lazy;
      if(l + 1 != r) {
        S[id<<1].lazy += S[id].lazy;
        S[id<<1|1].lazy += S[id].lazy;
      }
      S[id].lazy = 0;
    }
    if(S[id].lazyAp) {
      int m = (l + r)>>1;
      S[id].sum += ((r - l) * (r - l + 1) / 2) * S[id].lazyAp;
      if(l + 1 != r) {
        S[id<<1].lazyAp += S[id].lazyAp;
        S[id<<1|1].lazyAp += S[id].lazyAp;
        S[id<<1|1].lazy += S[id].lazyAp * (m - l);
      }
      S[id].lazyAp = 0;
    }
  }

  void build(int id, int l, int r, vi& v) {
    if(l + 1 == r) {
      S[id] = Node(v[l]);
      return;
    }
    int m = (l + r)>>1;
    build(id<<1, l, m, v);
    build(id<<1|1, m, r, v);
    S[id] = S[id<<1] + S[id<<1|1];
  }

  void update(int id, int l, int r, int x, int y, int val, int prog) {
    update(id, l, r);
    if(l >= y || r <= x) return;
    if(l >= x && r <= y) {
      S[id].lazy += val + (l - x - 1)*prog;
      S[id].lazyAp += prog;
      update(id, l, r);
      return;
    }
    int m = (l + r)>>1;
    update(id<<1, l, m, x, y, val, prog);
    update(id<<1|1, m, r, x, y, val, prog);
    S[id] = S[id<<1] + S[id<<1|1];
  }

  Node query(int id, int l, int r, int x, int y) {
    update(id, l, r);
    if(l >= y || r <= x) return Node();
    if(l >= x && r <= y) return S[id];
    int m = (l + r)>>1;
    return query(id<<1, l, m, x, y) + query(id<<1|1, m, r, x, y);
  }
};
