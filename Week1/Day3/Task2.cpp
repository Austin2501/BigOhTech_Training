#include <bits/stdc++.h>

using namespace std;

// checking for balance less than amount needed
class InvalidBalanceAmountException : public runtime_error {
public:
    InvalidBalanceAmountException() : runtime_error("Insufficient balance!") {}
};

// checking if needed amount is in multiple of notes
class InvalidDenominationAmountException : public runtime_error {
public:
    InvalidDenominationAmountException() : runtime_error("Please give amount in multiple of denomination!") {}
};

// Denomination class
class Denomination
{
public:
    int value;
    int count;

    Denomination() : value(0), count(0) {}

    Denomination(int value, int count) : value(value), count(count) {}
};

// Withdrawal result class
class Withdraw
{
public:
    map<int, int> notes;

    void addNotes(int denomination, int count)
    {
        notes[denomination] += count;
    }

    void display() const
    {
        for (const auto &note : notes)
        {
            cout << note.first << " x " << note.second << endl;
        }
    }
};

// ATM class (Singleton)
class ATM
{
private:
    map<int, Denomination> denominations;

    ATM() {}

public:
    // Static method to get the single instance of the ATM
    static ATM &getInstance()
    {
        static ATM instance;
        return instance;
    }
    // addMoney function
    // returntype void only add notes and count in map
    void addMoney(int value, int count)
    {
        if (denominations.find(value) != denominations.end())
        {
            denominations[value].count += count;
        }
        else
        {
            denominations[value] = Denomination(value, count);
        }
    }
    // Withdraw type function
    // return Withdraw type
    // return map
    Withdraw withdraw(int amount)
    {
        if (!isMultipleOfDenominations(amount))
        {
            throw InvalidDenominationAmountException();
        }

        int totalBalance = getTotalBalance();
        if (amount > totalBalance)
        {
            throw InvalidBalanceAmountException();
        }

        Withdraw result;
        vector<int> keys = SortedDenomination();
        for (int key : keys)
        {
            int needed = amount / key;
            if (needed > 0 && denominations[key].count > 0)
            {
                int toGive = min(needed, denominations[key].count);
                amount -= toGive * key;
                denominations[key].count -= toGive;
                result.addNotes(key, toGive);
            }
        }

        if (amount > 0)
        {
            throw InvalidBalanceAmountException(); // should never reach here if logic is correct
        }

        return result;
    }
    // display function
    void displayBalance() const
    {
        for (auto denomination : denominations)
        {
            cout << denomination.first << " INR : " << denomination.second.count << " notes" << endl;
        }
    }
    // Demonitization function
    void Demonitization(int value)
    {
        if (denominations.find(value) != denominations.end())
        {
            denominations.erase(value);
            cout << "Denomination " << value << " INR has been removed from the ATM." << endl;
        }
        else
        {
            cout << "Denomination " << value << " INR not found in the ATM." << endl;
        }
    }

private:
    bool isMultipleOfDenominations(int amount) const
    {
        for (const auto &denomination : denominations)
        {
            if (amount % denomination.first == 0)
            {
                return true;
            }
        }
        return false;
    }

    int getTotalBalance() const
    {
        int total = 0;
        for (const auto &denomination : denominations)
        {
            total += denomination.first * denomination.second.count;
        }
        return total;
    }

    vector<int> SortedDenomination() const
    {
        vector<int> keys;
        for (const auto &denomination : denominations)
        {
            keys.push_back(denomination.first);
        }
        sort(keys.rbegin(), keys.rend());
        return keys;
    }
};

// User class
class User
{
private:
    string name;

public:
    User(const string &name) : name(name) {}

    void withdraw(int amount)
    {
        try
        {
            cout << name << " is withdrawing " << amount << " INR:" << endl;
            Withdraw result = ATM::getInstance().withdraw(amount);
            result.display();
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }
};

int main()
{
    ATM &atm = ATM::getInstance();

    // Top-up the ATM with initial denominations
    atm.addMoney(2000, 20);
    atm.addMoney(500, 2);
    atm.addMoney(200, 5);
    atm.addMoney(100, 10);

    // Display initial balance
    cout << "Initial ATM Balance:" << endl;
    atm.displayBalance();
    cout << endl;

    // Create users
    User Vineet("Vineet");
    Vineet.withdraw(5300);

    cout << "Remaining ATM Balance:" << endl;
    atm.displayBalance();
    cout << endl;

    atm.Demonitization(2000); // Removing 2000 INR notes

    cout << "ATM Balance after demonetizing 2000 INR notes:" << endl;
    atm.displayBalance();
    cout << endl;

    atm.addMoney(5000, 10); // Adding new denomination (5000 INR)

    cout << "ATM Balance after adding 5000 INR notes:" << endl;
    atm.displayBalance();
    cout << endl;

    // Perform withdrawal with new denomination
    Vineet.withdraw(5000);
    cout << endl;

    cout << "Remaining ATM Balance:" << endl;
    atm.displayBalance();
    cout << endl;

    return 0;
}
