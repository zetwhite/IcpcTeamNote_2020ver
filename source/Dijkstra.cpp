// O(|E||log|V|)
// 알고스팟 최단거리문제에서 발췌함
// 마이너스로 저장하기 때문에 주의해야 됨!
FOR(i,101)
  FOR(j,101)
    adj[i][j] = -INF;

// adj[1][1] = 0;
// priority queue로 (최단거리, 시작지점, 끝지점) 저장
// 길이가 짧은 순으로 돌릴 예정이므로 마이너스로 저장.
// Ex) pq.top() =>  -1, -2, -3 vs 3, 2, 1 ...
pq.push(make_tuple(0,1,1)); // 1번부터 시작!
while(!pq.empty()) {
  int b = get<0>(pq.top()); // 최단거리
  int x = get<1>(pq.top()); // 시작지점
  int y = get<2>(pq.top()); // 끝지점
  if (x <= 0 || x > N || y <= 0 || y > M) { // 조건에서 벗어나면
    pq.pop();
    continue;
  }
  if (adj[x][y] >= b) { // 이미 설정된 최단거리보다 크면! (마이너스임)
    pq.pop();
    continue;
  }
  adj[x][y] = b; // 최단거리로 설정 후
  pq.pop();
  for (int i = 0; i < 4; i++) { // 인접한 노드를 전부 탐색하면서 최단거리 재설정
    int move_x = x + dir[i][0];
    int move_y = y + dir[i][1];
    int move_b = (board[move_x][move_y] == true) ? b - 1 : b;
    pq.push(make_tuple(move_b, move_x, move_y));
  }
}
// 거의 최단거리의 경우 한번 최단거리를 구한 후 최단거리인 노드를 삭제하고
// 한번 더 다익스트라를 돌리면 된다!