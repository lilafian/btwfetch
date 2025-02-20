#include <iostream>
#include <sys/utsname.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>

std::string getDistro() {
    std::ifstream file("/etc/os-release");
    if (!file.is_open()) {
        return "a secret distro";
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("PRETTY_NAME=") == 0) {
            size_t start = line.find('=') + 1;
            std::string value = line.substr(start);

            if (!value.empty() && value.front() == '"' && value.back() == '"') {
                value = value.substr(1, value.size() - 2);
            }
            return value;
        }
    }
    return "a secret distro";
}

const char* getDeWm() {
    const char* xdgCurrentDesktop = std::getenv("XDG_CURRENT_DESKTOP");
    if (xdgCurrentDesktop) {
        return xdgCurrentDesktop;
    }
    const char* desktopSession = std::getenv("DESKTOP_SESSION");
    if (desktopSession) {
        return desktopSession;
    }
    return "no DE or WM";
}

std::string getDistroArt(int line) {
    std::string distro = getDistro();
    if (distro == "Arch Linux") {
        switch (line) {
            case 1:
                return "\033[1;36m  /\\    \033[0m";
            case 2:
                return "\033[1;36m /  \\   \033[0m";
            case 3:
                return "\033[1;36m/ /\\ \\  \033[0m";
        }
    }
    return "";
}

int main() {
    struct utsname name;
    if (uname(&name)) exit(-1);
    std::cout << getDistroArt(1) << "i use \033[1;36m" << getDistro() << "\033[0m btw\r\n";
    std::cout << getDistroArt(2) << "i use \033[1;36m" << getDeWm() << "\033[0m btw\r\n";
    std::cout << getDistroArt(3) << "i use \033[1;36m" << name.sysname << " v" << name.release << "\033[0m btw\r\n";
    return 0;
}
