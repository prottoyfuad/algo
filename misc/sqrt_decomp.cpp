
void sqrt_decomp() {
  const int nax = 1e5;
  vector<int> queries(nax), order(nax);

  vector<int> f(nax);
  int distinct = 0;

  auto add = [&](int x) {
    x = a[x];
    distinct += f[x] == 0;
    f[x]++;
  };

  auto remove = [&](int x) {
    x = a[x];
    f[x]--;
    distinct -= f[x] == 0;
  };

  vector<int> answer(q);
  int x = 0, y = 0;

  for (int i = 0; i < q; i++) {
    auto [l, r] = queries[order[i]];
 
    while(l < x) add(--x);
    while(l > x) remove(x++);

    while(r < y) remove(--y);
    while(r > y) add(y++);
 
    answer[order[i]] = distinct;
  }
}

