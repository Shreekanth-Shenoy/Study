#include <iostream>
#include <memory>

// Command Interface
class Command {
public:
    virtual void execute() = 0;
};

// Concrete Command: Toast Command
class ToastCommand : public Command {
public:
    void execute() override {
        std::cout << "Bread is toasted" << std::endl;
    }
};

// Another Concrete Command: Butter Command
class ButterCommand : public Command {
public:
    void execute() override {
        std::cout << "Bread is buttered" << std::endl;
    }
};

// Invoker
class Toaster {
private:
    std::unique_ptr<Command> command;

public:
    void setCommand(std::unique_ptr<Command> cmd) {
        command = std::move(cmd);
    }

    void pressButton() {
        if (command) {
            command->execute();
        }
    }
};

// Client
int main() {
    // Create instances of concrete commands using unique pointers
    auto toast = std::make_unique<ToastCommand>();
    auto butter = std::make_unique<ButterCommand>();

    // Create an invoker
    Toaster toaster;

    // Toast the bread
    toaster.setCommand(std::move(toast));
    toaster.pressButton(); // Output: Bread is toasted

    // Butter the bread
    toaster.setCommand(std::move(butter));
    toaster.pressButton(); // Output: Bread is buttered

    return 0;
}
