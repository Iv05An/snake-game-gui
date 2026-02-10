// ResourceManager.cpp
#include "ResourceManager.h"
#include "Constants.h"

// Загрузка текстуры из файла
bool ResourceManager::loadTexture(const std::string& name, const std::string& filename)
{
    // Проверяем, не загружена ли уже текстура
    if (textures.find(name) != textures.end())
    {
        std::cout << "Texture '" << name << "' already loaded" << std::endl;
        return true;
    }
    
    // Создаём умный указатель на текстуру
    auto texture = std::make_shared<sf::Texture>();
    
    // Пытаемся загрузить из файла
    if (!texture->loadFromFile(filename))
    {
        std::cerr << "ERROR: Failed to load texture '" << name 
                  << "' from file: " << filename << std::endl;
        
        // Создаём текстуру-заглушку
        createPlaceholderTexture();
        return false;
    }
    
    // Настройки текстуры для улучшения качества
    texture->setSmooth(true);  // Включить сглаживание
    texture->setRepeated(false);  // Не повторять текстуру
    
    std::cout << "SUCCESS: Loaded texture '" << name 
              << "' from " << filename 
              << " (" << texture->getSize().x << "x" << texture->getSize().y << ")" 
              << std::endl;
    
    // Сохраняем в map
    textures[name] = texture;
    return true;
}

// Получение текстуры по имени
sf::Texture& ResourceManager::getTexture(const std::string& name)
{
    auto it = textures.find(name);
    if (it != textures.end())
    {
        return *(it->second);
    }
    
    // Если текстура не найдена
    std::cerr << "WARNING: Texture '" << name << "' not found!" << std::endl;
    
    // Пытаемся загрузить по умолчанию
    // if (loadTexture(name, "assets/textures/" + name + ".png"))
    // {
    //     return *(textures[name]);
    // }
    
    // Создаём и возвращаем заглушку
    createPlaceholderTexture();
    return *(textures["placeholder"]);
}

// Проверка существования текстуры
bool ResourceManager::hasTexture(const std::string& name) const
{
    return textures.find(name) != textures.end();
}

// Создание текстуры-заглушки (шахматная доска)
void ResourceManager::createPlaceholderTexture()
{
    if (hasTexture("placeholder"))
        return;
    
    auto texture = std::make_shared<sf::Texture>();
    
    // Создаём изображение 64x64
    sf::Image image;
    image.create(64, 64, sf::Color::Magenta);
    
    // Рисуем шахматную доску
    for (unsigned int x = 0; x < 64; ++x)
    {
        for (unsigned int y = 0; y < 64; ++y)
        {
            if ((x / 8 + y / 8) % 2 == 0)
            {
                image.setPixel(x, y, sf::Color::Black);
            }
        }
    }
    
    texture->loadFromImage(image);
    texture->setSmooth(false);
    textures["placeholder"] = texture;
    
    std::cout << "Created placeholder texture" << std::endl;
}

// // Загрузка шрифта (для будущего)
// bool ResourceManager::loadFont(const std::string& name, const std::string& filename)
// {
//     auto font = std::make_shared<sf::Font>();
//     if (!font->loadFromFile(filename))
//     {
//         std::cerr << "Failed to load font: " << filename << std::endl;
//         return false;
//     }
    
//     fonts[name] = font;
//     return true;
// }

// sf::Font& ResourceManager::getFont(const std::string& name)
// {
//     if (fonts.find(name) != fonts.end())
//     {
//         return *(fonts[name]);
//     }
    
//     // Возвращаем системный шрифт в случае ошибки
//     static sf::Font defaultFont;
//     if (defaultFont.getInfo().family == "")
//     {
//         defaultFont.loadFromFile("C:/Windows/Fonts/arial.ttf");
//     }
//     return defaultFont;
// }

// // Загрузка звука (для будущего)
// bool ResourceManager::loadSoundBuffer(const std::string& name, const std::string& filename)
// {
//     auto buffer = std::make_shared<sf::SoundBuffer>();
//     if (!buffer->loadFromFile(filename))
//     {
//         std::cerr << "Failed to load sound: " << filename << std::endl;
//         return false;
//     }
    
//     soundBuffers[name] = buffer;
//     return true;
// }

// sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& name)
// {
//     if (soundBuffers.find(name) != soundBuffers.end())
//     {
//         return *(soundBuffers[name]);
//     }
    
//     static sf::SoundBuffer emptyBuffer;
//     return emptyBuffer;
// }

// Очистка всех ресурсов
void ResourceManager::clearAll()
{
    textures.clear();
    fonts.clear();
    soundBuffers.clear();
    std::cout << "Cleared all resources" << std::endl;
}