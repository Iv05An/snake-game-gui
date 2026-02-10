// ResourceManager.h
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <memory>
#include <iostream>

class ResourceManager
{
private:
    // Хранилища ресурсов (умные указатели для автоматического удаления)
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;
    std::map<std::string, std::shared_ptr<sf::Font>> fonts;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;
    
    // Приватный конструктор для Singleton
    ResourceManager() = default;
    
public:
    // Удаляем копирование
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    // Получение единственного экземпляра
    static ResourceManager& getInstance()
    {
        static ResourceManager instance;
        return instance;
    }
    
    // === ТЕКСТУРЫ ===
    
    // Загрузка текстуры из файла
    bool loadTexture(const std::string& name, const std::string& filename);
    
    // Получение текстуры по имени
    sf::Texture& getTexture(const std::string& name);
    
    // Проверка существования текстуры
    bool hasTexture(const std::string& name) const;
    
    // Создание текстуры-заглушки (на случай ошибки)
    void createPlaceholderTexture();
    
    // // === ФОНТЫ === (для будущего)
    // bool loadFont(const std::string& name, const std::string& filename);
    // sf::Font& getFont(const std::string& name);
    
    // // === ЗВУКИ === (для будущего)
    // bool loadSoundBuffer(const std::string& name, const std::string& filename);
    // sf::SoundBuffer& getSoundBuffer(const std::string& name);
    
    // Очистка ресурсов
    void clearAll();
};

#endif