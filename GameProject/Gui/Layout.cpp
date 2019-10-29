#include "Layout.h"
#include "../Utils/Logger.h"

Layout::Layout(const std::string &name, Widget *parent):
    Widget(name, parent)
{
    m_background.setFillColor(sf::Color(0, 0, 0, 95));
    m_background.setOutlineThickness(2);
    m_background.setOutlineColor(sf::Color(sf::Color::Black));
}

void Layout::onMousePress(const Vector2D<int>& mousePos)
{
    Widget::onMousePress(mousePos);
    for (auto child: m_children)
    {
        if (child.second->isInside(mousePos))
            child.second->onMousePress(mousePos);
    }
}

void Layout::onMouseRelease(const Vector2D<int>& mousePos)
{
    Widget::onMouseRelease(mousePos);
    for (auto child: m_children)
    {
        if (child.second->isInside(mousePos))
            child.second->onMouseRelease(mousePos);
    }
}

void Layout::onMouseHover(const Vector2D<int> &mousePos)
{
    Widget::onMouseHover(mousePos);
    for (auto child: m_children)
    {
        if (child.second->isInside(mousePos))
            child.second->onMouseHover(mousePos);
        else
            child.second->onMouseLeave();
    }
}

void Layout::onMouseLeave()
{
    Widget::onMouseLeave();
}

void Layout::update(sf::Time deltaTime, const Vector2D<int> &mousePos)
{
    Widget::update(deltaTime, mousePos);
    for (auto child: m_children)
        child.second->update(deltaTime, mousePos);
}

void Layout::draw(sf::RenderTarget *target)
{
    target->draw(m_background);
    for (auto child: m_children)
        child.second->draw(target);
}

void Layout::setPosition(const Vector2D<int> &pos)
{
    Widget::setPosition(pos);
    Vector2D<int> global = getGlobalPosition();
    m_background.setPosition(global.x, global.y);
    for (auto child: m_children)
        child.second->setPosition(child.second->getPosition());
}

void Layout::setSize(const Vector2D<int> &size)
{
    Widget::setSize(size);
    m_background.setSize(sf::Vector2f(size.x, size.y));
}

void Layout::setState(const WidgetState &state)
{
    if (getState() == state)
        return;

    Widget::setState(state);
    if (state == WidgetState::HOVER)
        m_background.setFillColor(sf::Color(255, 0, 0, 95));
    else
        m_background.setFillColor(sf::Color(0, 0, 0, 95));
}

void Layout::addWidget(Widget *child)
{
    if (m_children.count(child->getName()) > 1)
    {
        LOG("Layout already have widget with name " + child->getName());
        delete m_children[child->getName()];
    }
    m_children[child->getName()] = child;
}
