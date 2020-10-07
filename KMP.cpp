// 총 문자열에서 중복되는 주기문을 찾는 문제에서 발췌했습니다.
int answer = 0;
int m = str.length(); // m은 총 문자열의 길이
int j = 0;
vector<int> pi(m);
for (int i = 1; i < m; i++)
{
  if (j == 0 && str[i] == str[j])
  { // 같은게 생겼다? -> 합리적의심 시작
    answer = i;
  }
  // 합리적 의심중에 의심이 실패한다면
  while (j != 0 && str[i] != str[j])
  { // str[i] == str[j]가 될 때 까지 pi를 이용해 되돌아가기
    j = pi[j - 1];
    answer = i - j;
  }
  if (str[i] == str[j])
  { // 합리적 의심이 지속된다면
    pi[i] = ++j;
  }
  if (j == 0)
  { // 같은게 없어졌다? -> 반복 안하는중
    answer = 0;
  }

  if (answer != 0)
  { // answer가 0이 아니라는 건 합리적 의심중이라는 뜻
    if (pi[i] % answer == 0)
    { // answer 크기만큼 pi가 증가중이다 -> 반복중
      I.push_back(i + 1);
      N.push_back(pi[i] / answer + 1);
    }
  }
}
/*
예시입니다
str
pi

abababababab
0012345678910

aaaaaa
012345

ababcababc
0012012345

aab aab aab aab
010 123 456 789

aaba aaba
0101 2234
*/

// =======================================================
// pi가 이미 나와있다면 pi배열 설정만 해주면 됩니다.
// N에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해 pi[] 계산
// pi[i] = N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
vector<int> getPartialMatch(const string &N)
{
  int M = N.size();
  vector<int> pi(M, 0);
  //KMP로 자기 자신을 찾는다
  //N을 N에서 찾는다.
  //begin = 0이면 자기 자신을 찾아버리니까 안됨!
  int begin = 1, matched = 0;
  //비교할 문자가 N의 끝에 도달할 때까지 찾으면서 부분 일치를 모두 기록한다
  while (begin + matched < M) {
    if (N[begin + matched] == N[matched])     {
      matched++;
      pi[begin + matched - 1] = matched;
    }
    else     {
      if (matched == 0)
        begin++;
      else {
        begin += matched - pi[matched - 1];
        matched = pi[matched - 1];
      }
    }
  }
  return pi;
}

vector<int> kmpSearch2(const string &H, const string &N) {
  int n = H.size(), m = N.size();
  vector<int> result;
  vector<int> pi = getPartialMatch(N);
  //현재 대응된 글자의 수
  int matched = 0;
  //짚더미의 각 글자를 순회
  for (int i = 0; i < n; i++) {
    //matched번 글자와 짚더미의 해당 글자가 불일치할 경우,
    //현재 대응된 글자의 수를 pi[matched-1]로 줄인다
    while (matched > 0 && H[i] != N[matched])
      matched = pi[matched - 1];
    //글자가 대응될 경우
    if (H[i] == N[matched]) {
      matched++;
      if (matched == m) {
        //문제에서 인덱스는 0이 아닌 1부터 시작
        result.push_back(i - m + 2);
        matched = pi[matched - 1];
      }
    }
  }
  return result;
}