#include <iostream>
#include "Query.h"
#include "TextQuery.h"

using std::cout;
using std::cin;
using std::endl;

void test_wordQuery()
{
    string filename;
    cout << "enter name of file to query: ";
    cin >> filename;
    ifstream ifs = get_file(filename);
    while (!ifs)
    {
        cout << "enter name of file to query: ";
        cin >> filename;
        ifs = get_file(filename);
    }

    TextQuery file(ifs);
    do {
        string sought;
        if (!get_word(sought)) break;
    ifstream ifs = get_file(filename);
    while (!ifs.good())
    {
        cout << "enter name of file to query: ";
        cin >> filename;
        ifs = get_file(filename);
    }

        Query name(sought);
        const QueryResult results = name.eval(file);
        cout << "\nExecuting Query for: " << name << endl;

        print(cout, results) << endl;
    } while (true);
}

void test_andQuery()
{
    string filename;
    cout << "enter name of file to query: ";
    cin >> filename;
    ifstream ifs = get_file(filename);
    while (!ifs)
    {
        cout << "enter name of file to query: ";
        cin >> filename;
        ifs = get_file(filename);
    }

    TextQuery file(ifs);
    do {
        string sought1, sought2;
        if (!get_words(sought1, sought2))
			break;

        Query andq = Query(sought1) & Query(sought2);
        cout << "\nExecuting query for: " << andq << endl;
        QueryResult results = andq.eval(file);
        print(cout, results);

        results = Query(sought1).eval(file);
        cout << "\nExecuted query: " << Query(sought1) << endl;
        print(cout, results);

        results = Query(sought2).eval(file);
        cout << "\nExecuted query: " << Query(sought2) << endl;
        print(cout, results);
    } while(true);
}

void test_andorQuery()
{
    string filename;
    cout << "enter name of file to query: ";
    cin >> filename;
    ifstream ifs = get_file(filename);
    while (!ifs)
    {
        cout << "enter name of file to query: ";
        cin >> filename;
        ifs = get_file(filename);
    }

    TextQuery file(ifs);
    while (true) {
        string sought1, sought2, sought3;
        if (!get_words(sought1, sought2)) break;
        cout << "\nenter third word: " ;
        cin  >> sought3;
        Query q = Query(sought1) & Query(sought2)
                             | Query(sought3);
        cout << "\nExecuting Query for: " << q << endl;
        const QueryResult results = q.eval(file);
		print(cout, results);
     }
}

int main(int argc, char **argv)
{
    cout << "Select query mode:\n"
         << "1. Single Word Query\n"
         << "2. Two Words Query(and)\n"
         << "3. Three Words Query(and_or)\n"
         << "0. quit\n";
    int state;
    cin >> state;
    while(1 <= state && state <= 3)
    {
        switch (state)
        {
            case 0:
                break;
            case 1:
                test_wordQuery();
                break;
            case 2:
                test_andQuery();
                break;
            case 3:
                test_andorQuery();
                break;
            default:
                cout << "Error input, try again" << endl;
                break;
        }
        cout << "Select query mode:\n"
             << "1. Single Word Query\n"
             << "2. Two Words Query(and)\n"
            << "3. Three Words Query(and_or)\n"
            << "0. quit\n";
        cin >> state;
    }
    /* test_wordQuery(); */
    /* test_andQuery(); */
    /* test_andorQuery(); */
    return 0;
}

