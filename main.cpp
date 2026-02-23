#include "DLL.hpp"

int main() {
    try {
        DLL<int> list2 = {10, 20, 30};
        DLL<int> list1 = {5, 15, 25, 35, 45};
        
        list1.insert(list1.begin(), {25,26,27});
        list1.erase(++list1.begin(),--list1.end());
        std::cout << "Merging list1 {10,20,30} and list2 {5,15,25,35,45}..." << std::endl;
        list1.merge(list2);

        std::cout << "Result: ";
        for(auto it = list1.begin(); it != list1.end(); ++it) std::cout << *it << " ";

        std::cout << "\nNew Size: " << list1.get_size() << " (Expected: 8)" << std::endl;
        std::cout << "Tail value: " << list1.back() << " (Expected: 45)" << std::endl;
        std::cout << "Other list size: " << list2.get_size() << " (Expected: 0)" << std::endl;

        std::cout << "------------------------------------" << std::endl;

        DLL<int> list3 = {1, 1, 1, 2, 3, 3, 4, 5, 5, 5};
        std::cout << "Testing unique on {1,1,1,2,3,3,4,5,5,5}..." << std::endl;
        list3.unique();

        std::cout << "Result: ";
        for(auto it = list3.begin(); it != list3.end(); ++it) std::cout << *it << " ";
        
        std::cout << "\nNew Size: " << list3.get_size() << " (Expected: 5)" << std::endl;

        std::cout << "------------------------------------" << std::endl;

        std::cout << "Reversing result..." << std::endl;
        list3.reverse();
        for(auto it = list3.begin(); it != list3.end(); ++it) std::cout << *it << " ";

        std::cout << "\nHead: " << list3.front() << ", Tail: " << list3.back() << std::endl;
        std::cout << "------------------------------------" << std::endl;
        
        std::cout << "Testing Copy and Move Logic..." << std::endl;
        
        DLL<int> original = {100, 200, 300};
        DLL<int> copy_constructed = original; 
        DLL<int> move_constructed = std::move(original);

        std::cout << "Original size after move: " << original.get_size() << " (Expected: 0)" << std::endl;
        std::cout << "Move constructed back: " << move_constructed.back() << " (Expected: 300)" << std::endl;

        DLL<int> assigned;
        assigned = {7, 8, 9};
        std::cout << "Assignment result: " << assigned.front() << " to " << assigned.back() << " (Expected: 7 to 9)" << std::endl;

        std::cout << "------------------------------------" << std::endl;
        std::cout << "Testing Pop and Emplace..." << std::endl;
        
        DLL<int> list4;
        list4.push_back(10);
        list4.push_front(5);
        list4.emplace_back(15);
        list4.emplace(++list4.begin(), 7); 
        list4.pop_front();
        list4.pop_back();
        
        std::cout << "List4 after pops: ";
        for(auto it = list4.begin(); it != list4.end(); ++it) std::cout << *it << " ";
        std::cout << "(Expected: 7 10)" << std::endl;

        std::cout << "------------------------------------" << std::endl;
        std::cout << "Testing remove()..." << std::endl;
        DLL<int> list5 = {1, 2, 1, 3, 1, 4};
        size_t removed_count = list5.remove(1);
        std::cout << "Removed: " << removed_count << " elements. New size: " << list5.get_size() << std::endl;
        std::cout << "Remaining: ";
        for(auto x : list5) std::cout << x << " ";
        std::cout << "(Expected: 2 3 4)" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}



