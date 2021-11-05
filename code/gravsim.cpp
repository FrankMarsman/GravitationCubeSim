#include "gravsim.h"

#include <cmath>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <QPainter>
#include <QPainterPath>
#include <QImage>
#include <QPen>
#include <QPointF>


// returns length of smallest bounding cube centered at origin
double GravSim::GetSize( ) {
  double L = 0;
  for (uint i = 0; i < particles.size( ); i++) {
    if (fabs(particles[i].p.x) > L)
      L = fabs(particles[i].p.x);
    if (fabs(particles[i].p.y) > L)
      L = fabs(particles[i].p.y);
  } // for
  return L;
}
// adds static cube centered at origin, with sides of length
// len, having N+1 particles on a size, so (N+1)^2 total,
// all particles together weigh M kg
void GravSim::AddStaticCube(double len, GravSim::uint N, double M) {
  double m = M / (double(N+1) * double(N+1));
  for (uint i = 0; i <= N; i++) {
    for (uint j = 0; j <= N; j++) {
      Particle P;
      P.p.x = (double(i) / N) * len - 0.5 * len;
      P.p.y = (double(j) / N) * len - 0.5 * len;
      P.m = m;
      this->staticParticles.push_back(P);
    } // for
  } // for
} // AddStaticCube

// updates positions of particles
void GravSim::NextStep(double dt) {
  Vector2D pos, r, F;
  Particle P;
  for (uint i = 0; i < particles.size( ); i++) {
    F = Vector2D(0, 0);
    pos = particles[i].p;

    for (uint k = 0; k < staticParticles.size( ); k++) {
      P = staticParticles[k];
      r = pos - P.p; // vector from particle[i] to P
      F -= P.m * particles[i].m * G * (r.Normalized( ) / (r.Length( ) * r.Length( )));
    } // for

    particles[i].v += (F / particles[i].m) * dt;
    particles[i].p += particles[i].v * dt;

    if (this->stepCounter % 50 == 0)
      particles[i].path.insert(particles[i].path.begin( ), particles[i].p);
  } // for
  stepCounter++;
  totTime += uint(dt);
} // NextStep

void GravSim::RotateStaticParticles(double theta) {
  Particle P;
  for (uint k = 0; k < staticParticles.size( ); k++) {
    P = staticParticles[k];
    staticParticles[k].p.x = cos(theta) * P.p.x - sin(theta) * P.p.y;
    staticParticles[k].p.y = cos(theta) * P.p.y + sin(theta) * P.p.x;
  } // for
} // RotateStaticParticles

// draws particle on image. positions multiplied by scale,
// particles pos is p * SCALE + SIZE/2
QImage GravSim::ToQImage(uint SIZE, double SCALE) {
  QImage img(SIZE, SIZE, QImage::Format_ARGB32);
  QPainter qPainter(&img);
  qPainter.setRenderHint(QPainter::Antialiasing);

  img.fill(qRgba(0, 0, 0, 0));
  //qPainter.fillRect(QRect(0, 0, SIZE, SIZE), QColor(255, 255, 255));

  QPen qPen(Qt::red);
  qPen.setWidthF(0.5);
  qPainter.setPen(qPen);
  qPainter.setBrush(Qt::red);

  for (uint i = 0; i < staticParticles.size( ); i++) {
    Particle P = staticParticles[i];
    P.p *= SCALE;
    P.p.x += SIZE / 2;
    P.p.y += SIZE / 2;
    QPointF pF(P.p.x, P.p.y);
    qPainter.drawEllipse(pF, 2.1, 2.1);
  } // for

  for (uint i = 0; i < particles.size( ); i++) {
    Particle P = particles[i];
    P.p *= SCALE;
    P.p.x += SIZE / 2;
    P.p.y += SIZE / 2;
    QPointF pF(P.p.x, P.p.y);

    qPen.setColor(QColor::fromRgb(64, 255, 64));
    qPen.setWidthF(0.72);
    qPainter.setPen(qPen);

    QPainterPath qPath;
    qPath.moveTo(pF);
    for (uint j = 0; j < particles[i].path.size( ); j++) {
      Vector2D pos = particles[i].path[j];
      pos *= SCALE;
      pos.x += SIZE / 2;
      pos.y += SIZE / 2;

      qPath.lineTo(QPointF(pos.x, pos.y));
      qPath.moveTo(QPointF(pos.x, pos.y));
    } // for
    qPainter.drawPath(qPath);

    qPen.setColor(Qt::blue);
    qPen.setWidthF(3.5);
    qPainter.setBrush(Qt::blue);
    qPainter.setPen(qPen);

    qPainter.drawEllipse(pF, 6, 6);
  } // for

  return img;
} // GetSize

GravSim::GravSim( ) {
  this->G = 6.67e-11;
  this->totTime = 0;
  this->stepCounter = 0;

  Particle maan;
  maan.m = 7e22;
  maan.p.x = 3.8e8 * 4;
  maan.v.y = 3.9e3 / 2;
  this->particles.push_back(maan);
} // GravSim

GravSim::~GravSim( ) {

} // ~GravSim



























