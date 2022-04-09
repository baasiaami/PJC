#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <cmath>

void mainWindow();

void choiceWindow();

void savedImageWindow(std::string &path);

sf::Font getFont(int option);

bool isRectangleBeingClicked(sf::Event e, sf::RectangleShape &rec);

bool isPictureBeingClicked(sf::Event e, sf::Sprite &);

void editWindow(std::string &);

void type(int c, std::string &);

bool isDotBeingClicked(sf::Event &, sf::CircleShape &);

void crop(sf::Image &image, sf::Texture *newTexture, sf::Sprite &sprite, sf::CircleShape *dots, float currWidth,
          float currHeight);     //this method crops the image properly, but the cropped image is rendered wrongly
                                //cropped image can be seen after saving

std::string bigBirdPath = "Images/big_bird_image.jpg";
std::string bigCatPath = "Images/big_cat_image.jpeg";
std::string bigDogPath = "Images/big_dog_image.jpg";
std::string smallBirdPath = "Images/small_bird_image.jpg";
std::string smallCatPath = "Images/small_cat_image.jpeg";
std::string smallDogPath = "Images/small_dog_image.jpg";


int main() {
    mainWindow();
}


void mainWindow() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Image Editor", sf::Style::Titlebar | sf::Style::Close);

    sf::RectangleShape button(sf::Vector2f(130, 50));
    sf::Font font = getFont(1);
    sf::Text text("Select an image\nto edit", font, 16);

    button.setPosition(sf::Vector2f(240, 150));
    text.setFillColor(sf::Color(200, 40, 20));
    text.setPosition(button.getPosition().x + 8, button.getPosition().y + 5);

    while (window.isOpen()) {
        window.draw(button);
        window.draw(text);

        sf::Event e;
        while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (isRectangleBeingClicked(e, button)) {
                        choiceWindow();
                    }
            }
        }
        window.display();
        window.clear(sf::Color(50, 30, 100));
    }
}

sf::Font getFont(int option) {
    sf::Font font;
    switch (option) {
        case 1:
            if (!font.loadFromFile("Fonts/Roboto-LightItalic.ttf")) {
                std::cout << "There has been an issue loading font" << std::endl;
            }
            break;
        case 2:
            if (!font.loadFromFile("Fonts/Roboto-Medium.ttf")) {
                std::cout << "There has been an issue loading font" << std::endl;
            }
            break;
        default:
            std::cout << "Font: No such option" << std::endl;
            break;
    }
    return font;
}

bool isRectangleBeingClicked(sf::Event e, sf::RectangleShape &rec) {
    return e.mouseButton.x >= rec.getPosition().x && e.mouseButton.x < rec.getPosition().x + rec.getSize().x &&
           e.mouseButton.y >= rec.getPosition().y && e.mouseButton.y < rec.getPosition().y + rec.getSize().y;

}

bool isPictureBeingClicked(sf::Event e, sf::Sprite &sprite) {
    return e.mouseButton.x >= sprite.getPosition().x &&
           e.mouseButton.x < sprite.getPosition().x + sprite.getTextureRect().width &&
           e.mouseButton.y >= sprite.getPosition().y &&
           e.mouseButton.y < sprite.getPosition().y + sprite.getTextureRect().height;
}

void choiceWindow() {
    //font
    sf::Font font = getFont(2);

    //top text
    sf::Text text1("Select a sample image", font, 24);
    text1.setPosition(sf::Vector2f(10, 10));

    //small bird icon
    sf::Texture birdTexture;
    if (!birdTexture.loadFromFile(smallBirdPath, sf::IntRect(0, 0, 50, 50))) {
        std::cout << "There was a problem loading bird icon" << std::endl;
    }
    sf::Sprite birdSprite;
    birdSprite.setTexture(birdTexture);
    birdSprite.setPosition(sf::Vector2f(text1.getPosition().x, text1.getPosition().y + text1.getCharacterSize() + 15));

    //small cat icon
    sf::Texture catTexture;
    if (!catTexture.loadFromFile(smallCatPath, sf::IntRect(0, 0, 41, 62))) {
        std::cout << "There was a problem loading cat icon" << std::endl;
    }
    sf::Sprite catSprite;
    catSprite.setTexture(catTexture);
    catSprite.setPosition(birdSprite.getPosition().x + birdSprite.getTextureRect().width + 20,
                          birdSprite.getPosition().y);

    //small dog icon
    sf::Texture dogTexture;
    if (!dogTexture.loadFromFile(smallDogPath, sf::IntRect(0, 0, 57, 43))) {
        std::cout << "There was a problem loading dog icon" << std::endl;
    }
    sf::Sprite dogSprite;
    dogSprite.setTexture(dogTexture);
    dogSprite.setPosition(catSprite.getPosition().x + catSprite.getTextureRect().width + 20, catSprite.getPosition().y);

    //down text
    sf::Text text2("Select an image from this device\n(enter path below)", font, 24);
    text2.setPosition(
            sf::Vector2f(text1.getPosition().x, catSprite.getPosition().y + catSprite.getTextureRect().height + 20));

    //textbox
    sf::RectangleShape box(sf::Vector2f(470, 30));
    box.setPosition(text2.getPosition().x, text2.getPosition().y + text2.getCharacterSize() * 2 + 20);

    sf::Text textFromBox("", font, 20);
    textFromBox.setPosition(box.getPosition().x + 5, box.getPosition().y + 5);
    textFromBox.setFillColor(sf::Color::Black);

    //window
    sf::RenderWindow choiceWindow(sf::VideoMode(500, 260), "Select images",
                                  sf::Style::Titlebar | sf::Style::Close);

    while (choiceWindow.isOpen()) {

        choiceWindow.draw(text1);
        choiceWindow.draw(birdSprite);
        choiceWindow.draw(catSprite);
        choiceWindow.draw(dogSprite);
        choiceWindow.draw(text2);
        choiceWindow.draw(box);
        choiceWindow.draw(textFromBox);

        sf::Event evnt;
        while (choiceWindow.pollEvent(evnt)) {
            switch (evnt.type) {
                case sf::Event::Closed:
                    choiceWindow.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (isPictureBeingClicked(evnt, birdSprite)) {
                        editWindow(bigBirdPath);
                    }
                    if (isPictureBeingClicked(evnt, catSprite)) {
                        editWindow(bigCatPath);
                    }
                    if (isPictureBeingClicked(evnt, dogSprite)) {
                        editWindow(bigDogPath);
                    }
                    if (isRectangleBeingClicked(evnt, box)) {
                        textFromBox.setString("_");
                    }
                    break;
                case sf::Event::TextEntered:
                    if (!textFromBox.getString().isEmpty()) {
                        std::string text = textFromBox.getString();
                        if (textFromBox.getString().substring(text.length() - 1, 1) == "_") {
                            int charT = evnt.text.unicode;
                            if (charT < 128) {
                                text = text.replace(text.length() - 1, 1, "");
                                type(charT, text);
                                textFromBox.setString(text);
                            }
                        } else {    //if the string is not empty and is not equal to "_"
                            editWindow(text);
                        }
                    }
                    break;
            }
        }
        choiceWindow.display();
        choiceWindow.clear(sf::Color(150, 150, 200));
    }

}


void type(int c, std::string &text) {
    if (c != 8 && c != 13) {    //8 - delete, 13 - enter
        text += static_cast<char>(c);
        text += "_";
    } else if (c == 8) {
        if (text.length() > 0) {
            text = text.replace(text.length() - 1, 1, "");
            text += "_";
        } else {
            text += "_";
        }
    } else { //exit if enter (13) pressed -> get rid of "_"
        text = text.replace(text.length(), 1, "");
    }
}
void savedImageWindow(std::string &path) {
    sf::Image image;
    if (!image.loadFromFile(path)) {
        std::cout << "Cannot load image: " << path << std::endl;
        return;
    }

    sf::Texture imageTexture;
    float width = image.getSize().x;
    float height = image.getSize().y;
    imageTexture.loadFromImage(image, sf::IntRect(0, 0, width, height));

    sf::Sprite sprite;
    sprite.setTexture(imageTexture);
    sprite.setPosition(20, 20);

    height += 40;   // |
    width += 40;    // | additional space for frame

    sf::RectangleShape imagePanel(sf::Vector2f(width, height));
    imagePanel.setPosition(0, 0);

    //window
    sf::RenderWindow window(sf::VideoMode(width, height), "Saved image");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {

        window.draw(imagePanel);
        window.draw(sprite);

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        window.display();
        window.clear();
    }

}

void editWindow(std::string &path) {

    sf::Image image;
    if (!image.loadFromFile(path)) {
        std::cout << "Cannot load image: " << path << std::endl;
        return;
    }

    sf::Texture imageTexture;
    float width = image.getSize().x;
    float height = image.getSize().y;
    imageTexture.loadFromImage(image, sf::IntRect(0, 0, width, height));

    sf::Sprite sprite;
    sprite.setTexture(imageTexture);
    sprite.setPosition(20, 20);

    sf::Font font = getFont(2);

    const float n = 200;    //width of buttons' panel
    height += 40;   // |
    width += 40;    // | additional space for frame

    sf::RectangleShape imagePanel(sf::Vector2f(width, height));
    sf::RectangleShape buttonPanel(sf::Vector2f(n, height));

    sf::RectangleShape saveButton(sf::Vector2f(100, 50));
    sf::RectangleShape cropButton(sf::Vector2f(100, 50));

    imagePanel.setFillColor(sf::Color(200, 200, 200));
    buttonPanel.setFillColor(sf::Color(150, 150, 150));

    imagePanel.setPosition(0, 0);
    buttonPanel.setPosition(width, 0);

    saveButton.setPosition(width + n / 4.0f, height * 3 / 4.0f);
    cropButton.setPosition(width + n / 4.0f, height / 4.0f);

    //button texts
    sf::Text saveText("Save", font, 20);
    sf::Text cropText("Crop", font, 20);

    saveText.setFillColor(sf::Color(50, 50, 50));
    cropText.setFillColor(sf::Color(50, 50, 50));

    saveText.setPosition(saveButton.getPosition().x + 25, saveButton.getPosition().y + 15);
    cropText.setPosition(cropButton.getPosition().x + 25, cropButton.getPosition().y + 15);

    sf::Color color(200, 100, 100);

    sf::CircleShape dots[4];

    const int radius = 10;
    for (auto &dot : dots) {
        dot = sf::CircleShape(radius, 20);
        dot.setFillColor(color);
    }

    float x = sprite.getPosition().x - radius;
    float y = sprite.getPosition().y - radius;

    float xLength = sprite.getTextureRect().width;
    float yLength = sprite.getTextureRect().height;

    dots[0].setPosition(x, y);
    dots[1].setPosition(x + xLength, y);
    dots[2].setPosition(x, y + yLength);
    dots[3].setPosition(x + xLength, y + yLength);

    //window
    sf::RenderWindow editWindow(sf::VideoMode(width + n, height), "Editor");
    editWindow.setVerticalSyncEnabled(true);

    bool isBeingCropped = false;
    bool isDotHold = false;
    bool isHorizontal = false;
    bool isFirstMove = true;
    int index = -1;

    float currWidth = sprite.getTextureRect().width;
    float currHeight = sprite.getTextureRect().height;

    while (editWindow.isOpen()) {

        editWindow.draw(imagePanel);
        editWindow.draw(buttonPanel);
        editWindow.draw(sprite);
        editWindow.draw(saveButton);
        editWindow.draw(cropButton);
        editWindow.draw(saveText);
        editWindow.draw(cropText);

        if (isBeingCropped) {
            for (const auto &dot : dots) {
                editWindow.draw(dot);
            }
        }

        sf::Event event;
        while (editWindow.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    editWindow.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (isRectangleBeingClicked(event, cropButton)) {
                        if (isBeingCropped) {

                            sf::Texture *newTexture;

                            crop(image, newTexture, sprite, dots, currWidth, currHeight);   //cropping image

                            sprite.setPosition(dots[0].getPosition());
                            sprite.setTextureRect(
                                    sf::IntRect(dots[0].getPosition().x, dots[0].getPosition().y, currWidth,
                                                currHeight));
                            sprite.setTexture(*newTexture);
                            editWindow.draw(sprite);
                            isBeingCropped = false;

                        } else {
                            isBeingCropped = true;
                        }
                    }

                    if (isBeingCropped) {
                        for (int i = 0; i < 4; i++) {
                            if (isDotBeingClicked(event, dots[i])) {
                                isDotHold = true;
                                index = i;
                                break;
                            } else {
                                isDotHold = false;
                            }
                        }
                    }

                    if (isRectangleBeingClicked(event, saveButton)) {   //saving image
                        std::string pathToSave = "Images/edited_image.png";
                        image.saveToFile(pathToSave);
                        savedImageWindow(pathToSave);
                        editWindow.close();

                    }
                    break;
                case sf::Event::MouseMoved:
                    if (isDotHold) {
                        int dX = dots[index].getPosition().x;
                        int dY = dots[index].getPosition().y;

                        int a = event.mouseMove.x;
                        int b = event.mouseMove.y;


                        switch (index) {
                            case 0:
                                if (isFirstMove) {
                                    if (abs(dX - a) > abs(dY - b)) {
                                        isHorizontal = true;
                                        dots[0].setPosition(a, dY);
                                        dots[2].setPosition(a, dY + currHeight);
                                    } else {
                                        dots[0].setPosition(dX, b);
                                        dots[1].setPosition(dX + currWidth, b);
                                    }
                                    isFirstMove = false;
                                } else {
                                    if (isHorizontal) {
                                        dots[0].setPosition(a, dY);
                                        dots[2].setPosition(a, dY + currHeight);
                                    } else {
                                        dots[0].setPosition(dX, b);
                                        dots[1].setPosition(dX + currWidth, b);
                                    }
                                }
                                break;
                            case 1:
                                if (isFirstMove) {
                                    if (abs(dX - a) > abs(dY - b)) {
                                        isHorizontal = true;
                                        dots[1].setPosition(a, dY);
                                        dots[3].setPosition(a, dY + currHeight);
                                    } else {
                                        dots[1].setPosition(dX, b);
                                        dots[0].setPosition(dX - currWidth, b);
                                    }
                                    isFirstMove = false;
                                } else {
                                    if (isHorizontal) {
                                        dots[1].setPosition(a, dY);
                                        dots[3].setPosition(a, dY + currHeight);
                                    } else {
                                        dots[1].setPosition(dX, b);
                                        dots[0].setPosition(dX - currWidth, b);
                                    }
                                }
                                break;
                            case 2:
                                if (isFirstMove) {
                                    if (abs(dX - a) > abs(dY - b)) {
                                        isHorizontal = true;
                                        dots[2].setPosition(a, dY);
                                        dots[0].setPosition(a, dY - currHeight);
                                    } else {
                                        dots[2].setPosition(dX, b);
                                        dots[3].setPosition(dX + currWidth, b);
                                    }
                                    isFirstMove = false;
                                } else {
                                    if (isHorizontal) {
                                        dots[2].setPosition(a, dY);
                                        dots[0].setPosition(a, dY - currHeight);
                                    } else {
                                        dots[2].setPosition(dX, b);
                                        dots[3].setPosition(dX + currWidth, b);
                                    }
                                }
                                break;
                            case 3:
                                if (isFirstMove) {
                                    if (abs(dX - a) > abs(dY - b)) {
                                        isHorizontal = true;
                                        dots[3].setPosition(a, dY);
                                        dots[1].setPosition(a, dY - currHeight);
                                    } else {
                                        dots[3].setPosition(dX, b);
                                        dots[2].setPosition(dX - currWidth, b);
                                    }
                                    isFirstMove = false;
                                } else {
                                    if (isHorizontal) {
                                        dots[3].setPosition(a, dY);
                                        dots[1].setPosition(a, dY - currHeight);
                                    } else {
                                        dots[3].setPosition(dX, b);
                                        dots[2].setPosition(dX - currWidth, b);
                                    }
                                }
                                break;
                        }
                    }

                    break;
                case sf::Event::MouseButtonReleased:
                    if (isDotHold) {
                        if (isHorizontal) {
                            currWidth = abs(dots[0].getPosition().x - dots[1].getPosition().x);
                        } else {
                            currHeight = abs(dots[0].getPosition().y - dots[2].getPosition().y);
                        }

                        isHorizontal = false;
                        isDotHold = false;
                        isFirstMove = true;
                        index = -1;

                    }
                    break;
            }
        }

        editWindow.display();
        editWindow.clear();
    }
}

bool isDotBeingClicked(sf::Event &event, sf::CircleShape &dot) {

    // sqrt( (x1 - x2)^2 + (y1 - y2)^2 ) - distance from center

    int x1 = event.mouseButton.x;
    int x2 = dot.getPosition().x + dot.getRadius();

    int y1 = event.mouseButton.y;
    int y2 = dot.getPosition().y + dot.getRadius();

    if (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) <= dot.getRadius()) {
        return true;
    }
    return false;
}

void crop(sf::Image &image, sf::Texture *newTexture, sf::Sprite &sprite, sf::CircleShape *dots, float currWidth,
          float currHeight) {

    sf::Image newImage;
    newImage.create(currWidth, currHeight, sf::Color::Magenta);
    std::cout << currWidth << " " << currHeight << "\n";

    int r = dots[0].getRadius();

    std::cout << dots[0].getPosition().x - 20 + r << "\n";
    std::cout << dots[0].getPosition().y - 20 + r << "\n";
    for (int i = 0; i < newImage.getSize().x; i++) {
        for (int j = 0; j < newImage.getSize().y; j++) {
            newImage.setPixel(i, j,
                              image.getPixel(i + dots[0].getPosition().x - 20 + r,
                                             j + dots[0].getPosition().y - 20 + r));
        }

    }

    image = newImage;

    *newTexture = sf::Texture();

    if (!newTexture->loadFromImage(newImage,
                                   sf::IntRect(0, 0, currWidth, currHeight))) {
        std::cout << "cannot load the cropped image\n";
    }


}
