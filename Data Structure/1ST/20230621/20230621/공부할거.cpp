// Ž�� : ã�°� search
//  - �迭 N�� ���� 
//  - for : O(n)
// 1.�̺� Ž��
// �߰��� ����鼭 Ž�� ������ ��� �ݾ� �پ��� Ž�����, O(longn)
// 2.Ž���� ������ �ڷᱸ�� //Ű �ߺ� ���� X
// ����O
// * key�� ������ value�� ã�� �ڷᱸ��
// - map : Ű�� �������� ���� o, �����Ʈ�� -> O(longn)
// ����X
// - unordered_map : Ű�� �������� ���� x, �ؽ� ���̺�� ���� -> O(1)) 
// * key�� �����ϴ� �ڷᱸ��.. // �迭���� �ȵ�!?!?
// - set == map
// set<int> s; s.find("����") //�迭���� ������ 
// - unordered_set == unordered_map
// 
// #include <map>
// map<int, stirng> m;
// m.insert(make_pair(1, "�浿��"));
// m.insert({(1, "�浿��")});
// m.insert({(1, "�浿��")});
// m[1] = "�浿��";
// 
// set<int> s;
// s.insert(1);
// s.find(1) == s.end(); //���°� üũ 
//