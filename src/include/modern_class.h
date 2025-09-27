#include <iostream>
#include <memory>
#include <vector>
#include <optional>
#include <algorithm>

class User {
    std::string name;
    int age;

public:
    User(std::string name, int age) : name(std::move(name)), age(age) {}

    const std::string& getName() const { return name; }
    int getAge() const { return age; }
};

class UserManager {
    std::vector<std::unique_ptr<User>> users;

public:
    void addUser(std::string name, int age) {
        users.push_back(std::make_unique<User>(std::move(name), age));
    }

    std::optional<std::reference_wrapper<const User>> findUser(const std::string& name) const {
        auto it = std::find_if(users.begin(), users.end(), [&name](const std::unique_ptr<User>& user) {return user->getName() == name; });

        if (it != users.end()) {
            return std::cref(**it);
        }
        return std::nullopt;
    }
    
    // std::expected<std::reference_wrapper<const User>, std::string> findUser2(const std::string& name) const {
    //     auto it = std::find_if(users.begin(), users.end(), [&name](const std::unique_ptr<User>& user) { return user->getName() == name; });

    //     if (it != users.end()) {
    //         return std::cref(**it);
    //     }
    //     return std::unexpected("User '" + name + "' not found.");
    // }

};

/**
 * 

int main() {
    UserManager manager;
    manager.addUser("Alice", 30);
    manager.addUser("Bob", 25);

    auto result = manager.findUser("Charlie");

    if (result.has_value()) {
        std::cout << "Found user: " << result->get().getName() << '\n';
    } else {
        std::cerr << "User not found.\n";
    }
}

int main() {
    UserManager manager;
    manager.addUser("Alice", 30);
    manager.addUser("Bob", 25);

    auto result = manager.findUser("Charlie");

    if (result) {
        std::cout << "Found user: " << result->get().getName() << '\n';
    } else {
        std::cerr << "Error: " << result.error() << '\n';
    }
}

 */
