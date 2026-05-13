#include <iostream>

using namespace std;

class Buffer {
private:
    int* data;
public:
    Buffer(int size) { data = new int[size]; }
    Buffer(Buffer&& other) noexcept : data(other.data) {
        other.data = nullptr;
    }

    int* getPointer() const {
        return data;
    } // Add a getter

    ~Buffer() { delete[] data; }
};


int main(){
    Buffer a(7);
    
    cout << "a's location: " << a.getPointer() << endl;
    
    Buffer b = move(a);

    cout << "a's location after moving: " << a.getPointer() << endl;
    cout << "b's location after moving a: " << b.getPointer() << endl;

    return 0;

}



