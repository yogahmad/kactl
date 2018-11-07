/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
Returns the shortest distance between point p and the line segment from point s to e.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{../content/geometry/SegmentDistance}
\end{minipage}
 * Status: tested
 * Usage: 
 * 	Point<double> a, b(2,2), p(1,1);
 * 	bool onSegment = segDist(a,b,p) < 1e-10;
 */
#pragma once

#include "Point.h"

typedef Point<double> P; 
double segDist(P& s, P& e, P& p) { // BEWARE OVERFLOW. BETTER USE THE OTHER
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

// return the distance and point at c, cannot 3D:
double segDist(const P& a, const P& b, const P& p, P& c) {
  double u = (p-a).dot(b-a) / (b-a).dist2();
	if (u < 0.0) {
		c = a;
		return (p - a).dist();
	} else if (u > 1.0) {
		c = b;
		return (p - b).dist();
	}
  c = a + ((b - a) * u);
  return (c - p).dist();
}
