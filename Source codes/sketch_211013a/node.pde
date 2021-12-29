class Node {
  Node parent = null;
  PVector location;
  int f, g, h;

  char dir;

  Node(PVector location) {
    f = 0;
    g = 0;
    h = 0;
    this.location = location;
    dir = 'X';
  }

  void setF(int f) {
    this.f = f;
  }
  void setG(int f) {
    this.g = f;
  }
  void setH(int f) {
    this.h = f;
  }

  void setLocation(PVector location) {
    this.location = location;
  }

  void setParent(Node parent) {
    this.parent = parent;
  };
}
