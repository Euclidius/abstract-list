#include <iostream>
#include "queue.h"

using namespace std;

int main()
{
    Queue<int> s1;

    s1.push(1);
    s1.push(2);
    s1.push(3);

    cout << s1 << endl;          // 1->2->3
    cout << s1.getSize() << endl;
    
    Queue<int> s2 (s1), s3;

    s1.pop();    
    s1.push(4);
    s1.push(5);
    
    s2.pop();
    s2.push(6);

    cout << s1 << endl;         // 2->3->4->5
    cout << s1.getSize() << endl;
    
    cout << s2 << endl;         // 2->3->6
    cout << s2.getSize() << endl;
    
    s3 = s1;
    
    s1.pop();                   
    s1.push(7);
    s1.push(8);
    
    s3.pop();
    s3.push(9);

    cout << s1 << endl;         // 3->4->5->7->8
    cout << s1.getSize() << endl;
    
    cout << s2 << endl;         // 2->3->6
    cout << s2.getSize() << endl;
    
    cout << s3 << endl;
    cout << s3.getSize() << endl;  // 3->4->5->9

}
