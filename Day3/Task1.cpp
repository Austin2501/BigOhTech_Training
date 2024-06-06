#include <bits/stdc++.h>

using namespace std;

class Comment {
public:
    string text;
    string commenter;

    Comment(string t, string c) : text(t), commenter(c) {}
};

class Brick {
public:
    string owner;
    string caption;
    string message;
    string dedicateTo;
    int flags;
    bool visible;
    vector<Comment> comments;

    Brick(string o, string c, string m, string d) : owner(o), caption(c), message(m), dedicateTo(d), flags(0), visible(true) {}

    void addComment(string text, string commenter) {
        comments.emplace_back(text, commenter);
    }

    void flag() {
        flags++;
        if (flags > 10) {
            visible = false;
        }
    }

    void display() {
        if (visible) {
            cout << "Brick by " << owner << " to " << dedicateTo << endl;
            cout << "Caption: " << caption << endl;
            cout << "Message: " << message << endl;
            cout << "Comments: " << endl;
            for (auto &comment : comments) {
                cout << comment.commenter << ": " << comment.text << endl;
            }
            cout << endl;
        } else {
            cout << "This brick is invisible due to multiple flags." << endl;
        }
    }
};

class Wall {
public:
    vector<Brick> bricks;
    int maxBricks = 90;

    bool addBrick(Brick brick) {
        if (bricks.size() < maxBricks) {
            bricks.push_back(brick);
            return true;
        }
        return false;
    }

    void display() {
        for (auto &brick : bricks) {
            brick.display();
        }
    }

    int getBrickCount() {
        return bricks.size();
    }
};

class City {
public:
    string name;
    vector<Wall> walls;

    City(string n) : name(n) {}

    void addBrickToWall(Brick brick) {
        for (auto &wall : walls) {
            if (wall.addBrick(brick)) {
                return;
            }
        }
        Wall newWall;
        newWall.addBrick(brick);
        walls.push_back(newWall);
    }

    void display() {
        for (auto &wall : walls) {
            wall.display();
        }
    }

    int getTotalWalls() {
        return walls.size();
    }

    int getTotalBricksInWall(int wallIndex) {
        if (wallIndex < walls.size()) {
            return walls[wallIndex].getBrickCount();
        }
        return 0;
    }
};

class Country {
private:
    static Country* instance;
    string name;

    Country(string n) : name(n) {}

public:
    vector<City> cities;
    static Country* getInstance(string name) {
        if (instance == nullptr) {
            instance = new Country(name);
        }
        return instance;
    }

    void addCity(City city) {
        cities.push_back(city);
    }

    City* getCity(string cityName) {
        for (auto &city : cities) {
            if (city.name == cityName) {
                return &city;
            }
        }
        return nullptr;
    }

    void display() {
        for (auto &city : cities) {
            cout << "City: " << city.name << endl;
            city.display();
        }
    }
};

Country* Country::instance = nullptr;

class User {
public:
    string name;

    User(string n) : name(n) {}

    void paintBrick(string cityName, string caption, string message, string dedicateTo) {
        Country* country = Country::getInstance("");
        City* city = country->getCity(cityName);
        if (city) {
            Brick newBrick(name, caption, message, dedicateTo);
            city->addBrickToWall(newBrick);
        } else {
            cout << "City not found!" << endl;
        }
    }
};

class Admin : public User {
public:
    Admin(string n) : User(n) {}

    void editBrick(Brick &brick, string newCaption, string newMessage, string newDedicateTo) {
        brick.caption = newCaption;
        brick.message = newMessage;
        brick.dedicateTo = newDedicateTo;
    }
};

void findHottestAndColdestUsers() {
    Country* country = Country::getInstance("");

    map<string, int> userBrickCount;

    // Count bricks for each user
    for (auto &city : country->cities) {
        for (auto &wall : city.walls) {
            for (auto &brick : wall.bricks) {
                userBrickCount[brick.owner]++;
            }
        }
    }

    // Find the hottest (most bricks) and coldest (fewest bricks) users
    string hottestUser, coldestUser;
    int maxBricks = 0, minBricks = INT_MAX;

    for (auto &entry : userBrickCount) {
        if (entry.second > maxBricks) {
            maxBricks = entry.second;
            hottestUser = entry.first;
        }
        if (entry.second < minBricks) {
            minBricks = entry.second;
            coldestUser = entry.first;
        }
    }

    cout << "Hottest User: " << hottestUser << " with " << maxBricks << " bricks." << endl;
    cout << "Coldest User: " << coldestUser << " with " << minBricks << " bricks." << endl;
}

int main() {
    // Example usage of findHottestAndColdestUsers
    Country* country = Country::getInstance("country");
    country->addCity(City("noida"));
    country->addCity(City("ghaziabad"));

    // Simulate adding bricks
    User user1("Vineet"), user2("Sagar");
    user1.paintBrick("noida", "Greetings", "Hello", "ok");
    user2.paintBrick("ghaziabad", "Hello", "hi", "notok");
    user2.paintBrick("ghaziabad", "Hello", "hi", "notok");

    for (auto &city : country->cities) {
        for (auto &wall : city.walls) {
            for (auto &brick : wall.bricks) {
                
            }
        }
    }

    findHottestAndColdestUsers();

    return 0;
}

