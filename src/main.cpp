#include "GameWindow.h"
#include <iostream>
#include <chrono>

int main() {
    std::cout << "=== SNAKE GAME START ===" << std::endl;
    std::cout << "Compiled: " << __DATE__ << " " << __TIME__ << std::endl;
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    try {
        GameWindow game;
        std::cout << "Game initialized successfully!" << std::endl;
        game.run();
    } 
    catch (const std::exception& e) {
        std::cerr << "\nFATAL ERROR: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "\nUnknown fatal error!" << std::endl;
        return 1;
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    
    std::cout << "\n=== GAME ENDED ===" << std::endl;
    std::cout << "Total play time: " << duration.count() << " seconds" << std::endl;
    std::cout << "Thanks for playing!" << std::endl;
    
    // Пауза перед закрытием (только для Windows)
    #ifdef _WIN32
    std::cout << "\nPress Enter to exit..." << std::endl;
    std::cin.get();
    #endif
    
    return 0;
}