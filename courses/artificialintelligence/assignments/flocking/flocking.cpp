#include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>

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

  Vector2D operator/ (const float& rhs) const
  {
    return Vector2D(x / rhs, y / rhs);
  }

  Vector2D operator- (const Vector2D& rhs) const
  {
    return Vector2D(x - rhs.x, y - rhs.y);
  }

  Vector2D operator+ (const Vector2D& rhs) const
  {
    return Vector2D(x + rhs.x, y + rhs.y);
  }

  [[nodiscard]] Vector2D normalize() const
  {
    double mag = sqrt(x * x + y * y);
    if (mag == 0) return Vector2D(x,y);
    return Vector2D(x / mag,y / mag);
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
    Vector2D force = m_cohesionForce + m_separationForce + m_alignmentForce;
    m_velocity += force * deltaTime;
    m_position += m_velocity * deltaTime;
    std::cout << std::fixed << std::setprecision(3)<< m_position.x << " " << m_position.y << " " << m_velocity.x << " " << m_velocity.y << std::endl;
  }

  void calculateCohesion(double constant, double radius, Agent agents[], int numOfAgents)
  {
    calculateNeighbors(radius, agents, numOfAgents, false);

    Vector2D center;
    for (auto i = m_neighborhood.begin(); i < m_neighborhood.end(); ++i)
    {
      center += i->getPos();
    }

    Vector2D force;
    force = center - m_position;
    m_cohesionForce = force.normalize() * constant;
  }

  void calculateSeparation(double constant, double maxForce, double radius, Agent agents[], int numOfAgents)
  {
    calculateNeighbors(radius, agents, numOfAgents, false);

    Vector2D force;
    for (auto i = m_neighborhood.begin(); i < m_neighborhood.end(); ++i)
    {
      force += m_position - i->getPos();
    }

    m_separationForce = force.normalize() * constant;
  }

  void calculateAlignment(double constant, double radius, Agent agents[], int numOfAgents)
  {
    calculateNeighbors(radius, agents, numOfAgents, true);

    Vector2D averageVelocity;
    for (auto i = m_neighborhood.begin(); i < m_neighborhood.end(); ++i)
    {
      averageVelocity += i->getVel();
    }

    averageVelocity = averageVelocity / m_neighborhood.size();
    m_alignmentForce = averageVelocity * constant;
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

  void calculateNeighbors(double radius, Agent agents[], int numOfAgents, bool includeSelf)
  {
    m_neighborhood.clear();

    for (int i = 0; i < numOfAgents; i++)
    {
      if(!includeSelf)
        if (&agents[i] == this) continue;

      Vector2D agentPos = agents[i].getPos();
      if(agentPos.x > m_position.x + radius || agentPos.x < m_position.x - radius) continue;
      if(agentPos.y > m_position.y + radius || agentPos.y < m_position.y - radius) continue;

      m_neighborhood.push_back(agents[i]);
    }
  }

  Vector2D m_position, m_velocity;
  Vector2D m_cohesionForce, m_separationForce, m_alignmentForce;
  std::vector<Agent> m_neighborhood;
};

int main()
{
  double c_radius,s_radius, a_radius;
  double c_constant, s_constant, a_constant;
  double maxForce;
  double deltaTime;
  int numOfAgents;

  //Collect Sim Info
  std::cin >> c_radius >> s_radius >> maxForce >> a_radius >> c_constant >> s_constant >> a_constant >> numOfAgents;

  //Collect Agent Info
  auto* agents = new Agent[numOfAgents];
  for (int i = 0; i < numOfAgents; ++i)
  {
    Vector2D pos, vel;
    std::cin >> pos.x >> pos.y >> vel.x >> vel.y;
    agents[i] = Agent(pos, vel);
  }

  //Game Loop
  while (std::cin >> deltaTime)
  {
    for (int i = 0; i < numOfAgents; i++)
    {
      agents[i].calculateCohesion(c_constant, c_radius, agents, numOfAgents);
      agents[i].calculateSeparation(s_constant, maxForce, s_radius, agents, numOfAgents);
      agents[i].calculateAlignment(a_constant, a_radius, agents, numOfAgents);
    }

    for (int i = 0; i < numOfAgents; i++)
    {
      agents[i].update(deltaTime);
    }
  }

  //Clean Up
  delete[] agents;
}