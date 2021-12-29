ArrayList<Node> openList = new ArrayList<Node>();
ArrayList<Node> closedList = new ArrayList<Node>();

void astar(PVector start, PVector end) {
  PVector childRelativeLocation[] = new PVector[4];
  childRelativeLocation[0] = new PVector(0, -1);
  childRelativeLocation[1] = new PVector(0, 1);
  childRelativeLocation[2] = new PVector(-1, 0);
  childRelativeLocation[3] = new PVector(1, 0);

  Node startNode = new Node(start);
  Node endNode = new Node(end);

  openList.add(startNode);

  while (!(openList.isEmpty())) {
    Node currentNode = openList.get(0);
    for (int i = 0; i < openList.size(); i++) {
      if (currentNode.f > openList.get(i).f) {
        currentNode = openList.get(i);
      }
    }

    openList.remove(currentNode);
    closedList.add(currentNode);

    if (currentNode.location.x == endNode.location.x && currentNode.location.y == endNode.location.y) {
      while (currentNode.parent != null) {
        int x = (int) currentNode.location.x;
        int y = (int) currentNode.location.y;

        maze[y][x] = "*";
        currentNode = currentNode.parent;
      }
      return;
    }


    ArrayList<Node> childrenList = new ArrayList<Node>();


    for (int i = 0; i < 4; i++) {
      float x = currentNode.location.x + childRelativeLocation[i].x;
      float y = currentNode.location.y + childRelativeLocation[i].y;

      if (x < 0 || x > 49 || y < 0 || y > 49) {
        continue;
      }

      if (maze[(int) y][(int) x] == obstacle) {
        continue;
      }

      Node childNode = new Node(new PVector(x, y));
      childNode.dir = (char) i;
      childNode.setParent(currentNode);
      childrenList.add(childNode);
    }

    for (int i = 0; i < childrenList.size(); i++) {
      Node childNode = childrenList.get(i);
      int flag = 0;

      for (int j = 0; j < closedList.size(); j++) {
        if (childNode.location.x == closedList.get(j).location.x && childNode.location.y == closedList.get(j).location.y) {
          flag = 1;
          //          childrenList.remove(childNode);
          break;
        }
      }

      if (flag == 1) {
        continue;
      }
      childNode.g = currentNode.g + 2;
      childNode.h = (int) heuristic(childNode.location, endNode.location);
      childNode.f = childNode.g + childNode.h;

      flag = 0;
      for (int j = 0; j < openList.size(); j++) {
        if (childNode.location.x == openList.get(j).location.x && childNode.location.y == openList.get(j).location.y) {
          flag = 1;
          childrenList.remove(childNode);
          break;
        }
      }

      if (flag == 1) {
        continue;
      }

      childrenList.remove(childNode);
      openList.add(childNode);
    }
  }
}
