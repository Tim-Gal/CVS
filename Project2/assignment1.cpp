#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cassert>

using namespace std;


bool identical_word(string word1, string word2)
{
    return word1 == word2;
}


void print_contents(filesystem::path filepath)
{
    string filename = filepath.filename().string();
    ifstream file(filepath);

    if (!file.is_open())
    {
        cout << filename << " cannot be opened" << endl;
        return;
    }

    string line;

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}


bool classical_identical_files(filesystem::path filepath1, filesystem::path filepath2)
{
    string filename1 = filepath1.filename().string();
    string filename2 = filepath2.filename().string();
    ifstream file1(filepath1);
    ifstream file2(filepath2);

    // deduplicate 2 following blocks
    if (!file1.is_open())
    {
        cout << filename1 << " cannot be opened" << endl;
        return false;
    }
    if (!file2.is_open())
    {
        cout << filename2 << " cannot be opened" << endl;
        return false;
    }

    string line1;
    string line2;

    while (getline(file1, line1) && getline(file2, line2))
    {
        if (!identical_word(line1, line2))
        {
            file1.close();
            file2.close();
            return false;
        }
    }

    // deduplicate 2 following blocks
    if (!file1.eof())
    {
        cout << filename1 << " did not reach end" << endl;
        file1.close();
        file2.close();
        return false;
    }
    if (!file2.eof())
    {
        cout << filename2 << " did not reach end" << endl;
        file1.close();
        file2.close();
        return false;
    }

    file1.close();
    file2.close();
    return true;
}


size_t hash_it(string someString)
{
    return hash<string>{}(someString);
}


bool enhanced_identical_files(filesystem::path filepath1, filesystem::path filepath2)
{
    string filename1 = filepath1.filename().string();
    string filename2 = filepath2.filename().string();
    ifstream file1(filepath1);
    ifstream file2(filepath2);

    // deduplicate 2 following blocks
    if (!file1.is_open())
    {
        cout << filename1 << " cannot be opened" << endl;
        return false;
    }
    if (!file2.is_open())
    {
        cout << filename2 << " cannot be opened" << endl;
        return false;
    }

    string line1;
    string line2;

    while (getline(file1, line1) && getline(file2, line2))
    {
        if (hash_it(line1) != hash_it(line2))
        {
            file1.close();
            file2.close();
            return false;
        }
    }

    // deduplicate 2 following blocks
    if (!file1.eof())
    {
        cout << filename1 << " did not reach end" << endl;
        file1.close();
        file2.close();
        return false;
    }
    if (!file2.eof())
    {
        cout << filename2 << " did not reach end" << endl;
        file1.close();
        file2.close();
        return false;
    }

    file1.close();
    file2.close();
    return true;
}


void list_mismatched_lines(filesystem::path filepath1, filesystem::path filepath2)
{
    string filename1 = filepath1.filename().string();
    string filename2 = filepath2.filename().string();
    ifstream file1(filepath1);
    ifstream file2(filepath2);

    // deduplicate 2 following blocks
    if (!file1.is_open())
    {
        cout << filename1 << " cannot be opened" << endl;
        return;
    }
    if (!file2.is_open())
    {
        cout << filename2 << " cannot be opened" << endl;
        return;
    }

    string line1;
    string line2;

    while (getline(file1, line1) && getline(file2, line2))
    {
        if (hash_it(line1) != hash_it(line2))
        {
            cout << filename1 << ": " << line1 << endl;
            cout << filename2 << ": " << line2 << endl;
        }
    }
    while (getline(file1, line1)) // while file1 continues & file2 ends
    {
        cout << filename1 << ": " << line1 << endl;
        cout << filename2 << ": --- NO LINE ---" << endl;
    }
    while (getline(file2, line2)) // while file1 ends & file2 continues
    {
        cout << filename1 << ": --- NO LINE ---" << endl;
        cout << filename2 << ": " << line2 << endl;
    }
}


int main()
{
    filesystem::path filepath1 = "C:\\Users\\Luna Laptop\\Desktop\\VCS_project\\file1.txt";
    filesystem::path filepath2 = "C:\\Users\\Luna Laptop\\Desktop\\VCS_project\\file2.txt";
    filesystem::path filepath3 = "C:\\Users\\Luna Laptop\\Desktop\\VCS_project\\file3.txt";
    filesystem::path filepath4 = "C:\\Users\\Luna Laptop\\Desktop\\VCS_project\\file4.txt";
    
   
    assert(1 == classical_identical_files(filepath1, filepath2));
    assert(0 == classical_identical_files(filepath1, filepath3));
    assert(0 == classical_identical_files(filepath1, filepath4));

    assert(1 == enhanced_identical_files(filepath1, filepath2));
    assert(0 == enhanced_identical_files(filepath1, filepath3));
    assert(0 == enhanced_identical_files(filepath1, filepath4));


    cout << "list_mismatched_lines for file1 vs file2" << endl;
    list_mismatched_lines(filepath1, filepath2);
    cout << "\nlist_mismatched_lines for file1 vs file3" << endl;
    list_mismatched_lines(filepath1, filepath3);
    cout << "\nlist_mismatched_lines for file1 vs file4" << endl;
    list_mismatched_lines(filepath1, filepath4);


    return 0;
}