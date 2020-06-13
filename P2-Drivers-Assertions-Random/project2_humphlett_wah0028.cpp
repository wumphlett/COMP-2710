//=============================================================================
// Name        : project2_humphlett_wah0028.cpp
// Author      : Will Humphlett (wah0028)
// Version     : 6/12/2020
// Description : COMP2710 Software Construction Project 2
// Compile     : g++ project2_humphlett_wah0028.cpp -o Project2.out
// Run         : ./Project2.out
//=============================================================================

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

// Accuracy Constants
const double aaron_acc = 0.33333333;
const double bob_acc = 0.5;
const double charlie_acc = 1;

// Testing Constants
const int total_duels = 10000;

// Status
bool at_least_two_alive(bool aaron_alive, bool bob_alive, bool charlie_alive) {
    int players_alive = 0;

    players_alive = aaron_alive ? players_alive + 1 : players_alive;
    players_alive = bob_alive ? players_alive + 1 : players_alive;
    players_alive = charlie_alive ? players_alive + 1 : players_alive;

    return players_alive >= 2;
}

// Shooting Methods
bool shoot(double accuracy) {
    double shoot_target = ((double) rand()) / (double) RAND_MAX;
    return shoot_target <= accuracy;
}

int aaron_shoots_1(bool& bob_alive, bool& charlie_alive) {
    if (charlie_alive) {
        bool hit = shoot(aaron_acc);
        charlie_alive = hit ? false : charlie_alive;
        return 2;
    }
    else if (bob_alive) {
        bool hit = shoot(aaron_acc);
        bob_alive = hit ? false : bob_alive;
        return 1;
    }
    return -1;
}

int aaron_shoots_2(bool& bob_alive, bool& charlie_alive) {
    if (bob_alive && charlie_alive) {
        return -1;
    }
    return aaron_shoots_1(bob_alive, charlie_alive);
}

int bob_shoots(bool& aaron_alive, bool& charlie_alive) {
    if (charlie_alive) {
        bool hit = shoot(bob_acc);
        charlie_alive = hit ? false : charlie_alive;
        return 2;
    }
    else if (aaron_alive) {
        bool hit = shoot(bob_acc);
        aaron_alive = hit ? false : aaron_alive;
        return 0;
    }
    return -1;
}

int charlie_shoots(bool& aaron_alive, bool& bob_alive) {
    if (bob_alive) {
        bool hit = shoot(charlie_acc);
        bob_alive = hit ? false : bob_alive;
        return 1;
    }
    else if (aaron_alive) {
        bool hit = shoot(charlie_acc);
        aaron_alive = hit ? false : aaron_alive;
        return 0;
    }
    return -1;
}

// Duel
int duel(int strategy) {
    bool aaron_alive = true;
    bool bob_alive = true;
    bool charlie_alive = true;
    while (at_least_two_alive(aaron_alive, bob_alive, charlie_alive)) {
        if (aaron_alive) {
            if (strategy == 1) {
                aaron_shoots_1(bob_alive, charlie_alive);
            }
            else if (strategy == 2) {
                aaron_shoots_2(bob_alive, charlie_alive);
            }
        }
        if (bob_alive) {
            bob_shoots(aaron_alive, charlie_alive);
        }
        if (charlie_alive) {
            charlie_shoots(aaron_alive, bob_alive);
        }
    }
    return aaron_alive ? 0 : bob_alive ? 1 : charlie_alive ? 2 : -1;
}

// Helper
void wait_for_key(void) {
    cout << "Press Enter to continue...";
    cin.ignore().get(); // Pause Terminal
}

// Unit Tests
void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
    
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\t\tCase passed ...\n";

    wait_for_key();
}

void test_aaron_shoots_1(void) {
    cout << "Unit Testing 2: Function - aaron_shoots_1()\n";

    cout << "\tCase 1: Bob alive, Charlie alive\n";
    bool b = true; bool c = true;
    assert(2 == aaron_shoots_1(b, c));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    b = false; c = true;
    assert(2 == aaron_shoots_1(b, c));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    b = true; c = false;
    assert(1 == aaron_shoots_1(b, c));
    cout << "\t\tAaron is shooting at Bob\n";

    wait_for_key();
}

void test_bob_shoots(void) {
    cout << "Unit Testing 3: Function - bob_shoots()\n";

    cout << "\tCase 1: Aaron alive, Charlie alive\n";
    bool a = true; bool c = true;
    assert(2 == bob_shoots(a, c));
    cout << "\t\tBob is shooting at Charlie\n";

    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    a = false; c = true;
    assert(2 == bob_shoots(a, c));
    cout << "\t\tBob is shooting at Charlie\n";

    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    a = true; c = false;
    assert(0 == bob_shoots(a, c));
    cout << "\t\tBob is shooting at Aaron\n";

    wait_for_key();
}

void test_charlie_shoots(void) {
    cout << "Unit Testing 4: Function - charlie_shoots()\n";

    cout << "\tCase 1: Aaron alive, Bob alive\n";
    bool a = true; bool b = true;
    assert(1 == charlie_shoots(a, b));
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 2: Aaron dead, Bob alive\n";
    a = false; b = true;
    assert(1 == charlie_shoots(a, b));
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 3: Aaron alive, Bob dead\n";
    a = true; b = false;
    assert(0 == charlie_shoots(a, b));
    cout << "\t\tCharlie is shooting at Aaron\n";

    wait_for_key();
}

void test_aaron_shoots_2(void) {
    cout << "Unit Testing 5: Function - aaron_shoots_2()\n";

    cout << "\tCase 1: Bob alive, Charlie alive\n";
    bool b = true; bool c = true;
    assert(-1 == aaron_shoots_2(b, c));
    cout << "\t\tAaron intentionally misses his first shot\n";
    assert(b == true); assert(c == true);
    cout << "\t\tBoth Bob and Charlie are alive\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    b = false; c = true;
    assert(2 == aaron_shoots_2(b, c));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    b = true; c = false;
    assert(1 == aaron_shoots_2(b, c));
    cout << "\t\tAaron is shooting at Bob\n";

    wait_for_key();
}

int test_duel(int strategy) {
    cout << "Ready to test strategy " << strategy << " (run " << total_duels << " times):\n";
    wait_for_key();

    int a_wins = 0; int b_wins = 0; int c_wins = 0;
    for (int i = 0; i < total_duels; i++) {
        int duel_result = duel(strategy);
        switch (duel_result) {
        case 0: a_wins++;
                break;
        case 1: b_wins++;
                break;
        case 2: c_wins++;
                break;
        }
    }

    cout << "Aaron won " << a_wins << "/" << total_duels << " duels or " << static_cast <double>(a_wins) / total_duels * 100 << "%\n";
    cout << "Bob won " << b_wins << "/" << total_duels << " duels or " << static_cast <double>(b_wins) / total_duels * 100 << "%\n";
    cout << "Charlie won " << c_wins << "/" << total_duels << " duels or " << static_cast <double>(c_wins) / total_duels * 100 << "%\n";
    cout << endl;

    return a_wins;
}

void eval_strategies(int wins_1, int wins_2) {
    if (wins_1 > wins_2) {
        cout << "Strategy 1 is better than strategy 2";
    }
    else if (wins_2 > wins_1) {
        cout << "Strategy 2 is better than strategy 1";
    }
    else {
        cout << "Both strategies produce equal results for Aaron";
    }
}

int main() {
    // Set cout Format
    cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

    // Initialize Random
    srand(time(0));
    rand();

    cout << "*** Welcome to Will's Duel Simulator ***\n";
    // Unit Testing
    test_at_least_two_alive();
    test_aaron_shoots_1();
    test_bob_shoots();
    test_charlie_shoots();
    test_aaron_shoots_2();

    // Test Strategy
    int wins_1 = test_duel(1);
    int wins_2 = test_duel(2);
    eval_strategies(wins_1, wins_2);

    cout << endl;
    return 0;
}