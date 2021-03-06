#include "Button.h"
#include "GuiManager.h"
#include "../../Utils/Logger.h"

Button::Button(const std::string &name, const GuiEventController& controller, Widget *parent): Widget(name, controller, parent), m_toggled(false)
{
    m_background.setFillColor(sf::Color(0, 0, 0, 95));
    m_background.setOutlineThickness(1);
    m_background.setOutlineColor(sf::Color(215, 183, 64));
    setHoverable(true);

    font.loadFromFile("arial.ttf");
    m_text.setFont(font);
    m_text.setCharacterSize(20);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1);
    m_text.setStyle(sf::Text::Bold);
}

void Button::onMousePress(const Vector2D<int> &mousePos)
{
    Widget::onMousePress(mousePos);
    m_controller.elementPressed(getName());
}

void Button::onMouseRelease(const Vector2D<int> &mousePos)
{
    Widget::onMouseRelease(mousePos);
}

void Button::onMouseHover(const Vector2D<int> &mousePos)
{
    Widget::onMouseHover(mousePos);
}

void Button::onMouseLeave()
{
    Widget::onMouseLeave();
}

void Button::update(sf::Time deltaTime, const Vector2D<int> &mousePos)
{
    Widget::update(deltaTime, mousePos);
}

void Button::draw(sf::RenderTarget *target)
{
    target->draw(m_background);
    target->draw(m_text);
}

void Button::setPosition(const Vector2D<int> &pos)
{
    Widget::setPosition(pos);
    adjustContent();
}

void Button::setSize(const Vector2D<int> &size)
{
    Widget::setSize(size);
    adjustContent();
}

void Button::setState(const WidgetState &state)
{
    if (getState() == state)
        return;

    Widget::setState(state);
    if (state == WidgetState::HOVER)
        m_background.setFillColor(sf::Color(255, 0, 0, 95));
    else
        m_background.setFillColor(sf::Color(0, 0, 0, 95));
}

void Button::setText(const std::string &text)
{
    m_text.setString(text);
    adjustContent();
}

void Button::adjustContent()
{
    m_background.setSize(sf::Vector2f(getSize().x, getSize().y));
    Vector2D<int> global = getGlobalPosition();
    m_background.setPosition(global.x, global.y);
    m_text.setPosition(global.x + getSize().x / 2, global.y + getSize().y / 2);
    m_text.setOrigin(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2,
                     m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2);
}

void Button::setToggled(bool toggled)
{
    m_toggled = toggled;
    if (toggled)
    {
        m_background.setOutlineThickness(4);
    }
    else
    {
        m_background.setOutlineThickness(1);
    }
}

bool Button::isToggled()
{
    return m_toggled;
}
