#include <iostream>
#include <thread>
#include <vector>
#include <sstream>

using namespace std;

vector<string> resultNotebooks;

void performStudyOperation(int notebook_i, int pencil, int eraser, char operation) 
{
    int studyResult;
    switch (operation) 
    {
        case 's':
            studyResult = pencil + eraser;
            break;
        case 'm':
            studyResult = pencil * eraser;
            break;
        case 'c':
            studyResult = pencil * pencil + eraser * eraser;
            break;
        default:
            cerr << "Недопустимая операция:" << operation << endl;
            return;
    }

    ostringstream notebookStream;
    notebookStream << "out_" << notebook_i << ": \"" << pencil << " " << operation << " " << eraser << " = " << studyResult << "\"";
    resultNotebooks.push_back(notebookStream.str());
}

int main() 
{
    int numberOfNotebooks;
    cin >> numberOfNotebooks;

    vector<thread> studyThreads;

    for (int i = 0; i < numberOfNotebooks; ++i) 
    {
        int pencil, eraser;
        char operation;
        cin >> pencil >> eraser >> operation;

        studyThreads.emplace_back(performStudyOperation, i + 1, pencil, eraser, operation);
    }

    for (auto& thread : studyThreads) 
    {
        thread.join();
    }

    for (const auto& result : resultNotebooks) 
    {
        cout << result << endl;
    }

    return 0;
}

