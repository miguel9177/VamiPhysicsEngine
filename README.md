# VamiPhysicsEngine
This was done in my second year of university

Keys to play:

To shoot hold space and then release it, if you click and let go imediatly the space key the shot will be weak, if you hold it for 3 seconds it will be maximum shot power

arrow keys - to move the cue (from bottom, up, left and right of the ball) to change the rotation of the sphere by adding a spin to the white ball, this will affect the force applyed, this works on every camera, but it may spin to the oposite side of the cue position, depending on the current camera position (from 1 to 9).

to aim we have 9 camera positions, and they are all accessible by clicking the numbers:
1 - front of the ball camera position
2 - right of the ball camera position
3 - left of the ball camera position
4 - back of the ball camera position
5 - diagonal back left of the ball camera position
6 - diagonal front left of the ball camera position
7 - diagonal back right of the ball camera position
8 - diagonal front right of the ball camera position
9 - top camera position, this one wont affect the aiming it will just shoot forward.

Z - to turn debug mode on;
X - to turn debug mode off;

F - to togle flying force on the white objects outside of the pool table, this is for physics demonstration only

To move the camera freely:
j - to go forward
n - to go backwards
b - to go left
m - to go right
h - to go down
k - to go up

to rotate the camera freely
, - to rotate left
. - to rotate right

to reset the camera click one of the numbers

to move the white ball freelly use the keys:
w - to move up
s - to move down
a - to move left
d - to move right

in the begining of the scene we can see balls moving left, this is because theres a small zone that is simulating wind, we can see this by clicking 9 (to use the top camera view) and then D (to turn debug mode on), if we do this at the begining of the scene you should be seeing some balls left and a red square where the balls were, this red square is a trigger collider, and if any object triggers with it, it will move that object on the wind direction.

theres also a friction zone behind the white ball initial position, if you click 9 (to use top view) in the begining, and then D (to turn debug mode on), you can see a red squere behind the white ball, this square is a trigger collider, and it will add friction to the object that go trough them, every object has its own friction, but if we go trought the trigger collider it will add more friction.
if you want to test the friction zone, in the begining click 4 and then D and you will be looking at that friction zone, just hold space for a litle bit to add force, and then release it.
