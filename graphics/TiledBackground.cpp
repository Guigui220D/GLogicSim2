#include "TiledBackground.h"

TiledBackground::TiledBackground() :
    va(sf::Quads, 4)
{
    sf::RenderTexture render_texture;
    render_texture.create(100, 100);

    //render_texture.clear(sf::Color(254, 229, 153));
    render_texture.clear(sf::Color(50, 80, 150));
    {
        sf::RectangleShape rs;
        rs.setFillColor(sf::Color(0, 0, 0, 30));
        rs.setSize(sf::Vector2f(50.f, 50.f));

        render_texture.draw(rs);

        rs.setPosition(sf::Vector2f(50.f, 50.f));
        render_texture.draw(rs);
    }
    render_texture.display();

    t = render_texture.getTexture();
    t.setRepeated(true);
}

TiledBackground::~TiledBackground()
{

}

void TiledBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(va, &t);
}

void TiledBackground::updateWithView(const sf::View& view)
{
    sf::Vector2f a, b, c, d;

    a = view.getCenter() + sf::Vector2f(-view.getSize().x, -view.getSize().y);
    b = view.getCenter() + sf::Vector2f( view.getSize().x, -view.getSize().y);
    c = view.getCenter() + sf::Vector2f( view.getSize().x,  view.getSize().y);
    d = view.getCenter() + sf::Vector2f(-view.getSize().x,  view.getSize().y);

    va[0] = sf::Vertex(a, a);
    va[1] = sf::Vertex(b, b);
    va[2] = sf::Vertex(c, c);
    va[3] = sf::Vertex(d, d);
}
