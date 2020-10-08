#include <iostream>
#include <vector>

using namespace std;

template<typename Node>
class DisjointSet{
public:
    DisjointSet *root_set; // this set의 root이다. root DisjointSet를 가리킨다.
    vector<Node> node; // set의 root index는 0임.

    DisjointSet(){
        root_set = (DisjointSet*)0; //root default: 0 (자기 자신이 root인 경우)
    }
    DisjointSet(Node _node, int nodeSize = 1){
        root_set = (DisjointSet*)0; //root default: 0 (자기 자신이 root인 경우)
        node.reserve(nodeSize);
        node.push_back(_node);   //this set의 root node의 정보를 넣는다.
    }

    void add_node(Node _node){ // set에 node를 추가한다.
        node.push_back(_node);
    }

    void put_root(DisjointSet *_root_set){ // this set의 root set의 pointer를 재설정한다.
        root_set = _root_set;
    }

    DisjointSet* find_root(){ // this set의 root를 return한다.
        DisjointSet *find_root = this;
        while(find_root->root_set != (DisjointSet*)0){
            find_root = find_root->root_set;
        }
        return find_root;
    }

    void union_set(DisjointSet &ano){ //this set과 ano set을 합친다.
        // root가 같으면 합치지 않는다.
        DisjointSet *this_root = find_root();
        DisjointSet *ano_root = ano.find_root();
        if(this_root == ano_root)
            return;
        // root가 다르면 ano를 this_root class에 합친다.
        ano.put_root(this_root);
    }

    void print_set(){
        cout << "-------------------------\n";
        cout << "[Root Set]\t" << find_root()->node[0] << '\n';
        cout << "[Set Name]\t" << node[0] << '\n'; // only for example: 예제에서 set의 name을 첫번째 노드로 줘봤다.
        cout << "[Node] " << '\n';
        for(int i=1; i<node.size(); i++){
            cout << "\t* " << node[i] << '\n';
        }
        cout << "-------------------------\n";
    }
};

int main(){
	//ios::sync_with_stdio(false);
  // Example
	// create disjoint sets and add nodes
    DisjointSet<string> ds1("Disney");
    ds1.add_node("Jasmin");
    ds1.add_node("Cinderella");
    ds1.add_node("Mermaid");
    ds1.print_set();

    DisjointSet<string> ds2("Marvel");
    ds2.add_node("Captain");
    ds2.add_node("Thor");
    ds2.print_set();

    // find sets
    if(ds1.find_root() == ds2.find_root())
        cout << "ds1 and ds2 have same root\n";
    else
        cout << "ds1 and ds2 have other roots\n";

    // union sets
    ds1.union_set(ds2);
    cout << "\nAfter union ds1 and ds2,\n";
    ds1.print_set();
    ds2.print_set();

    // find sets
    if(ds1.find_root() == ds2.find_root())
        cout << "ds1 and ds2 have same root\n";
    else
        cout << "ds1 and ds2 have other roots\n";
	return 0;
}
