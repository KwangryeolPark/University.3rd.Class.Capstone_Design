float heuristic(PVector location1, PVector location2) {
/*  float dx = location1.x - location2.x;
  float dy = location1.y - location2.y;

  dx = (dx < 0) ? -dx : dx;
  dy = (dy < 0) ? -dy : dy;

  float dM = (dx < dy) ? dy : dx;
  float dm = (dx > dy) ? dy : dx;

  dM = dM - dm;*/

  return PVector.dist(location1, location2);
}
