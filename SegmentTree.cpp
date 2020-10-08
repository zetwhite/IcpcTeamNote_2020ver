#include <vector> 
#include <iostream> 
using namespace std; 

class SegTree{
private:
    //완전이진트리 뒷쪽에 빈 값을 채우기 위함, invalid한 값을 넣어야한다. 
    //현재는 구간곱을 구하는 예제라서 곱셈의 항등원인 1을 넣은 것  
    const int inValid = 1; 
    int size; //tree 배열을 저장하는 전체 사이즈  
    int leaf; //leaf node가 시작되는 index
    int* data; 

    //n보다 크면서 가장 가까운 2의 거듭제곱 * 2한 값 계산
    int calSize(int n){
        int m = 1; 
        n = n - 1; 
        while(n > 0){
            m = m << 1; 
            n = n >> 1; 
        }
        return m*2; 
    }

public: 
    //생성자: values를 leaf노드로 옮기고 위쪽 트리를 계산해서 채움 
    SegTree(vector<int>& values){
        size = calSize(values.size()); 
        data = new int[size]; 
        leaf = size/2; 
        //leaf노드에 값 옮기기 
        for(int i = 0; i < values.size(); i++){
            data[leaf + i] = values[i]; 
        }
        //완전 이진트리 남는 자리에 invalid한 값 넣기 
        for(int i = leaf + values.size(); i < size; i++){
            data[i] = inValid; 
        }
        //root노드(index==1)까지 부분 결과값 채우기 
        for(int i = leaf - 1; i > 0; i--){
            //현재는 구간곱을 구하는 예제라서 곱셈을 하지만, 
            //찾는 값에 따라서 다른 연산으로 대체해야함. 
            data[i] = data[i*2] * data[i+2 + 1]; 
        }
    }

    //index에 newValue라는 새로운 값이 들어오는 경우 
    void update(int index, int newValue){
        int indexOfTree = leaf + index;
        data[indexOfTree] = newValue; 
        //root노드로 올라가면서 관련 값들 모두 갱신하기 
        indexOfTree = indexOfTree / 2; 
        while(indexOfTree > 0){
            //갱신되는 값 계산도 경우에 따라서 다른 연산으로 구해야함. 
            //현재는 구간곱을 구하는 예제라서 곱셈을 했음. 
            data[indexOfTree]  = data[indexOfTree*2] * data[indexOfTree*2 + 1]; 
            indexOfTree = indexOfTree / 2; 
        } 
    }

    //[start, end] 까지의 구간값을 rLeft(range_Left), rRight(range_Right) 범위내에서 구함. 
    int select(int start, int end, int rLeft=-1, int rRight=-1){
        //rLeft범위가 안 주어지면 전체 범위에서 진행
        //rLeft = Leaf노드의 시작, start = tree에서의 start index로 변환 
        if(rLeft == -1){
            rLeft = size / 2; 
            start = rLeft + start; 
        }
        //rRight의 범위가 안 주어지면 전체 범위에서 진행 
        //rRight = Leaf노드의 끝, end = tree에서의 end index로 변환
        if(rRight == -1){
            rRight = size - 1; 
            end = rLeft + end; 
        }
        //[start, end], [rLeft, rRight]가 겹치는 구간이 없는 경우
        if(end < rLeft || rRight < start){
            return inValid; 
        }
        //[rLeft, rRight]가 [start, end]에 포함되는 경우 
        if(start <= rLeft && rRight <= end){
            int gap = rRight - rLeft; //현재 구간 크기
            int index = rLeft; //현재 구간 index
            while(gap > 0){ //gap이 0이 될때까지 계속 트리를 타고 올라간다. 
                gap = gap >> 1; 
                index = index >> 1; 
            }
            return data[index]; //구간에 해당되는 값반환 
        }
        //그 외의 모든 경우 
        int mid = (rLeft + rRight) / 2; 
        //range를 다시 2개로 나누어서 [start, end]에 포함되는 range찾을때까지 진행 
        //적절한 연산으로 찾은 2개의 값을 비교해야한다. 여기서는 구간곱 예제라서 곱셈을 쓴 것 
        return select(start, end , rLeft, mid) * select(start, end, mid+1, rRight); 
    }
}; 

int main(){

    vector<int> arr = {1, 2, 3, 4, 5}; 
    SegTree tree(arr); 
    tree.update(2, 6); //arr[2] = 6 update
    cout << tree.select(1, 4) << endl; //구간곱(arr[1] ~ arr[4])
    tree.update(4, 2);  //arr[4] = 2 update
    cout << tree.select(2, 4) << endl;  //구간곱(arr[2] ~ arr[4])
    return 0; 
}