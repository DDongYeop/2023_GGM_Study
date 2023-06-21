// 탐색 : 찾는것 search
//  - 배열 N개 저장 
//  - for : O(n)
// 1.이분 탐색
// 중간값 물어보면서 탐색 범위가 계속 반씩 줄어드는 탐색기법, O(longn)
// 2.탐색에 유용한 자료구조 //키 중복 저장 X
// 정렬O
// * key를 가지고 value를 찾는 자료구조
// - map : 키를 기준으로 정렬 o, 레드블랙트리 -> O(longn)
// 정렬X
// - unordered_map : 키를 기준으로 정렬 x, 해시 테이블로 구현 -> O(1)) 
// * key만 저장하는 자료구조.. // 배열쓰면 안됨!?!?
// - set == map
// set<int> s; s.find("원준") //배열보다 빠르다 
// - unordered_set == unordered_map
// 
// #include <map>
// map<int, stirng> m;
// m.insert(make_pair(1, "경동엽"));
// m.insert({(1, "경동엽")});
// m.insert({(1, "경동엽")});
// m[1] = "경동엽";
// 
// set<int> s;
// s.insert(1);
// s.find(1) == s.end(); //없는거 체크 
//