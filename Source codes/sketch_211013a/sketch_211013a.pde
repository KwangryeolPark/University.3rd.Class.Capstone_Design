//Robot robot = new Robot(250, 200, PI);
PVector target = new PVector();

ArrayList<Robot> robots = new ArrayList<Robot>();

String obstacle = "O";
String maze[][] = new String[50][50];

void setup() {
  size(500, 500);
  strokeWeight(5);

  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 50; j++) {
      maze[j][i] = " ";
    }
  }
  maze[12][1] = obstacle;

  astar(new PVector(0, 0), new PVector(19, 34));
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 50; j++) {
      print(maze[i][j]);
    }
    println();
  }

  robots.add(new Robot(100, 100, random(PI)));
  robots.add(new Robot(200, 100, random(PI)));
  robots.add(new Robot(300, 100, random(PI)));
}
float distance[] = new float[3];
void draw() {
  background(255);
  strokeWeight(5);
  stroke(0);

  target.set(mouseX, mouseY);

  distance[0] = PVector.dist(robots.get(0).get(), robots.get(1).get());
  distance[1] = PVector.dist(robots.get(1).get(), robots.get(2).get());
  distance[2] = PVector.dist(robots.get(2).get(), robots.get(0).get());
  //  println(distance[0]);
  //robot.show();

  if (distance[0] < 120) {
    robots.get(0).stop();
    robots.get(1).stop();
  } else {
    robots.get(0).start();
    robots.get(1).start();
  }

  if (distance[1] < 120) {
    robots.get(1).stop();
    robots.get(2).stop();
  } else {
    robots.get(1).start();
    robots.get(2).start();
  }

  if (distance[2] < 120) {
    robots.get(2).stop();
    robots.get(0).stop();
  } else {
    robots.get(2).start();
    robots.get(0).start();
  }

  robots.get(0).setTarget(target);
  robots.get(1).setTarget(target);
  robots.get(2).setTarget(target);


  robots.get(0).show();
  robots.get(1).show();
  robots.get(2).show();


  // target = 102, 401
}
