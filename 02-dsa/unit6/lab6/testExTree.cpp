#include <iostream>
#include <string>
#include "myExpressionTree.hpp"

using namespace std;

void runExpressionTest(const string& infix)
{
    cout << "=========================================" << endl;

    myExpressionTree t(infix);

    cout << "Input string is " << t.getInput() << endl;
    cout << "Postfix input string is " << t.getPostFixInput() << endl;
    cout << "Before build, is tree empty? " << boolalpha << t.isEmpty() << endl;
    cout << "Before build the value of tree is " << t.evaluate() << endl << endl;

    t.build();

    cout << "In-order traversal yields: ";
    t.printIn();
    cout << endl << endl;

    cout << "Post-order traversal yields: ";
    t.printPost();
    cout << endl << endl;

    cout << "Pre-order traversal yields: ";
    t.printPre();
    cout << endl << endl;

    cout << "Using operator<< yields: ";
    cout << t;
    cout << endl << endl;

    cout << "After build the value of tree is " << t.evaluate() << endl;
    cout << "After build, is tree empty? " << t.isEmpty() << endl;
    cout << "Levels is: " << t.getLevels() << endl;
    cout << "Height is: " << t.getHeight() << endl;

    cout << "=========================================" << endl << endl;
}

void runDeepCopyTest(const string& originalInfix, const string& replacementInfix)
{
    cout << "=========================================" << endl;
    cout << "Deep Copy Test" << endl;

    myExpressionTree original(originalInfix);
    original.build();

    myExpressionTree copyConstructed(original);

    myExpressionTree assigned;
    assigned = original;

    cout << "Original input string is " << original.getInput() << endl;
    cout << "Original postfix input string is " << original.getPostFixInput() << endl;
    cout << "Original value before change: " << original.evaluate() << endl;
    cout << "Copy constructed value before change: " << copyConstructed.evaluate() << endl;
    cout << "Assigned value before change: " << assigned.evaluate() << endl;
    cout << "Original levels before change: " << original.getLevels() << endl;
    cout << "Original height before change: " << original.getHeight() << endl << endl;

    cout << "Resetting and rebuilding original with input string " << replacementInfix << endl;
    original.resetInput(replacementInfix);
    original.build();

    cout << "Original value after change: " << original.evaluate() << endl;
    cout << "Copy constructed value after original change: " << copyConstructed.evaluate() << endl;
    cout << "Assigned value after original change: " << assigned.evaluate() << endl;
    cout << "Copy constructed levels after original change: " << copyConstructed.getLevels() << endl;
    cout << "Copy constructed height after original change: " << copyConstructed.getHeight() << endl;
    cout << "Assigned levels after original change: " << assigned.getLevels() << endl;
    cout << "Assigned height after original change: " << assigned.getHeight() << endl;

    cout << "=========================================" << endl << endl;
}

int main()
{
    cout << boolalpha;

    cout << "CSC 240 Lab 6: Expression Tree Test Driver" << endl << endl;

    string input1 = "12+34=";
    string input2 = "12+34*2=";
    string input3 = "(12+3)*(56/2)/(34-4)=";
    string input4 = "100*2/25+5*4=";
    string input5 = "7/2=";
    string input6 = "9=";

    runExpressionTest(input1);
    runExpressionTest(input2);
    runExpressionTest(input3);
    runExpressionTest(input4);
    runExpressionTest(input5);
    runExpressionTest(input6);

    runDeepCopyTest(input3, input1);

    return 0;
}
