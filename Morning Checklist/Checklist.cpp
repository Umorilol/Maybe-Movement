//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include <vector>
//#include <iostream>
//
//class checkBox
//{
//public:
//    checkBox( sf::Vector2f boxPosition, sf::Text text ) {
//        //CheckBox
//        this->text = text;
//        this->boxPosition = boxPosition;
//        checked = false;
//        box.setSize( sf::Vector2f(15.f, 15.f ));
//        box.setPosition( sf::Vector2f( boxPosition ) );
//        box.setOutlineThickness( 4 );
//        box.setOutlineColor( sf::Color::Blue );
//        //text.setPosition(sf::Vector2f(boxPosition.x + 5, boxPosition.y ));
//    }
//
//    void checkClick( sf::Vector2i mousePos );
//
//    sf::RectangleShape box;
//    sf::Text text;
//    sf::Vector2f boxPosition;
//    bool checked;
//};
//
//void checkBox::checkClick( sf::Vector2i mousePos ) {
//    if ( mousePos.x > box.getPosition().x && mousePos.x < box.getPosition().x + 15.f ) {
//        if ( mousePos.y > box.getPosition().y && mousePos.y < box.getPosition().y + 15.f ) {
//            checked = true;
//            std::cout << "checked" << std::endl;
//            box.setFillColor( sf::Color::Magenta );
//        }
//    }
//}
//
//int main()
//{
//    int arrayLength = 5;
//    float x = 20.f, y = 20.f;
//
//    std::vector<checkBox> boxes;
//
//    sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Morning Checklist" );
//    window.setFramerateLimit( 60 );
//
//    sf::Font font;
//    if ( !font.loadFromFile("Fonts/Dosis-Light.ttf") )
//        throw ( "Could not load font!" ); 
//
//    std::string stringList[] { "Eat Breakfast", "Take Meds", "Exercise", "Shower", "Brush Teeth" };
//
//    sf::Text textList[5];
//    for ( size_t i = 0; i < 5; i++ )
//    {
//        textList[ i ].setFont( font );
//        textList[ i ].setString( stringList[ i ] );
//        textList[ i ].setCharacterSize( 14 );
//    }
//   
//    for ( size_t i = 0; i < arrayLength; i++ ) {
//        textList[ i ].setPosition( sf::Vector2f( x + 20, y ) );
//        boxes.push_back( checkBox( sf::Vector2f(x, y), textList[i]));
//        y += 20;
//    }
//
//    while ( window.isOpen() )
//    {
//        sf::Event event;
//        while ( window.pollEvent( event ) )
//        {
//            if ( event.type == sf::Event::Closed )
//                window.close();
//        }
//        //Check if mouse pos is inside of a button and mark it
//        for ( size_t i = 0; i < arrayLength; i++ ) {
//            if ( boxes[i].checked == false ) {
//                if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ) {
//                    sf::Vector2i position = sf::Mouse::getPosition( window );
//                    boxes[i].checkClick(position);
//                }
//            }
//        }
//
//        window.clear();
//
//       //Draw Boxes and text
//        for ( size_t i = 0; i < arrayLength; i++ ) {
//            window.draw( boxes[i].box );
//            window.draw( boxes[ i ].text );
//        }
//
//       // window.draw( box1.text );
//        window.display();
//    }
//
//    return 0;
//}
