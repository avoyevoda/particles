#include "Engine.h"

Engine::Engine()
{
	VideoMode vm(960, 540);
	// Create and open a window for the game
	m_Window.create(vm, "Screen", Style::Default);
}

void Engine::run()
{
	// Variables to control time itself
	Clock clock;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	
	while (m_Window.isOpen())
	{
		// Measure time
		Time dt = clock.restart();
		
		input();
		update(dt.asSeconds());
		draw();
	}

}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "the left button was pressed" << std::endl;
				std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				std::cout << "mouse y: " << event.mouseButton.y << std::endl;

				int randPoints = rand() % 50 + 25;
				Particle one(m_Window, randPoints, Vector2i(event.mouseButton.x, event.mouseButton.y));
				m_particles.push_back(one);
			}
		}

		// Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition);
		//create loop to make 5 particles
		// numPoints is random 25:50
		// this is in the wrong spot so it does that particle draw on mouse move
		int randPoints = rand() % 50 + 25;
		Particle one(m_Window, randPoints, Vector2i(event.mouseButton.x, event.mouseButton.y));
		m_particles.push_back(one);
	}

}

void Engine::update(float dtAsSeconds)
{
	/*
	for (int i = 0; i < m_particles.size(); i++)
	{
		if (m_particles[i].getTTL() > 0.0)
		{
			m_particles[i].update(dtAsSeconds);
		}
		else
		{
			//needs itarator 
			// needs work
			//m_particles.erase(m_particles[i]);
		}
	}*/

	vector<Particle>::iterator ptr;
	for (ptr = m_particles.begin(); ptr < m_particles.end(); )
	{
		if ((*ptr).getTTL() > 0.0)
		{
			(*ptr).update(dtAsSeconds);
			ptr++;
		}
		else
		{
			ptr = m_particles.erase(ptr);
		}
	}


}

void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles[i]);
	}
	m_Window.display();

}