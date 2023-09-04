#include <iostream>
#include <vector>
#include <iomanip>

struct Vector2D
{
  explicit Vector2D(double x = 0, double y = 0)
  {
    this->x = x;
    this->y = y;
  }

  Vector2D& operator+= (const Vector2D& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  Vector2D operator* (const float& rhs) const
  {
    return Vector2D(x * rhs, y * rhs);
  }

  Vector2D operator- (const Vector2D& rhs) const
  {
    return Vector2D(x - rhs.x, y - rhs.y);
  }

  double x;
  double y;
};

class Agent
{
public:
  explicit Agent(Vector2D position = Vector2D(), Vector2D velocity = Vector2D())
  {
    m_position = position;
    m_velocity = velocity;
  }

  void update(double deltaTime)
  {
    m_position += m_velocity * deltaTime;
    std::cout << std::fixed << std::setprecision(3)<< m_position.x << " " << m_position.y << " " << m_velocity.x << " " << m_velocity.y << std::endl;
  }

  void calculateCohesion(double radius, Agent agents[], int numOfAgents, double deltaTime)
  {
    calculateNeighbors(radius, agents, numOfAgents);

    Vector2D center;
    for (auto i = neighborhood.begin(); i < neighborhood.end(); ++i)
    {
      center.x += i->getPos().x;
      center.y += i->getPos().y;
    }

    Vector2D force;
    force = center - m_position;
    m_velocity += force * deltaTime;
  }

  void calculateCohesion()
  {

  }

  Vector2D getPos()
  {
    return m_position;
  }

  Vector2D getVel()
  {
    return m_velocity;
  }

private:
  void calculateNeighbors(double radius, Agent agents[], int numOfAgents)
  {
    for (int i = 0; i < numOfAgents; i++)
    {
      if (&agents[i] == this) continue;

      Vector2D agentPos = agents[i].getPos();
      if(agentPos.x > m_position.x + radius || agentPos.x < m_position.x - radius) continue;
      if(agentPos.y > m_position.y + radius || agentPos.y < m_position.y - radius) continue;

      neighborhood.push_back(agents[i]);
    }
  }

  Vector2D m_position, m_velocity;
  std::vector<Agent> neighborhood;
};

int main()
{
  bool quit = false;

  double c_radius,s_radius, a_radius;
  double c_constant, s_constant, a_constant;
  double maxForce;
  double deltaTime;
  int numOfAgents;

  std::cin >> c_radius >> s_radius >> maxForce >> a_radius >> c_constant >> s_constant >> a_constant >> numOfAgents;

  auto* agents = new Agent[numOfAgents];
  for (int i = 0; i < numOfAgents; ++i)
  {
    Vector2D pos, vel;
    std::cin >> pos.x >> pos.y >> vel.x >> vel.y;
    agents[i] = Agent(pos, vel);

    //std::cout << std::fixed << std::setprecision(3)<< agents[i].getPos().x << " " << agents[i].getPos().y << " " << agents[i].getVel().x << " " << agents[i].getVel().y << std::endl;
  }

  std::cin >> deltaTime;

  for (int i = 0; i < numOfAgents; i++)
  {
    agents[i].calculateCohesion(c_radius, agents, numOfAgents, deltaTime);
  }

  for (int i = 0; i < numOfAgents; i++)
  {
    agents[i].update(deltaTime);
  }
}