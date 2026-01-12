#include <iostream>

namespace first{
    int x = 1;
}

namespace second{
    int x = 2;
}


int main() {
    /*
        Namespace = provides a solution for preventing name conflicts in large projects.
        Each entity needs a unique name.
        A namespace allows for identically name entities as long as the namespaces are different
    */
   
    using namespace second;
    std::cout << x << "\n";
    std::cout << first::x << "\n";
        
    return 0;


    // using std::cout;
    // using std::string;

    // string name = "bro";
    // cout << "Hello "<< name;

}
