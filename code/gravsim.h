#ifndef GRAVSIM_H
#define GRAVSIM_H

#include "vector2d.h"

#include <vector>
#include <QImage>
#include <QColor>

using namespace std;

class GravSim
{
public:
  typedef unsigned int uint;

  struct Particle {
    Vector2D p;
    Vector2D v;
    double m;
    vector <Vector2D> path;
  }; // Particle

  // CONSTANTS
  double G;

  uint stepCounter;
  uint totTime; // time passed in simulation

  vector <Particle> particles; // only react to static particles
  vector <Particle> staticParticles; // react with nothing

  double GetSize( ); // returns length of smalles bounding cube

  void AddStaticCube(double len, uint N, double M);
  void NextStep(double dt);
  void RotateStaticParticles(double theta);

  QImage ToQImage(uint SIZE, double SCALE);

  GravSim( );
  ~GravSim( );
};

#endif // GRAVSIM_H
